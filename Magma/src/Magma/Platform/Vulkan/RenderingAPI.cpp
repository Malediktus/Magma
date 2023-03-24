#include <Magma/pch.h>
#ifdef MG_VULKAN

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>

#include <Magma/Event/Event.h>
#include <Magma/Renderer/RenderingAPI.h>

#include <Magma/Platform/Vulkan/Instance.h>
#include <Magma/Platform/Vulkan/Device.h>
#include <Magma/Platform/Vulkan/Surface.h>
#include <Magma/Platform/Vulkan/SwapChain.h>
#include <Magma/Platform/Vulkan/RenderPass.h>
#include <Magma/Platform/Vulkan/Pipeline.h>
#include <Magma/Platform/Vulkan/Framebuffer.h>
#include <Magma/Platform/Vulkan/CommandPool.h>
#include <Magma/Platform/Vulkan/CommandBuffer.h>
#include <Magma/Platform/Vulkan/Semaphore.h>
#include <Magma/Platform/Vulkan/Fence.h>
#include <Magma/Platform/Vulkan/Buffer.h>
#include <Magma/Platform/Vulkan/DescriptorPool.h>

#include <imgui.h>
// TODO: Make ImGui independent from window implementation, when using native windows
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_vulkan.h>

namespace Magma
{
    const std::vector<VulkanVertex> vertices = {
        {{-0.5f, -0.5f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
        {{ 0.5f, -0.5f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
        {{ 0.5f,  0.5f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
        {{-0.5f,  0.5f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}
    };

    const std::vector<uint16_t> indices = {
        0, 1, 2, 2, 3, 0
    };

    // TODO: Balance
    const std::vector<VkDescriptorPoolSize> imGuiPoolSizes = {
        { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
        { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
        { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
        { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
        { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
    };

#ifdef _DEBUG
    const bool enableValidationLayers = true;
#else
    const bool enableValidationLayers = false;
#endif

    const int MAX_FRAMES_IN_FLIGHT = 2;

    const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};
    const std::vector<const char *> deviceExtensions = {"VK_KHR_portability_subset", VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    class VulkanRenderingAPI : public RenderingAPI
    {
    public:
        VulkanRenderingAPI(Window *window)
            : m_Window(window)
        {
            auto extensions = m_Window->GetVulkanExtensions();
            extensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);

            m_Instance = std::unique_ptr<VulkanInstance>(new VulkanInstance(extensions, enableValidationLayers, validationLayers));
            m_Surface = std::unique_ptr<VulkanSurface>(new VulkanSurface(m_Window, m_Instance->GetInstance()));
            m_Device = std::unique_ptr<VulkanDevice>(new VulkanDevice(deviceExtensions, m_Surface->GetSurface(), m_Instance->GetInstance(), enableValidationLayers, validationLayers));
            m_SwapChain = std::unique_ptr<VulkanSwapChain>(new VulkanSwapChain(m_Window, m_Device->GetDevice(), m_Surface->GetSurface(), m_Device->QuerySwapChainSupport(), m_Device->GetQueueFamilyIndices()));
            m_RenderPass = std::unique_ptr<VulkanRenderPass>(new VulkanRenderPass(m_Device->GetDevice(), m_SwapChain->GetSwapChainImageFormat()));
            m_Pipeline = std::unique_ptr<VulkanPipeline>(new VulkanPipeline("assets/Base.vert.spv", "assets/Base.frag.spv", m_Device->GetDevice(), m_RenderPass->GetRenderPass()));
            m_Framebuffers.resize(m_SwapChain->GetSwapChainImageViews().size());
            for (size_t i = 0; i < m_SwapChain->GetSwapChainImageViews().size(); i++)
                m_Framebuffers[i] = std::unique_ptr<VulkanFramebuffer>(new VulkanFramebuffer(m_Device->GetDevice(), m_RenderPass->GetRenderPass(), m_SwapChain->GetSwapChainExtend(), m_SwapChain->GetSwapChainImageViews()[i]));

            m_CommandPool = std::unique_ptr<VulkanCommandPool>(new VulkanCommandPool(m_Device->GetDevice(), m_Device->GetQueueFamilyIndices()));
            m_IndexBuffer = std::unique_ptr<VulkanIndexBuffer>(new VulkanIndexBuffer(m_Device->GetDevice(), m_Device->GetPhysicalDevice(), m_CommandPool->GetCommandPool(), m_Device->GetGraphicsQueue(), indices));
            m_VertexBuffer = std::unique_ptr<VulkanVertexBuffer>(new VulkanVertexBuffer(m_Device->GetDevice(), m_Device->GetPhysicalDevice(), m_CommandPool->GetCommandPool(), m_Device->GetGraphicsQueue(), vertices));
            m_CommandBuffers = std::unique_ptr<VulkanCommandBufferArray>(new VulkanCommandBufferArray(MAX_FRAMES_IN_FLIGHT, m_Device->GetDevice(), m_CommandPool->GetCommandPool()));

            m_ImageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
            m_RenderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
            m_InFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
            for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
            {
                m_ImageAvailableSemaphores[i] = std::unique_ptr<VulkanSemaphore>(new VulkanSemaphore(m_Device->GetDevice()));
                m_RenderFinishedSemaphores[i] = std::unique_ptr<VulkanSemaphore>(new VulkanSemaphore(m_Device->GetDevice()));
                m_InFlightFences[i] = std::unique_ptr<VulkanFence>(new VulkanFence(m_Device->GetDevice(), true));
            }

            EventDispatcher::Subscribe<WindowResizeEvent>(std::bind(&VulkanRenderingAPI::WindowResizeCallback, this, std::placeholders::_1));
            
            // ImGui init
            m_ImGuiDescriptorPool = std::unique_ptr<VulkanDescriptorPool>(new VulkanDescriptorPool(m_Device->GetDevice(), imGuiPoolSizes));

            ImGui::CreateContext();
            ImGui::StyleColorsDark();
            // TODO: Make window implementation independent
            ImGui_ImplGlfw_InitForVulkan((GLFWwindow*)m_Window->GetWindowEventHandle(), true);
            ImGui_ImplVulkan_InitInfo initInfo{};
            initInfo.Instance = m_Instance->GetInstance();
            initInfo.PhysicalDevice = m_Device->GetPhysicalDevice();
            initInfo.Device = m_Device->GetDevice();
            initInfo.QueueFamily = m_Device->GetQueueFamilyIndices().graphicsFamily.value();
            initInfo.Queue = m_Device->GetGraphicsQueue();
            initInfo.DescriptorPool = m_ImGuiDescriptorPool->GetDescriptorPool();
            // TODO: Balance
            initInfo.MinImageCount = 2;
            initInfo.ImageCount = (uint32_t) m_SwapChain->GetSwapChainImageViews().size();
        
            ImGui_ImplVulkan_Init(&initInfo, m_RenderPass->GetRenderPass());
            
            // Upload ImGui fonts
            {
                VkCommandPool commandPool = m_CommandPool->GetCommandPool();
                VkCommandBuffer commandBuffer = m_CommandBuffers->GetCommandBuffer(0);
                
                MG_ASSERT_MSG(vkResetCommandPool(m_Device->GetDevice(), commandPool, 0) == VK_SUCCESS, "Failed reset command pool for ImGui!");
                VkCommandBufferBeginInfo beginInfo{};
                beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
                beginInfo.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
                
                MG_ASSERT_MSG(vkBeginCommandBuffer(commandBuffer, &beginInfo) == VK_SUCCESS, "Failed to begin command buffer for ImGui!");
                ImGui_ImplVulkan_CreateFontsTexture(commandBuffer);
                MG_ASSERT_MSG(vkEndCommandBuffer(commandBuffer) == VK_SUCCESS, "Failed to end command buffer for ImGui!");
                
                VkSubmitInfo submitInfo{};
                submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
                submitInfo.commandBufferCount = 1;
                submitInfo.pCommandBuffers = &commandBuffer;
                MG_ASSERT_MSG(vkQueueSubmit(m_Device->GetGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE) == VK_SUCCESS, "Failed to submit graphics queue for ImGui!");
                
                vkDeviceWaitIdle(m_Device->GetDevice());
                ImGui_ImplVulkan_DestroyFontUploadObjects();
            }
        }

        ~VulkanRenderingAPI()
        {
            vkDeviceWaitIdle(m_Device->GetDevice());
            
            // ImGui
            ImGui_ImplVulkan_Shutdown();
            m_ImGuiDescriptorPool->DestroyDescriptorPool();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();

            for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
            {
                m_ImageAvailableSemaphores[i]->DestroySemaphore();
                m_RenderFinishedSemaphores[i]->DestroySemaphore();
                m_InFlightFences[i]->DestroyFence();
            }

            m_CommandPool->DestroyCommandPool();

            for (size_t i = 0; i < m_SwapChain->GetSwapChainImageViews().size(); i++)
                m_Framebuffers[i]->DestroyFramebuffer();

            m_Pipeline->DestroyPipeline();
            m_Pipeline->DestroyPipelineLayout();
            m_RenderPass->DestroyRenderPass();

            m_SwapChain->DestroySwapChainImageViews();
            m_SwapChain->DestroySwapChain();
            
            m_IndexBuffer->DestroyBuffer();
            m_IndexBuffer->DestroyBufferMemory();
            m_VertexBuffer->DestroyBuffer();
            m_VertexBuffer->DestroyBufferMemory();
            
            m_Device->DestroyDevice();
            m_Instance->DestroyDebugMessenger();

            m_Surface->DestroySurface();
            m_Instance->DestroyInstance();
        }

        void BeginFrame() override
        {
            m_InFlightFences[m_CurrentFrame]->WaitForSignal();

            VkResult result = vkAcquireNextImageKHR(m_Device->GetDevice(), m_SwapChain->GetSwapChain(), UINT64_MAX, m_ImageAvailableSemaphores[m_CurrentFrame]->GetSemaphore(), VK_NULL_HANDLE, &m_ImageIndex);

            if (result == VK_ERROR_OUT_OF_DATE_KHR)
            {
                RecreateSwapChain();
                return;
            }
            else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
            {
                MG_ASSERT_MSG(false, "Failed to acquire swap chain image!");
            }

            m_InFlightFences[m_CurrentFrame]->Reset();
            m_CommandBuffers->Reset(m_CurrentFrame);
            m_CommandBuffers->Begin(m_CurrentFrame);
            m_RenderPass->Begin(m_CommandBuffers->GetCommandBuffer(m_CurrentFrame), m_Framebuffers[m_ImageIndex]->GetFramebuffer(), m_SwapChain->GetSwapChainExtend());
            m_Pipeline->Bind(m_CommandBuffers->GetCommandBuffer(m_CurrentFrame));
            m_SwapChain->SetViewport(m_CommandBuffers->GetCommandBuffer(m_CurrentFrame));
            m_SwapChain->SetScissor(m_CommandBuffers->GetCommandBuffer(m_CurrentFrame));
            m_VertexBuffer->Bind(m_CommandBuffers->GetCommandBuffer(m_CurrentFrame));
            m_IndexBuffer->Bind(m_CommandBuffers->GetCommandBuffer(m_CurrentFrame));
            m_CommandBuffers->DrawIndexed(m_CurrentFrame, static_cast<uint32_t>(indices.size()));
        }

        void EndFrame() override
        {
            m_RenderPass->End(m_CommandBuffers->GetCommandBuffer(m_CurrentFrame));
            m_CommandBuffers->End(m_CurrentFrame);

            VkSubmitInfo submitInfo{};
            submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

            VkSemaphore waitSemaphores[] = {m_ImageAvailableSemaphores[m_CurrentFrame]->GetSemaphore()};
            VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
            submitInfo.waitSemaphoreCount = 1;
            submitInfo.pWaitSemaphores = waitSemaphores;
            submitInfo.pWaitDstStageMask = waitStages;
            submitInfo.commandBufferCount = 1;
            submitInfo.pCommandBuffers = &m_CommandBuffers->GetCommandBuffer(m_CurrentFrame);

            VkSemaphore signalSemaphores[] = {m_RenderFinishedSemaphores[m_CurrentFrame]->GetSemaphore()};
            submitInfo.signalSemaphoreCount = 1;
            submitInfo.pSignalSemaphores = signalSemaphores;

            MG_ASSERT_MSG(vkQueueSubmit(m_Device->GetGraphicsQueue(), 1, &submitInfo, m_InFlightFences[m_CurrentFrame]->GetFence()) == VK_SUCCESS, "Failed to submit draw command buffer!");

            VkPresentInfoKHR presentInfo{};
            presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

            presentInfo.waitSemaphoreCount = 1;
            presentInfo.pWaitSemaphores = signalSemaphores;

            VkSwapchainKHR swapChains[] = {m_SwapChain->GetSwapChain()};
            presentInfo.swapchainCount = 1;
            presentInfo.pSwapchains = swapChains;
            presentInfo.pImageIndices = &m_ImageIndex;
            presentInfo.pResults = nullptr; // Optional

            VkResult result = vkQueuePresentKHR(m_Device->GetPresentQueue(), &presentInfo);
            if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || m_FramebufferResized)
            {
                m_FramebufferResized = false;
                RecreateSwapChain();
            }
            else if (result != VK_SUCCESS)
            {
                MG_ASSERT_MSG(false, "Failed to present swap chain image!");
            }

            m_CurrentFrame = (m_CurrentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
        }
        
        void BeginGui() override
        {
            ImGui_ImplVulkan_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }
        
        void EndGui() override
        {
            ImGui::Render();
            ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), m_CommandBuffers->GetCommandBuffer(m_CurrentFrame));
        }

    private:
        void RecreateSwapChain()
        {
            vkDeviceWaitIdle(m_Device->GetDevice());
            for (size_t i = 0; i < m_SwapChain->GetSwapChainImageViews().size(); i++)
            {
                m_Framebuffers[i]->DestroyFramebuffer();
                m_Framebuffers[i].reset();
            }
            m_SwapChain->DestroySwapChainImageViews();
            m_SwapChain->DestroySwapChain();
            m_SwapChain.reset();

            m_SwapChain = std::unique_ptr<VulkanSwapChain>(new VulkanSwapChain(m_Window, m_Device->GetDevice(), m_Surface->GetSurface(), m_Device->QuerySwapChainSupport(), m_Device->GetQueueFamilyIndices()));
            for (size_t i = 0; i < m_SwapChain->GetSwapChainImageViews().size(); i++)
                m_Framebuffers[i] = std::unique_ptr<VulkanFramebuffer>(new VulkanFramebuffer(m_Device->GetDevice(), m_RenderPass->GetRenderPass(), m_SwapChain->GetSwapChainExtend(), m_SwapChain->GetSwapChainImageViews()[i]));
        }

        void WindowResizeCallback(const Event &e)
        {
            m_FramebufferResized = true;
        }

        Window *m_Window;

        std::unique_ptr<VulkanInstance> m_Instance;
        std::unique_ptr<VulkanDevice> m_Device;
        std::unique_ptr<VulkanSurface> m_Surface;
        std::unique_ptr<VulkanSwapChain> m_SwapChain;
        std::unique_ptr<VulkanRenderPass> m_RenderPass;
        std::unique_ptr<VulkanPipeline> m_Pipeline;
        std::vector<std::unique_ptr<VulkanFramebuffer>> m_Framebuffers;
        std::unique_ptr<VulkanCommandPool> m_CommandPool;
        std::unique_ptr<VulkanStagingBuffer> m_StagingBuffer;
        std::unique_ptr<VulkanVertexBuffer> m_VertexBuffer;
        std::unique_ptr<VulkanIndexBuffer> m_IndexBuffer;

        std::unique_ptr<VulkanCommandBufferArray> m_CommandBuffers;
        std::vector<std::unique_ptr<VulkanSemaphore>> m_ImageAvailableSemaphores;
        std::vector<std::unique_ptr<VulkanSemaphore>> m_RenderFinishedSemaphores;
        std::vector<std::unique_ptr<VulkanFence>> m_InFlightFences;
        
        std::unique_ptr<VulkanDescriptorPool> m_ImGuiDescriptorPool;

        uint32_t m_CurrentFrame = 0;
        uint32_t m_ImageIndex = 0;
        bool m_FramebufferResized = false;
    };

    std::shared_ptr<RenderingAPI> RenderingAPICreate(Window *window)
    {
        return std::shared_ptr<RenderingAPI>(new VulkanRenderingAPI(window));
    }
}

#endif
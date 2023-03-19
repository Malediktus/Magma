#pragma once

#include <Magma/pch.h>
#ifdef MG_VULKAN

#include <vulkan/vulkan.h>

#include <Magma/Core/Logger.h>
#include <Magma/Platform/Vulkan/Device.h>

#include <vector>

namespace Magma
{
    class VulkanFramebuffer
    {
    public:
        VulkanFramebuffer(const VkDevice &device, const VkRenderPass &renderPass, const VkExtent2D &swapChainExtent, const VkImageView &swapChainImageView)
            : m_Device(device)
        {
            VkImageView attachments[] = {swapChainImageView};

            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = renderPass;
            framebufferInfo.attachmentCount = 1;
            framebufferInfo.pAttachments = attachments;
            framebufferInfo.width = swapChainExtent.width;
            framebufferInfo.height = swapChainExtent.height;
            framebufferInfo.layers = 1;

            MG_ASSERT_MSG(vkCreateFramebuffer(m_Device, &framebufferInfo, nullptr, &m_SwapChainFramebuffer) == VK_SUCCESS, "Failed to create framebuffer!");
        }

        const VkFramebuffer &GetFramebuffer() { return m_SwapChainFramebuffer; }

        void DestroyFramebuffer()
        {
            vkDestroyFramebuffer(m_Device, m_SwapChainFramebuffer, nullptr);
        }

    private:
        const VkDevice &m_Device;
        VkFramebuffer m_SwapChainFramebuffer;
    };
}

#endif
#pragma once

#include <Magma/Renderer/RenderingAPI.h>

namespace Magma
{
    struct QueueFamilyIndices
    {
        std::optional<uint32_t> GraphicsFamily;
        std::optional<uint32_t> PresentFamily;

        bool IsComplete()
        {
            return GraphicsFamily.has_value() && PresentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    class VulkanRenderingAPI : public RenderingAPI
    {
    public:
        VulkanRenderingAPI(Window *window);
        ~VulkanRenderingAPI();

        void Clear(const glm::vec4 &color) const override;
        void DrawIndexed(const size_t numIndices, const bool wireframes) const override;
        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const override;

    private:
        SwapChainSupportDetails GetSwapChainSupport(const VkPhysicalDevice &device);
        int CheckPhysicalDevice(const VkPhysicalDevice &device, const std::vector<const char *> deviceExtensions);
        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
        bool CheckValidationLayers(const std::vector<const char *> validationLayers);
        bool CheckDeviceExtensions(const VkPhysicalDevice &device, const std::vector<const char *> deviceExtensions);
        void CheckRequiredExtensions(const std::vector<const char *> extensions);
        QueueFamilyIndices FindQueueFamilies(const VkPhysicalDevice &device);
        void CreateInstance(const std::vector<const char *> extensions, const VkInstanceCreateFlags flags, const std::vector<const char *> validationLayers);
        void CreateDebugMessenger();
        void CreatePhysicalDevice(const std::vector<const char *> deviceExtensions);
        void CreateLogicalDevice(const std::vector<const char *> extensions, const std::vector<const char *> validationLayers);
        void CreateSurface();
        void CreateSwapChain();

        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
            void *pUserData);

        Window *m_Window;
        VkSwapchainKHR m_SwapChain;
        VkSurfaceKHR m_Surface;
        VkQueue m_PresentQueue;
        VkQueue m_GraphicsQueue;
        VkDevice m_Device;
        VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
        VkDebugUtilsMessengerEXT m_DebugMessenger;
        VkInstance m_Instance;
    };
}
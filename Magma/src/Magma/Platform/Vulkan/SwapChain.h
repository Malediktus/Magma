#pragma once

#include <Magma/pch.h>
#ifdef MG_VULKAN

#include <vulkan/vulkan.h>

#include <Magma/Core/Logger.h>
#include <Magma/Platform/Vulkan/Device.h>

namespace Magma
{
    class VulkanSwapChain
    {
    public:
        VulkanSwapChain(Window *window, const VkDevice &device, const VkSurfaceKHR &surface, const SwapChainSupportDetails swapChainSupport, const QueueFamilyIndices indices)
            : m_Device(device), m_Window(window)
        {
            VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
            VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
            VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities);

            uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

            if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
                imageCount = swapChainSupport.capabilities.maxImageCount;

            VkSwapchainCreateInfoKHR swapchainCreateInfo{};
            swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
            swapchainCreateInfo.surface = surface;
            swapchainCreateInfo.minImageCount = imageCount;
            swapchainCreateInfo.imageFormat = surfaceFormat.format;
            swapchainCreateInfo.imageColorSpace = surfaceFormat.colorSpace;
            swapchainCreateInfo.imageExtent = extent;
            swapchainCreateInfo.imageArrayLayers = 1;
            swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

            uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

            if (indices.graphicsFamily != indices.presentFamily)
            {
                swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
                swapchainCreateInfo.queueFamilyIndexCount = 2;
                swapchainCreateInfo.pQueueFamilyIndices = queueFamilyIndices;
            }
            else
            {
                swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
                swapchainCreateInfo.queueFamilyIndexCount = 0;     // Optional
                swapchainCreateInfo.pQueueFamilyIndices = nullptr; // Optional
            }

            swapchainCreateInfo.preTransform = swapChainSupport.capabilities.currentTransform;
            swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
            swapchainCreateInfo.presentMode = presentMode;
            swapchainCreateInfo.clipped = VK_TRUE;
            swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

            MG_ASSERT_MSG(vkCreateSwapchainKHR(m_Device, &swapchainCreateInfo, nullptr, &m_SwapChain) == VK_SUCCESS, "failed to create swap chain");

            vkGetSwapchainImagesKHR(m_Device, m_SwapChain, &imageCount, nullptr);
            m_SwapChainImages.resize(imageCount);
            vkGetSwapchainImagesKHR(m_Device, m_SwapChain, &imageCount, m_SwapChainImages.data());

            m_SwapChainImageFormat = surfaceFormat.format;
            m_SwapChainExtent = extent;

            m_SwapChainImageViews.resize(m_SwapChainImages.size());

            for (size_t i = 0; i < m_SwapChainImages.size(); i++)
            {
                VkImageViewCreateInfo ImageViewCreateInfo{};
                ImageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
                ImageViewCreateInfo.image = m_SwapChainImages[i];
                ImageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
                ImageViewCreateInfo.format = m_SwapChainImageFormat;
                ImageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
                ImageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
                ImageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
                ImageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
                ImageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
                ImageViewCreateInfo.subresourceRange.baseMipLevel = 0;
                ImageViewCreateInfo.subresourceRange.levelCount = 1;
                ImageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
                ImageViewCreateInfo.subresourceRange.layerCount = 1;

                MG_ASSERT_MSG(vkCreateImageView(m_Device, &ImageViewCreateInfo, nullptr, &m_SwapChainImageViews[i]) == VK_SUCCESS, "Failed to create image views!");
            }
        }

        const VkSwapchainKHR &GetSwapChain() { return m_SwapChain; }
        const VkFormat &GetSwapChainImageFormat() { return m_SwapChainImageFormat; }
        const VkExtent2D &GetSwapChainExtend() { return m_SwapChainExtent; }
        const std::vector<VkImageView> &GetSwapChainImageViews() { return m_SwapChainImageViews; }
        const std::vector<VkImage> &GetSwapChainImages() { return m_SwapChainImages; }

        void DestroySwapChain()
        {
            vkDestroySwapchainKHR(m_Device, m_SwapChain, nullptr);
        }

        void DestroySwapChainImageViews()
        {
            for (auto imageView : m_SwapChainImageViews)
                vkDestroyImageView(m_Device, imageView, nullptr);
        }

    private:
        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats)
        {
            for (const auto &availableFormat : availableFormats)
            {
                if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
                {
                    return availableFormat;
                }
            }

            return availableFormats[0];
        }

        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes)
        {
            for (const auto &availablePresentMode : availablePresentModes)
            {
                if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
                {
                    return availablePresentMode;
                }
            }

            return VK_PRESENT_MODE_FIFO_KHR;
        }

        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities)
        {
            if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
                return capabilities.currentExtent;

            else
            {
                int width = m_Window->GetWidth();
                int height = m_Window->GetHeight();

                VkExtent2D actualExtent = {
                    static_cast<uint32_t>(width),
                    static_cast<uint32_t>(height)};

                actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
                actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

                return actualExtent;
            }
        }

        Window *m_Window;
        const VkDevice &m_Device;

        VkSwapchainKHR m_SwapChain;
        VkFormat m_SwapChainImageFormat;
        VkExtent2D m_SwapChainExtent;
        std::vector<VkImage> m_SwapChainImages;
        std::vector<VkImageView> m_SwapChainImageViews;
    };
}

#endif
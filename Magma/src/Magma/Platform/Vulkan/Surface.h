#pragma once

#include <Magma/pch.h>
#ifdef MG_VULKAN

#include <vulkan/vulkan.h>

#include <Magma/Core/Logger.h>
#include <Magma/Platform/Vulkan/Device.h>

namespace Magma
{
    class VulkanSurface
    {
    public:
        VulkanSurface(const Window *window, const VkInstance &instance)
            : m_Instance(instance)
        {
            MG_ASSERT_MSG(window->CreateVulkanWindowSurface(m_Instance, &mSurface) == VK_SUCCESS, "Failed to create window surface!");
        }

        const VkSurfaceKHR &GetSurface() { return mSurface; }

        void DestroySurface()
        {
            vkDestroySurfaceKHR(m_Instance, mSurface, nullptr);
        }

    private:
        const VkInstance &m_Instance;
        VkSurfaceKHR mSurface;
    };
}

#endif
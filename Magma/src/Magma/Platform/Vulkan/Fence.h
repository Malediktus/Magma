#pragma once

#include <Magma/pch.h>
#ifdef MG_VULKAN

#include <vulkan/vulkan.h>

#include <Magma/Core/Logger.h>
#include <Magma/Platform/Vulkan/Device.h>

namespace Magma
{
    class VulkanFence
    {
    public:
        VulkanFence(const VkDevice &device, bool signaled)
            : m_Device(device)
        {
            VkFenceCreateInfo fenceInfo{};
            fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
            if (signaled)
                fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

            MG_ASSERT_MSG(vkCreateFence(m_Device, &fenceInfo, nullptr, &m_Fence) == VK_SUCCESS, "Failed to create fence!");
        }

        void WaitForSignal(const uint64_t timeout = UINT64_MAX)
        {
            vkWaitForFences(m_Device, 1, &m_Fence, VK_TRUE, timeout);
        }

        void Reset()
        {
            vkResetFences(m_Device, 1, &m_Fence);
        }

        void DestroyFence()
        {
            vkDestroyFence(m_Device, m_Fence, nullptr);
        }

        const VkFence &GetFence() const { return m_Fence; }

    private:
        const VkDevice &m_Device;
        VkFence m_Fence;
    };
}

#endif
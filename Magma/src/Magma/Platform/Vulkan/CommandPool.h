#pragma once

#include <Magma/pch.h>
#ifdef MG_VULKAN

#include <vulkan/vulkan.h>

#include <Magma/Core/Logger.h>
#include <Magma/Platform/Vulkan/Device.h>

namespace Magma
{
    class VulkanCommandPool
    {
    public:
        VulkanCommandPool(const VkDevice &device, const QueueFamilyIndices &queueFamilyIndices)
            : m_Device(device)
        {
            VkCommandPoolCreateInfo poolInfo{};
            poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
            poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
            poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

            MG_ASSERT_MSG(vkCreateCommandPool(m_Device, &poolInfo, nullptr, &m_CommandPool) == VK_SUCCESS, "Failed to create command pool!");
        }

        void DestroyCommandPool()
        {
            vkDestroyCommandPool(m_Device, m_CommandPool, nullptr);
        }

        const VkCommandPool &GetCommandPool() const { return m_CommandPool; }

    private:
        const VkDevice &m_Device;
        VkCommandPool m_CommandPool;
    };
}

#endif
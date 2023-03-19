#pragma once

#include <Magma/pch.h>
#ifdef MG_VULKAN

#include <vulkan/vulkan.h>

#include <Magma/Core/Logger.h>
#include <Magma/Platform/Vulkan/Device.h>

namespace Magma
{
    class VulkanCommandBuffer
    {
    public:
        VulkanCommandBuffer(const VkDevice &device, const VkCommandPool &commandPool)
        {
            VkCommandBufferAllocateInfo allocInfo{};
            allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
            allocInfo.commandPool = commandPool;
            allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
            allocInfo.commandBufferCount = 1;

            MG_ASSERT_MSG(vkAllocateCommandBuffers(device, &allocInfo, &m_CommandBuffer) == VK_SUCCESS, "Failed to allocate command buffers!");
        }

        void Reset()
        {
            vkResetCommandBuffer(m_CommandBuffer, 0);
        }

        const VkCommandBuffer &GetCommandBuffer() { return m_CommandBuffer; }

    private:
        VkCommandBuffer m_CommandBuffer;
    };

    class VulkanCommandBufferArray
    {
    public:
        VulkanCommandBufferArray(const int count, const VkDevice &device, const VkCommandPool &commandPool)
        {
            m_CommandBuffers.resize(count);

            VkCommandBufferAllocateInfo allocInfo{};
            allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
            allocInfo.commandPool = commandPool;
            allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
            allocInfo.commandBufferCount = count;

            MG_ASSERT_MSG(vkAllocateCommandBuffers(device, &allocInfo, m_CommandBuffers.data()) == VK_SUCCESS, "Failed to allocate command buffers!");
        }

        void Reset(const int &index)
        {
            vkResetCommandBuffer(m_CommandBuffers[index], 0);
        }

        const VkCommandBuffer &GetCommandBuffer(const int &index) { return m_CommandBuffers[index]; }

    private:
        std::vector<VkCommandBuffer> m_CommandBuffers;
    };
}

#endif
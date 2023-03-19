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
        
        void Begin()
        {
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            beginInfo.flags = 0;                  // Optional
            beginInfo.pInheritanceInfo = nullptr; // Optional

            MG_ASSERT_MSG(vkBeginCommandBuffer(m_CommandBuffer, &beginInfo) == VK_SUCCESS, "Failed to begin recording command buffer!");
        }
        
        void End()
        {
            MG_ASSERT_MSG(vkEndCommandBuffer(m_CommandBuffer) == VK_SUCCESS, "Failed to end recording command buffer!");
        }
        
        void Draw(const int &numVertices)
        {
            vkCmdDraw(m_CommandBuffer, numVertices, 1, 0, 0);
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
        
        void Begin(const int &index)
        {
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            beginInfo.flags = 0;                  // Optional
            beginInfo.pInheritanceInfo = nullptr; // Optional

            MG_ASSERT_MSG(vkBeginCommandBuffer(m_CommandBuffers[index], &beginInfo) == VK_SUCCESS, "Failed to begin recording command buffer!");
        }
        
        void End(const int &index)
        {
            MG_ASSERT_MSG(vkEndCommandBuffer(m_CommandBuffers[index]) == VK_SUCCESS, "Failed to end recording command buffer!");
        }
        
        void Draw(const int &index, const int &numVertices)
        {
            vkCmdDraw(m_CommandBuffers[index], numVertices, 1, 0, 0);
        }

        const VkCommandBuffer &GetCommandBuffer(const int &index) { return m_CommandBuffers[index]; }

    private:
        std::vector<VkCommandBuffer> m_CommandBuffers;
    };
}

#endif

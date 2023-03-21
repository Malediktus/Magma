#pragma once

#include <Magma/pch.h>
#ifdef MG_VULKAN

#include <vulkan/vulkan.h>

#include <Magma/Core/Logger.h>
#include <Magma/Platform/Vulkan/Device.h>

namespace Magma
{
    class VulkanBuffer
    {
    public:
        VulkanBuffer(const VkBufferUsageFlags &usage, const VkMemoryPropertyFlags &properties, const VkDeviceSize &size, const VkDevice &device, const VkPhysicalDevice &physicalDevice)
            : m_Device(device), m_PhysicalDevice(physicalDevice)
        {
            VkBufferCreateInfo bufferInfo{};
            bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
            bufferInfo.size = size;
            bufferInfo.usage = usage;
            bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
            
            MG_ASSERT_MSG(vkCreateBuffer(m_Device, &bufferInfo, nullptr, &m_Buffer) == VK_SUCCESS, "Failed to create buffer");
            
            VkMemoryRequirements memoryRequirements;
            vkGetBufferMemoryRequirements(m_Device, m_Buffer, &memoryRequirements);
            
            VkMemoryAllocateInfo allocInfo{};
            allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
            allocInfo.allocationSize = memoryRequirements.size;
            allocInfo.memoryTypeIndex = FindMemoryType(memoryRequirements.memoryTypeBits, properties);
            
            MG_ASSERT_MSG(vkAllocateMemory(m_Device, &allocInfo, nullptr, &m_BufferMemory) == VK_SUCCESS, "Failed to allocate buffer memory!");
            vkBindBufferMemory(m_Device, m_Buffer, m_BufferMemory, 0);
        }

        void DestroyBuffer()
        {
            vkDestroyBuffer(m_Device, m_Buffer, nullptr);
        }
        
        void DestroyBufferMemory()
        {
            vkFreeMemory(m_Device, m_BufferMemory, nullptr);
        }
        
        virtual void Bind(const VkCommandBuffer &commandBuffer) = 0;
        
        const VkBuffer &GetBuffer() const { return m_Buffer; }

    private:
        uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
            VkPhysicalDeviceMemoryProperties memoryProperties;
            vkGetPhysicalDeviceMemoryProperties(m_PhysicalDevice, &memoryProperties);
            
            for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++) {
                if ((typeFilter & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                    return i;
                }
            }
            
            MG_ASSERT_MSG(false, "Failed to find suitable memory type!");
        }
        
        friend class VulkanVertexBuffer;
        friend class VulkanStagingBuffer;
        friend class VulkanIndexBuffer;
        
        const VkDevice &m_Device;
        const VkPhysicalDevice &m_PhysicalDevice;
        VkBuffer m_Buffer;
        VkDeviceMemory m_BufferMemory;
    };

    class VulkanStagingBuffer : public VulkanBuffer
    {
    public:
        VulkanStagingBuffer(const VkDevice &device, const VkPhysicalDevice &physicalDevice, const VkDeviceSize dataSize, const void* stagingData)
            : VulkanBuffer(VK_BUFFER_USAGE_TRANSFER_SRC_BIT, (const VkMemoryPropertyFlags) (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT), dataSize, device, physicalDevice)
        {
            void* data;
            vkMapMemory(m_Device, m_BufferMemory, 0, dataSize, 0, &data);
            memcpy(data, stagingData, (size_t) dataSize);
            vkUnmapMemory(m_Device, m_BufferMemory);
        }
        
        void Bind(const VkCommandBuffer &commandBuffer) override
        {
            MG_ASSERT_MSG(false, "Binding staging buffers is not allowed!");
        }
    };

    class VulkanVertexBuffer : public VulkanBuffer
    {
    public:
        VulkanVertexBuffer(const VkDevice &device, const VkPhysicalDevice &physicalDevice, const VkCommandPool &commandPool, const VkQueue &graphicsQueue, const std::vector<VulkanVertex> vertices)
            : VulkanBuffer((const VkBufferUsageFlags) VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, sizeof(vertices[0]) * vertices.size(), device, physicalDevice)
        {
            auto stagingBuffer = std::unique_ptr<VulkanStagingBuffer>(new VulkanStagingBuffer(m_Device, m_PhysicalDevice, sizeof(vertices[0]) * vertices.size(), vertices.data()));
            CopyFromStagingBuffer(stagingBuffer->GetBuffer(), (const VkDeviceSize) sizeof(vertices[0]) * vertices.size(), commandPool, graphicsQueue);
            stagingBuffer->DestroyBuffer();
            stagingBuffer->DestroyBufferMemory();
        }
        
        void CopyFromStagingBuffer(const VkBuffer &stagingBuffer, const VkDeviceSize &size, const VkCommandPool &commandPool, const VkQueue &graphicsQueue)
        {
            VkCommandBufferAllocateInfo allocInfo{};
            allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
            allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
            allocInfo.commandPool = commandPool;
            allocInfo.commandBufferCount = 1;

            VkCommandBuffer commandBuffer;
            vkAllocateCommandBuffers(m_Device, &allocInfo, &commandBuffer);
            
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

            vkBeginCommandBuffer(commandBuffer, &beginInfo);
            
            VkBufferCopy copyRegion{};
            copyRegion.srcOffset = 0; // Optional
            copyRegion.dstOffset = 0; // Optional
            copyRegion.size = size;
            vkCmdCopyBuffer(commandBuffer, stagingBuffer, m_Buffer, 1, &copyRegion);
            
            vkEndCommandBuffer(commandBuffer);
            VkSubmitInfo submitInfo{};
            submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
            submitInfo.commandBufferCount = 1;
            submitInfo.pCommandBuffers = &commandBuffer;

            vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
            vkQueueWaitIdle(graphicsQueue);
            
            vkFreeCommandBuffers(m_Device, commandPool, 1, &commandBuffer);
        }
        
        void Bind(const VkCommandBuffer &commandBuffer) override
        {
            VkBuffer vertexBuffers[] = {m_Buffer};
            VkDeviceSize offsets[] = {0};
            vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
        }
    };

    class VulkanIndexBuffer : public VulkanBuffer
    {
    public:
        VulkanIndexBuffer(const VkDevice &device, const VkPhysicalDevice &physicalDevice, const VkCommandPool &commandPool, const VkQueue &graphicsQueue, const std::vector<uint16_t> indices)
            : VulkanBuffer((const VkBufferUsageFlags) (VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT), VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, sizeof(indices[0]) * indices.size(), device, physicalDevice)
        {
            auto stagingBuffer = std::unique_ptr<VulkanStagingBuffer>(new VulkanStagingBuffer(m_Device, m_PhysicalDevice, sizeof(indices[0]) * indices.size(), indices.data()));
            CopyFromStagingBuffer(stagingBuffer->GetBuffer(), (const VkDeviceSize) sizeof(indices[0]) * indices.size(), commandPool, graphicsQueue);
            stagingBuffer->DestroyBuffer();
            stagingBuffer->DestroyBufferMemory();
        }
        
        void CopyFromStagingBuffer(const VkBuffer &stagingBuffer, const VkDeviceSize &size, const VkCommandPool &commandPool, const VkQueue &graphicsQueue)
        {
            VkCommandBufferAllocateInfo allocInfo{};
            allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
            allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
            allocInfo.commandPool = commandPool;
            allocInfo.commandBufferCount = 1;

            VkCommandBuffer commandBuffer;
            vkAllocateCommandBuffers(m_Device, &allocInfo, &commandBuffer);
            
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

            vkBeginCommandBuffer(commandBuffer, &beginInfo);
            
            VkBufferCopy copyRegion{};
            copyRegion.srcOffset = 0; // Optional
            copyRegion.dstOffset = 0; // Optional
            copyRegion.size = size;
            vkCmdCopyBuffer(commandBuffer, stagingBuffer, m_Buffer, 1, &copyRegion);
            
            vkEndCommandBuffer(commandBuffer);
            VkSubmitInfo submitInfo{};
            submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
            submitInfo.commandBufferCount = 1;
            submitInfo.pCommandBuffers = &commandBuffer;

            vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
            vkQueueWaitIdle(graphicsQueue);
            
            vkFreeCommandBuffers(m_Device, commandPool, 1, &commandBuffer);
        }
        
        void Bind(const VkCommandBuffer &commandBuffer) override
        {
            vkCmdBindIndexBuffer(commandBuffer, m_Buffer, 0, VK_INDEX_TYPE_UINT16);
        }
    };
}

#endif

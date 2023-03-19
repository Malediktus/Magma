#pragma once

#include <Magma/pch.h>
#ifdef MG_VULKAN

#include <vulkan/vulkan.h>

#include <Magma/Core/Logger.h>
#include <Magma/Platform/Vulkan/Device.h>

namespace Magma
{
    class VulkanVertexBuffer
    {
    public:
        VulkanVertexBuffer(const VkDevice &device, const VkPhysicalDevice &physicalDevice, const std::vector<Vertex> vertices)
            : m_Device(device), m_PhysicalDevice(physicalDevice)
        {
            VkBufferCreateInfo bufferInfo{};
            bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
            bufferInfo.size = sizeof(vertices[0]) * vertices.size();
            bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
            bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
            
            MG_ASSERT_MSG(vkCreateBuffer(m_Device, &bufferInfo, nullptr, &m_VertexBuffer) == VK_SUCCESS, "Failed to create vertex buffer");
            
            VkMemoryRequirements memoryRequirements;
            vkGetBufferMemoryRequirements(m_Device, m_VertexBuffer, &memoryRequirements);
            
            VkMemoryAllocateInfo allocInfo{};
            allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
            allocInfo.allocationSize = memoryRequirements.size;
            allocInfo.memoryTypeIndex = FindMemoryType(memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
            
            MG_ASSERT_MSG(vkAllocateMemory(m_Device, &allocInfo, nullptr, &m_VertexBufferMemory) == VK_SUCCESS, "Failed to allocate vertex buffer memory!");
            vkBindBufferMemory(m_Device, m_VertexBuffer, m_VertexBufferMemory, 0);
            
            void* data;
            vkMapMemory(m_Device, m_VertexBufferMemory, 0, bufferInfo.size, 0, &data);
            memcpy(data, vertices.data(), (size_t) bufferInfo.size);
            vkUnmapMemory(m_Device, m_VertexBufferMemory);
        }

        void DestroyVertexBuffer()
        {
            vkDestroyBuffer(m_Device, m_VertexBuffer, nullptr);
        }
        
        void DestroyVertexBufferMemory()
        {
            vkFreeMemory(m_Device, m_VertexBufferMemory, nullptr);
        }
        
        void Bind(const VkCommandBuffer &commandBuffer)
        {
            VkBuffer vertexBuffers[] = {m_VertexBuffer};
            VkDeviceSize offsets[] = {0};
            vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
        }
        
        const VkBuffer &GetVertexBuffer() const { return m_VertexBuffer; }

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

        const VkDevice &m_Device;
        const VkPhysicalDevice &m_PhysicalDevice;
        VkBuffer m_VertexBuffer;
        VkDeviceMemory m_VertexBufferMemory;
    };
}

#endif

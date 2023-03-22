#pragma once

#include <Magma/pch.h>
#ifdef MG_VULKAN

#include <vulkan/vulkan.h>

#include <Magma/Core/Logger.h>
#include <Magma/Platform/Vulkan/Device.h>

namespace Magma
{
    class VulkanDescriptorPool
    {
    public:
        VulkanDescriptorPool(const VkDevice &device, const std::vector<VkDescriptorPoolSize> &poolSizes)
            : m_Device(device)
        {
            VkDescriptorPoolCreateInfo poolInfo{};
            poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
            poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
            poolInfo.maxSets = 1000 * (uint32_t) poolSizes.size();
            poolInfo.poolSizeCount = (uint32_t) poolSizes.size();
            poolInfo.pPoolSizes = poolSizes.data();
            MG_ASSERT_MSG(vkCreateDescriptorPool(m_Device, &poolInfo, nullptr, &m_Pool) == VK_SUCCESS, "Failed to create descriptor pool!");
        }
        
        void DestroyDescriptorPool()
        {
            vkDestroyDescriptorPool(m_Device, m_Pool, nullptr);
        }
        
        const VkDescriptorPool &GetDescriptorPool() const { return m_Pool; }

    private:
        const VkDevice &m_Device;
        VkDescriptorPool m_Pool;
    };
}

#endif

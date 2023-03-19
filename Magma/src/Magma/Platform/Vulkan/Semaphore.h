#pragma once

#include <Magma/pch.h>
#ifdef MG_VULKAN

#include <vulkan/vulkan.h>

#include <Magma/Core/Logger.h>
#include <Magma/Platform/Vulkan/Device.h>

namespace Magma
{
    class VulkanSemaphore
    {
    public:
        VulkanSemaphore(const VkDevice &device)
            : m_Device(device)
        {
            VkSemaphoreCreateInfo semaphoreInfo{};
            semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

            MG_ASSERT_MSG(vkCreateSemaphore(m_Device, &semaphoreInfo, nullptr, &m_Semaphore) == VK_SUCCESS, "Failed to create semaphore!");
        }

        void DestroySemaphore()
        {
            vkDestroySemaphore(m_Device, m_Semaphore, nullptr);
        }

        const VkSemaphore &GetSemaphore() const { return m_Semaphore; }

    private:
        const VkDevice &m_Device;
        VkSemaphore m_Semaphore;
    };
}

#endif
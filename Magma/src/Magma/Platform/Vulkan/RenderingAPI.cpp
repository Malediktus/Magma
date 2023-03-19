#include <Magma/pch.h>

#ifdef MG_VULKAN
#include <Magma/Renderer/RenderingAPI.h>
#include <Magma/Renderer/Renderer.h>

#include <vulkan/vulkan.h>

namespace Magma
{
    class VulkanRenderingAPI : public RenderingAPI
    {
    public:
        VulkanRenderingAPI(Window *window)
            : m_Window(window)
        {
        }

        ~VulkanRenderingAPI()
        {
        }

        void BeginFrame() override
        {
        }

        void EndFrame() override
        {
        }

    private:
        Window *m_Window;
    };

    std::shared_ptr<RenderingAPI> RenderingAPICreate(Window *window)
    {
        return std::shared_ptr<RenderingAPI>(new VulkanRenderingAPI(window));
    }
}

#endif
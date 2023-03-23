#include <Magma/pch.h>
#ifdef MG_OPENGL

#include <glm/glm.hpp>

#include <Magma/Event/Event.h>
#include <Magma/Renderer/RenderingAPI.h>

namespace Magma
{
    class OpenGLRenderingAPI : public RenderingAPI
    {
    public:
        OpenGLRenderingAPI(Window *window)
            : m_Window(window)
        {
        }

        ~OpenGLRenderingAPI()
        {
        }

        void BeginFrame() override
        {
        }

        void EndFrame() override
        {
        }
        
        void BeginGui() override
        {
        }
        
        void EndGui() override
        {
        }

    private:
        Window *m_Window;
    };

    std::shared_ptr<RenderingAPI> RenderingAPICreate(Window *window)
    {
        return std::shared_ptr<RenderingAPI>(new OpenGLRenderingAPI(window));
    }
}

#endif

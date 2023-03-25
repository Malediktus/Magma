#pragma once

#include <Magma/Renderer/GraphicsContext.h>

class GLFWwindow;

namespace Magma
{
class OpenGLContext : public GraphicsContext
{
public:
    OpenGLContext(GLFWwindow* windowHandle);
    
    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;
    
private:
    GLFWwindow* m_WindowHandle;
};
}

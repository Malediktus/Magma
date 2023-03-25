#pragma once

#include <Magma/Renderer/GraphicsContext.h>

class GLFWwindow;

namespace Magma
{
class OpenGLContext : public GraphicsContext
{
public:
    OpenGLContext(GLFWwindow* windowHandle);
    
    void Init() override;
    void SwapBuffers() override;
    
private:
    GLFWwindow* m_WindowHandle;
};
}

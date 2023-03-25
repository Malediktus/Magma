#pragma once

#include <Magma/Core/Window.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace Magma
{
class DebugUI
{
public:
    static void Init(std::shared_ptr<Window> window);
    static void Shutdow();
    static void BeginFrame();
    static void EndFrame();
};
}

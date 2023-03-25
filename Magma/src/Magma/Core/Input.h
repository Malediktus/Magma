#pragma once

#include <Magma/pch.h>
#include <Magma/Event/KeyCode.h>

namespace Magma
{
class Input
{
public:
    static void Init(std::shared_ptr<Window> window);
    static bool GetKey(KeyCode key);
    static int GetMouseX();
    static int GetMouseY();
    static std::pair<int, int> GetMousePos();
    
private:
    static std::shared_ptr<Window> m_Window;
};
}

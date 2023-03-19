#pragma once

#include <Magma/pch.h>
#include <Magma/Event/KeyCode.h>

namespace Magma
{
    class Input
    {
    public:
        static void Init(void *WindowEventHandle);

        static bool GetKey(KeyCode key);

        static int GetMouseX();
        static int GetMouseY();
        static std::pair<int, int> GetMousePos();

    private:
        static void *m_WindowEventHandle; // void* because it differs on platforms
    };
}
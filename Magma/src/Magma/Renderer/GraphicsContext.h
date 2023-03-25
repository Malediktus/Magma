#pragma once

#include <Magma/pch.h>

namespace Magma
{
class GraphicsContext
{
public:
    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;
};
}

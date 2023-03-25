#pragma once

#include <Magma/Renderer/Texture2D.h>

namespace Magma
{
    class VulkanTexture2D : public Texture2D
    {
    public:
        VulkanTexture2D(const std::string &filename);
        ~VulkanTexture2D();
        void Bind() const override;
    };
}

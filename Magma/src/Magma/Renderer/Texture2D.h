#pragma once

#include <Magma/pch.h>

namespace Magma
{
	class Texture2D
	{
	public:
		virtual ~Texture2D() = default;
		virtual void Bind() const = 0;
	};

	std::shared_ptr<Texture2D> Texture2DCreate(const std::string& filename);
}

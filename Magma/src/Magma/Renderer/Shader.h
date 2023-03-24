#pragma once

#include <Magma/pch.h>

namespace Magma
{
	class Shader
	{
	public:
		virtual ~Shader() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};

	std::shared_ptr<Shader> ShaderCreate(const std::string &vertexShaderFilename, const std::string &fragmentShaderFilename);
}
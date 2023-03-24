#pragma once

#include <Magma/pch.h>
#include <glm/glm.hpp>

namespace Magma
{
	class Shader
	{
	public:
		virtual ~Shader() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UploadInt(const std::string& name, const unsigned int value) const = 0;
		virtual void UploadMat4(const std::string& name, const glm::mat4 & value) const = 0;
	};

	std::shared_ptr<Shader> ShaderCreate(const std::string &vertexShaderFilename, const std::string &fragmentShaderFilename);
}

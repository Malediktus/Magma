#include <Magma/pch.h>
#include <Magma/Renderer/Renderer.h>

using namespace Magma;

void Renderer::BeginScene()
{
}

void Renderer::EndScene()
{
}

void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
{
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}

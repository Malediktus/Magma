#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 Color;
out vec2 TexCoord;

uniform mat4 uModelViewProj;

void main()
{
    gl_Position = vec4(aPos, 1.0) * uModelViewProj;
    Color = aColor;
    TexCoord = aTexCoord;
}

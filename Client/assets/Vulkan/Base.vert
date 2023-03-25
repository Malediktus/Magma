#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;

layout(location = 0) out vec4 fragColor;

uniform mat4 uModelViewProj;

void main()
{
    gl_Position = vec4(inPosition, 1.0) * uModelViewProj;
    fragColor = inColor;
}

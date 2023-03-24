#version 330 core

out vec4 FragColor;
  
in vec4 Color;
in vec2 TexCoord;

uniform sampler2D TextureId;

void main()
{
	FragColor = Color; //texture(TextureId, TexCoord) * vec4(Color, 1.0);  
}

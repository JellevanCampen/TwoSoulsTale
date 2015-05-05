#version 430 core

in vec2 fUV;

out vec4 fColor;

uniform sampler2D spriteSampler;

void main()
{
	// fColor = vec4(fUV.x, fUV.y, 1.0f, 1.0f);
	fColor = vec4(texture(spriteSampler, fUV).rgb, 1.0f);
}
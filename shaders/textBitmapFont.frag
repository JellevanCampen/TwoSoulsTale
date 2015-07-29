#version 430 core

in vec2 fUV;

out vec4 color;

uniform vec4 uColor;
uniform sampler2D uSpriteSampler;

void main()
{
	color = vec4(uColor.xyz, uColor.w * texture(uSpriteSampler, fUV).r);
}
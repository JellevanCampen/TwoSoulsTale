#version 430 core

in vec2 fUV;
in vec4 fColor;

out vec4 color;

uniform sampler2D uSpriteSampler;

void main()
{
	color = vec4(fColor.x, fColor.y, fColor.z, fColor.w * texture(uSpriteSampler, fUV).r);
}
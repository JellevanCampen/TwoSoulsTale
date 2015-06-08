#version 430 core

layout(location = 0) in vec2 vPosition;
layout(location = 1) in vec2 vUV; 

out vec2 fUV;

uniform vec2 spriteUV1; 
uniform vec2 spriteUV2; 

uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProjection;

void main()
{
	gl_Position = matProjection * matView * matModel * vec4(vPosition.x, vPosition.y, 0.0f, 1.0f);
	vec2 vUV_flipped = vec2(vUV.x, 1.0f - vUV.y);
	fUV = (spriteUV1 + (vUV_flipped) * (spriteUV2 - spriteUV1));
	fUV.y = -fUV.y;
}
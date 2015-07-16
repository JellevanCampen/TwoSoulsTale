#version 430 core

layout(location = 0) in vec2 vPosition;
layout(location = 1) in vec2 vUV; 

out vec2 fUV;

uniform vec2 uPosBottomLeft; 
uniform vec2 uPosTopRight;

uniform vec2 uUVBottomLeft; 
uniform vec2 uUVTopRight; 

uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProjection;

void main()
{
	// Calculate the position
	float sX = vPosition.x;
	float eX = (1.0f - vPosition.x);
	float sY = vPosition.y;
	float eY = (1.0f - vPosition.y);
	gl_Position = matProjection * matView * matModel * vec4(sX * uPosBottomLeft.x + eX * uPosTopRight.x, sY * uPosBottomLeft.y + eY * uPosTopRight.y, 0.0f, 1.0f);
	
	// Pass the UVs
	float sX_uv = vUV.x;
	float eX_uv = (1.0f - vUV.x);
	float sY_uv = vUV.y;
	float eY_uv = (1.0f - vUV.y);
	fUV = vec2(sX_uv * uUVBottomLeft.x + eX_uv * uUVTopRight.x, sY_uv * uUVBottomLeft.y + eY_uv * uUVTopRight.y);
}
#version 430 core

layout(location = 0) in vec2 vPosition;

uniform vec2 uBottomLeft;
uniform vec2 uTopRight;

uniform mat4 matView;
uniform mat4 matProjection;

void main()
{
	float sX = vPosition.x;
	float eX = (1.0f - vPosition.x);
	float sY = vPosition.y;
	float eY = (1.0f - vPosition.y);
	gl_Position = matProjection * matView * vec4(sX * uBottomLeft.x + eX * uTopRight.x, sY * uBottomLeft.y + eY * uTopRight.y, 0.0f, 1.0f);
}
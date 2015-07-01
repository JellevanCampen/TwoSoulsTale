#version 430 core

layout(location = 0) in float vPosition;

uniform vec2 uStart;
uniform vec2 uEnd;

uniform mat4 matView;
uniform mat4 matProjection;

void main()
{
	float s = vPosition.x;
	float e = (1.0f - vPosition.x);
	gl_Position = matProjection * matView * vec4(s * uStart.x + e * uEnd.x, s * uStart.y + e * uEnd.y, 0.0f, 1.0f);
}
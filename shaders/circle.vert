#version 430 core

#define M_PI 3.1415926535897932384626433832795

layout(location = 0) in float vPosition;

uniform vec2 uPosition;
uniform float uRadius;

uniform mat4 matView;
uniform mat4 matProjection;

void main()
{
	gl_Position = matProjection * matView * vec4(uPosition.x + uRadius * cos(2 * M_PI * vPosition), uPosition.y + uRadius * sin(2 * M_PI * vPosition), 0.0f, 1.0f);
}
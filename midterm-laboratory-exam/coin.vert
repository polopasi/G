#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 vertexEyeSpace;
out vec3 N;
out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

const float PI = 3.141592;
uniform int mode = 0;
uniform float time;

void main()
{

	float t = smoothstep(0.0, 1.0, mod(time, 3.0));

	// dos rotationes por segundo
	float alpha = 4*PI*t;
	float A = 0.5;

	mat3 matrixRotation = mat3(cos(alpha), 0, sin(alpha),
						   0, 1, 0,
						   -sin(alpha), 0, cos(alpha));
	matrixRotation = transpose(matrixRotation);
	
	mat4 matrixJump = mat4( 1, 0, 0, 0,
					   		0, 1, 0, cos(A),
					   		0, 0, 0, 0,
					   		0, 0, 0, 1);
	matrixJump = transpose(matrixJump);

    N = normalize(normalMatrix * normal);
    vertexEyeSpace = modelViewMatrix * vec4(vertex, 1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(matrixRotation * vertex, 1.0);
}

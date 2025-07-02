#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec3 N;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;


void main()
{

	/* 
	 * watch out! Do not make the mistake of writing:
	 * vec3 N = normalize(normalMatrix * normal);
	 * I was declarating again N while doing it in out vec3 N, but shader didn't warn me, 
	 * resulting in a fragColor (in fragment) black
	 */
    N = normalize(normalMatrix * normal);
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}

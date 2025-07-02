#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;
// UNIFORMS PER CALCULAR VECTOR V
out vec3 N;
out vec4 vertexEyeSpace;


uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;

void main()
{
    N = normalize(normal);
    vertexEyeSpace = modelViewMatrix * vec4(vertex, 1.0);    
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;
    mat4 scaleMatrix = mat4(.75, 0, 0, 0,
    			    0, 1.0, 0, 0,
    			    0, 0, 1.0, 0,
    			    0, 0, 0, 1.0);
	scaleMatrix = transpose(scaleMatrix);    			    
    gl_Position = modelViewProjectionMatrix * scaleMatrix * vec4(vertex, 1.0);
}

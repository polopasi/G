#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float time;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
    
    // convert gl_Position from clip space to NDC
    gl_Position = gl_Position/gl_Position.w;
    
    // create scaleMatrix and aplies the scalation
    float scaleFactor = 0.5 + abs(sin(time));
    // be careful to NOT scale the Z component, otherwise, you
    // are messing with fragment depth and the model dissappears
    // when crossing Znear
    mat4 scaleMatrix = mat4(scaleFactor, 0, 0, 0,
                            0 , scaleFactor, 0, 0,
                            0, 0, 1, 0,
                            0, 0, 0, 1);
    scaleMatrix = transpose(scaleMatrix);
    gl_Position = scaleMatrix * gl_Position;
}

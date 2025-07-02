#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * abs(N.z);
    vtexCoord = texCoord;
    
    /*
     * The only change needed is doing abs(N.z) to iluminate correctly 
     * backface faces, and to inverse the Z component of gl_Position,
     * which is in clip space. If you try to invert it before, like
     *
     * modelViewProjectionMatrix * vec4(vertex.xy, -vertex.z, 1.0);
     *
     * you will only rotate the model 180 grades in Y axis.
    */
    
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
    gl_Position.z = -gl_Position.z;
}

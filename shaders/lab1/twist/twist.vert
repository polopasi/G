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
    frontColor = vec4(color,1.0);
    
    float omega = 0.4*vertex.y*sin(time);
    
    /*
     * Even if we use veci() inside mati(), openGL interprets it as
     * a sequence of columns. That's why we make a transpose later
    */
    
    mat3 twistMatrix = mat3(vec3(cos(omega), 0, sin(omega)), 
                            vec3(0, 1, 0),
                            vec3(-sin(omega), 0, cos(omega)));                      
    twistMatrix = transpose(twistMatrix);
    
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(twistMatrix*vertex, 1.0);
}

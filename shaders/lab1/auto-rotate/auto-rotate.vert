#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float speed = 0.5;
uniform float time;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    float omega = speed*time;
    
    /*
     * Watch out: openGL reads matrix by columns, instead of rows
     * the below matrix is the next one:
     *
     *   cos(omega),     0,      sin(omega),
     * (          0,     1,               0, )  
     *  -sin(omega),     0,      cos(omega),
     *
    */
    
    mat3 rotationMatrix = mat3(cos(omega), 0 , -sin(omega), 
                          0, 1, 0,
                          sin(omega), 0, cos(omega));
    gl_Position = modelViewProjectionMatrix * vec4(rotationMatrix * vertex, 1.0);
}

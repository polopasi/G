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
uniform vec3 boundingBoxMax;

void main()
{
    float A = (vertex.y - 0.5)*sin(time);
    if (vertex.y < 0.5) A = 0;
    mat3 rotationMatrix = mat3(1, 0, 0,
                               0, cos(A), sin(A),
                               0, -sin(A), cos(A));
                               
    vec3 translatedVertex = vertex - vec3(0, 1, 0);
    
    mat4 translateUpMatrix = mat4(vec4(1, 0, 0, 0),
                                  vec4(0, 1, 0, 0),
                                  vec4(0, 0, 1, 0),
                                  vec4(0, 1, 0, 1));
                                  
    /*
     * The exercise asks you to translate -1 in Y axis before rotation,
     * and then +1 in Y axis after. To do this I substracted -vec3(0, 1, 0)
     * at the beggining and then multiplied by translateUpMatrix.
     * I used the translateUpMatrix because otherwise I should have split up
     * the gl_Position line.
     *
    */
                                  

    gl_Position = modelViewProjectionMatrix * translateUpMatrix * vec4(rotationMatrix*translatedVertex, 1.0);
    
    
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
}

#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float amplitude = 0.1;
uniform float freq = 1;
uniform float time;

void main()
{

    float d = amplitude*sin(freq*2*3.1415*time);
    vec3 N = normalize(normalMatrix * normal);
    // grey of components of normal.Z is N.z 
    frontColor = vec4(1.0) * N.z;
    vtexCoord = texCoord;
    
    
    /*
     * The exercise is resolved in the hard way: with translationMatrix.
     * 
     * (1) we create the translationMatrix with translation d*normal.i
     *     due to how openGL reads mats (in columns instead of rows), we
     *     must do a transpose to achieve that openGL reads translationMatrix
     *     like we do. Then we multiply to get the translation.
     *
     * (2) the easy and recommended way is to sum d*normal to the point.
     *     vec3 finalPoint = vertex + d*normal;
     *
     * Both solutions are the same. Difference is that in (1) we do it with
     * translation matrix and in (2) we do it with a normal sum. Remember that
     * translationMatrix * vertex = last column (vertex.x + d*normal.x, ....) 
     */
    
    mat4 translationMatrix = mat4(1, 0, 0, d*normal.x,
                                  0, 1, 0, d*normal.y,
                                  0, 0, 1, d*normal.z,
                                  0, 0, 0, 1);
    translationMatrix = transpose(translationMatrix);
    
    vec3 finalPoint = vec4(translationMatrix * vec4(vertex, 1.0)).xyz;
    
    // next line is solution (2)
    //vec3 finalPoint = vertex + d*normal;
    
    gl_Position =  modelViewProjectionMatrix * vec4(finalPoint, 1.0);
    
}

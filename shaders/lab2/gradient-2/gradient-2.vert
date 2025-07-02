#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform vec3 boundingBoxMax;
uniform vec3 boundingBoxMin;

void main()
{

    /*
     * Same exercise as gradient-1, but on this one you must do it on NDC.
     * The only difference, apart from calculing y in clip space and then
     * doing the perspective division (/w), you must change the argument in
     * fract. To know you have to use 2.0, it's easy to think the next:
     * how much do I have to multiply the wide of the if condition (0.5)
     * in order to arrive to an enter number? 2.0 * 0.5 = 1.0
     * This way, mix functions will always work, as fract(2.0 * y)
     * will always go from 0.0 to 1.0.
    */ 

    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
    float y = (gl_Position/gl_Position.w).y;
    
    vec3 red = vec3(1, 0, 0);
    vec3 yellow = vec3(1, 1, 0);
    vec3 green = vec3(0, 1, 0);
    vec3 cian = vec3(0, 1, 1);
    vec3 blue = vec3(0, 0, 1);
    
    vec3 color;
    
    if (y < -0.5) color = mix(red, yellow, fract(2.0 * y));
    else if (y < 0.0) color = mix(yellow, green, fract(2.0 * y));
    else if (y < 0.5) color = mix(green, cian, fract(2.0 * y));
    else if (y < 1.0) color = mix(cian, blue, fract(2.0 * y));
    else color = blue;
    
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
}

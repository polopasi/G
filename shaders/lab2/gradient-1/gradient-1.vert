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
     * This exercise is a mess... it is not hard, but you must
     * know what formula they want you to use exactly. It's mandatory to
     * use fract(x) function to get the coloring between colors
     * rightly. I had to search for a solution in Github on this one
     *
     * The justification to why fract(4.0 * yModel) is that we need to
     * convert the "wide of the if condition" (0.25-0.5-0.75-1.0 = 0.25)
     * into the rang of 0.0-1.0. So 4*0.25 = 1.0.
     *
     * For example, imagine we have yModel = 0.20. As we know that between
     * 0.0 and 0.25 we must use red and yellow colors, this implies we have to paint
     * the fragment with 20% red and 80% yellow. To achieve this in the mix function,
     * we make fract(4.0 * 0.20) = fract(0.80) = 0.80 ==> 80% yellow.
     * In case we have fract(4.0 * 0.25) = fract(1.0) = 1.0 ==> 100% yellow.
    */ 

    float yModel = (vertex.y - boundingBoxMin.y)/(boundingBoxMax.y - boundingBoxMin.y);
    
    vec3 red = vec3(1, 0, 0);
    vec3 yellow = vec3(1, 1, 0);
    vec3 green = vec3(0, 1, 0);
    vec3 cian = vec3(0, 1, 1);
    vec3 blue = vec3(0, 0, 1);
    
    vec3 color;
    
    if (yModel <= 0.25) color = mix(red, yellow, fract(4.0 * yModel));
    else if (yModel <= 0.5) color = mix(yellow, green, fract(4.0 * yModel));
    else if (yModel <= 0.75) color = mix(green, cian, fract(4.0 * yModel));
    else if (yModel <= 1.0) color = mix(cian, blue, fract(4.0 * yModel));
    else color = blue;
    
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
    
}

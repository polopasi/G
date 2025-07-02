#version 330 core

in vec4 frontColor;
in vec3 vertexObjectSpace;
in vec2 vtexCoord;

out vec4 fragColor;

const float PI = 3.141592;

uniform sampler2D colorMap;

void main()
{

    float psi = asin(vertexObjectSpace.y);
    /*
     * Watch out: do not make the mistake of using atan(vertexObjectSpace.z/vertexObjectSpace.x)
     * the sign of the number is very important when using atan, as you could be in any quadrant
     * For example: 4/-2 == -4/2. Therefore, atan(A/B) does NOT know in which quadrant you are.
     * To prevent this problem, you must use the other atan function, atan(a, b) that calculates
     * atan(a/b), so glsl knows the sign of both numbers.
    */
    float theta = atan(vertexObjectSpace.z, vertexObjectSpace.x);

    vec2 st = vec2(theta/(2*PI), (psi/PI) + 0.5);
    fragColor = texture(colorMap, st);
}

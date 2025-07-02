#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform bool classic;
uniform float pi = 3.1415;

void main()
{

    // This exercise is easy, we must code the operations they tell you
    vec2 center = vec2(0.5);
    if (classic) {
        if (distance(center, vtexCoord) < 0.2) fragColor = vec4(1, 0, 0, 1);
        else fragColor = vec4(1);    
    } else {
        float phi = pi/16;
        vec2 u = vtexCoord - center;
        float theta = atan(u.y, u.x);
        if (mod(theta/phi + 0.5, 2) < 1) fragColor = vec4(1, 0, 0, 1);
        else if (distance(center, vtexCoord) < 0.2) fragColor = vec4(1, 0, 0, 1);
        else fragColor = vec4(1);    
    }
}

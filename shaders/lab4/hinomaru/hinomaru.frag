#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

void main()
{
    fragColor = frontColor;
    vec2 center = vec2(0.5);
    if (distance(center, vtexCoord) < 0.2) fragColor = vec4(1, 0, 0, 1);
    else fragColor = vec4(1);
}

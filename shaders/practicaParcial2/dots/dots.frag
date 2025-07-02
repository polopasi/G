#version 330 core

in vec4 gfrontColor;
in vec3 P;
in vec3 C;
out vec4 fragColor;

uniform float size = 0.02;
uniform bool opaque = true;

void main()
{
    if (distance(P, C) > size) {
        if (opaque) fragColor = vec4(1.0);
        else discard;
    }
    else fragColor = gfrontColor;
}

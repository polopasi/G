#version 330 core

in vec3 N;					// in eye space
out vec4 fragColor;

uniform float paintBlack;

void main()
{
    fragColor = vec4(vec3(N.z), 1.0);
    if (paintBlack == 1.0) fragColor = vec4(0,0,0,1);
}

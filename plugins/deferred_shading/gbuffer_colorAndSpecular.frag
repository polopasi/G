#version 330 core

out vec4 fragColor;

uniform vec4 matDiffuse;
uniform float matShininess;

void main()
{
    // TODO: write the correct value in the color buffer
    fragColor = vec4(matDiffuse.x, matDiffuse.y, matDiffuse.z, matShininess);
}


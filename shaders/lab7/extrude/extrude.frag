#version 330 core

in vec4 gfrontColor;
in vec3 NeyeSpaceFrag;
out vec4 fragColor;

void main()
{
    fragColor = vec4(NeyeSpaceFrag.z, NeyeSpaceFrag.z, NeyeSpaceFrag.z, 1.0);
}

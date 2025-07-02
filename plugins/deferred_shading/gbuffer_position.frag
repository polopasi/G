#version 330 core

in vec3 vPos;

out vec4 fragColor;

void main()
{
    // TODO: write the correct value in the color buffer
    fragColor = vec4(vPos.x, vPos.y, vPos.z, 1.0);
}


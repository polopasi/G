#version 330 core

in vec4 frontColor;
out vec4 fragColor;


void main()
{
    float zComponent = gl_FragCoord.z;
    fragColor = vec4(zComponent, zComponent, zComponent, 1.0);
}



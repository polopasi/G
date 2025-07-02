#version 330 core

in vec4 frontColor;
in vec3 normalObjectSpace;
out vec4 fragColor;


void main()
{
    fragColor = vec4((normalObjectSpace.x + 1)/2., (normalObjectSpace.y + 1)/2., (normalObjectSpace.z + 1)/2., 1.0);
}



#version 330 core

in vec4 frontColor;
in vec2 coordinates;
out vec4 fragColor;

uniform float time;

void main()
{
    float xErase = time - 1.0;
    if (coordinates.x > xErase) {
        discard;
    }
    fragColor = vec4(0, 0, 1, 1);
    
}

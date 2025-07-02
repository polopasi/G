#version 330 core

uniform sampler2D colorMap;

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform int N = 3;
uniform float R = 0.2;

void main()
{

    fragColor = texture(colorMap, vtexCoord);
    vec2 C = vec2(0.5);
    if (N == 1) {
        vec2 auxCoordinates = (vtexCoord)*(1./.4) + vec2(0.25);
        if (distance(vtexCoord, C) < R) fragColor = texture(colorMap, auxCoordinates);
        
    } else if (N > 1) {
        for (int i = 1; i < N + 1; ++i) {    
            vec2 auxCoordinates = (vtexCoord)*(i*1./.4) + vec2(pow(0.25, i));
            if (distance(vtexCoord, C) < (R/i)) fragColor = texture(colorMap, auxCoordinates);
        }
    }

}

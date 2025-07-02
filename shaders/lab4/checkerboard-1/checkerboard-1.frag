#version 330 core

uniform sampler2D colorMap;

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform int N = 8;

uniform vec4 black = vec4(vec3(0.0), 1.0);
uniform vec4 white = vec4(vec3(0.8), 1.0);

void main()
{

    /*
     * If you don't write the condition if correctly, test will fail.
     * You must take account on the conditions when x and y are both positive, or both negative, or otherise (else)
    */
    float tileSize = 1/float(N);
    if (vtexCoord.x >= 0 && vtexCoord.y >= 0 || vtexCoord.x < 0 && vtexCoord.y < 0) {
        if (int(vtexCoord.y/tileSize)%2 == 1 && int(vtexCoord.x/tileSize)%2 == 0) fragColor = black;
        else if(int(vtexCoord.y/tileSize)%2 == 0 && int(vtexCoord.x/tileSize)%2 == 1) fragColor = black;
        else fragColor = white;
    }
    else {
            if (int((-vtexCoord.y)/tileSize)%2 == 0 && int((-vtexCoord.x)/tileSize)%2 == 0) fragColor = black;
            else if(int((-vtexCoord.y)/tileSize)%2 == 1 && int((-vtexCoord.x)/tileSize)%2 == 1) fragColor = black;
            else fragColor = white;
    }
}

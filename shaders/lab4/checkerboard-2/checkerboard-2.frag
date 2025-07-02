#version 330 core

uniform sampler2D colorMap;

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform float n;

uniform vec4 black = vec4(vec3(0.0), 1.0);
uniform vec4 white = vec4(vec3(0.8), 1.0);

void main()
{

    /*
     * this solution is correct; however, for some reason test does not change n.
     * if you change its value from viewer, you will get the solution correctly, but 
     * the test does not do it by itself
     * FOUND THE ERROR: I wrote uniform int n, instead of uniform float n.
    */
    float tileSize = 1/float(n);
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

#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D sampler;
uniform float time;
uniform vec2 offset = vec2(0.057, -0.172);
uniform vec2 eye = vec2(0.393, 0.652);

void main()
{
    fragColor = texture(sampler, vtexCoord);
    if (fract(time) > 0.5) {
        vec2 actualCoord = vtexCoord;
        // we replace a circle of radius 0.025
        if (distance(actualCoord, eye) <= 0.025) {
            // we add the needed offset
            vec2 lipsCoord = actualCoord + offset;
            fragColor = texture(sampler, lipsCoord);    
         }    
    }
}

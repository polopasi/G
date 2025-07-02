#version 330 core


in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform float time;
uniform sampler2D fons;
uniform sampler2D noise1;

void main()
{
    vec2 coordinatesNoise = vec2(vtexCoord.x + 0.08*time, vtexCoord.y + 0.07*time);
    vec2 colorNoise = texture2D(noise1, coordinatesNoise).xy;
    vec2 disturbance = colorNoise * vec2(0.003, -0.005);
    fragColor = texture(fons, vtexCoord + disturbance);
}

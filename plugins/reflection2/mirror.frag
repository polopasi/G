#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D mirror0;
uniform float SIZE;

void main()
{
    vec2 st = (gl_FragCoord.xy - vec2(0.5)) / SIZE;
    fragColor = 0.4 * frontColor + 0.6 * texture2D(mirror0, st);
}

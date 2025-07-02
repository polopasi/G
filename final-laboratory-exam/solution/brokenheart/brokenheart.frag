#version 330 core

in vec4 gfrontColor;
in vec2 ftexCoord;
out vec4 fragColor;

uniform sampler2D text0;

void main()
{
	if (texture(text0, ftexCoord).a < 1.0) discard;
    fragColor = texture(text0, ftexCoord);
}

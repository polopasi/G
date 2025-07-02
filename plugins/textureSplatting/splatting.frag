#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D noise0;
uniform sampler2D rock1;
uniform sampler2D grass2;

void main()
{
	/*
	 * from thebookofshaders.com
	 * texture2D(sampler2D sampler, vec2 coord) - retrieves texels from a texture
	 *
	 * using this function we get the color of a texel of each texture (rock, grass and noise)
	 * then we can mix them as a lineal interpolation depending of the color of colorNoise
	*/
	vec4 colorRock = texture2D(rock1, vtexCoord);
	vec4 colorGrass = texture2D(grass2, vtexCoord);
	vec4 colorNoise = texture2D(noise0, vtexCoord);
	vec4 color = mix(colorRock, colorGrass, colorNoise); 
    fragColor = color;
}

#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform vec2 C1 = vec2(0.35, 0.6);
uniform vec2 C2 = vec2(0.65, 0.6);
uniform vec2 C3 = vec2(0.5, 0.13);
uniform float radiAmunt = 0.225;
uniform float radiAvall = 0.45;

uniform vec4 red = vec4(1, 0, 0, 1);

uniform int mode = 0;

float aastep(float threshold, float x) {
	float width = 0.7 * length(vec2(dFdx(x), dFdy(x)));
	return smoothstep(threshold - width, threshold + width, x);
}

void main()
{
	
	if (mode >= 0) {	
		if (distance(C1, vtexCoord) < radiAmunt) fragColor = red;
		if (distance(C2, vtexCoord) < radiAmunt) fragColor = red;
		if (distance(C3, vtexCoord) < radiAvall) {
			fragColor = red;
			if (vtexCoord.t < C3.y) fragColor = vec4(0);
			if (vtexCoord.s < C3.x && vtexCoord.t < (0.5 - (vtexCoord.x - 0.135))) fragColor = vec4(0);
			if (vtexCoord.s > C3.x && vtexCoord.t > (1.0 + (vtexCoord.x - 0.135))) fragColor = vec4(0);
	}
	
    //fragColor = vec4(1, 1, 1, 1);
	if (mode >= 1) {	
		if (distance(C1, vtexCoord) < radiAmunt) fragColor = red;
		else if (distance(C1, vtexCoord) == radiAmunt) aastep(5, vtexCoord.x);
		if (distance(C2, vtexCoord) < radiAmunt) fragColor = red;
		else if (distance(C2, vtexCoord) == radiAmunt) aastep(5, vtexCoord.x);
		if (distance(C3, vtexCoord) < radiAvall) {
			fragColor = red;
			if (vtexCoord.t < C3.y) fragColor = vec4(0);
			if (vtexCoord.s < C3.x && vtexCoord.t < 0.2*vtexCoord.t) fragColor = vec4(0);
		}
		else if (distance(C3, vtexCoord) == radiAvall) aastep(5, vtexCoord.x);
	}


	}
	if (mode >= 2) {
		float d = distance(vtexCoord, C2);
		fragColor = fragColor * max(1.1 - d / 0.75, 0);
	}
	if (mode >= 3) {
		float d = distance(vtexCoord, C2);
		
		float smoothParameter = 0.005/d;
		vec4 colorEspecular = mix(fragColor, vec4(1.0), vec4(smoothParameter));
		fragColor = colorEspecular;
		
		// FACTOR DE ESCALA EN VS
	}

}

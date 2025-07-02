#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

const float PI = 3.141592;
const vec3 golden = vec3(1.0, 0.84, 0.0);
const float shininess = 5.0;

uniform sampler2D colorMap, depthMap1, normalMap2;
uniform float R = 2;
uniform float time;
uniform int mode = 2;
uniform float AO = 1.5;


uniform vec4 lightPosition;
uniform mat3 normalMatrix;

void main()
{
    if (mode == 0) fragColor = texture(colorMap, vtexCoord);
    if (mode == 1) {
    	float d = texture(depthMap1, vtexCoord).x;
    	float f1 = (1 - d) * AO;
    	fragColor = texture(colorMap, vtexCoord) * min(1, f1);
    }
    if (mode == 2) {
    	vec3 N = (texture(normalMap2, vtexCoord)).xyz;
    	vec3 L = normalize(lightPosition.xyz);
    	float f2 = dot(N, L);
    	fragColor = texture(colorMap, vtexCoord) * max(1, f2);
    }
    if (mode == 3) {
    	vec3 N = normalize((texture(normalMap2, vtexCoord)).xyz);
    	vec3 L = lightPosition.xyz; 
    	float f2 = dot(N, L);
    	float d = texture(depthMap1, vtexCoord).x;
    	float f1 = (1 - d) * AO;
    	fragColor = texture(colorMap, vtexCoord) * min(1, f1) * max(1, f2);
    
    }
}

#version 330 core

in vec4 vertexEyeSpace;
in vec3 N;					// in eye space
in vec2 vtexCoord;
out vec4 fragColor;

uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition; // will always be in eye space

uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

uniform float time;
uniform vec2 offset = vec2(0, 0.66666666666667);
uniform float frameX = 0.25;
uniform float frameY = 0.333333333333334;
uniform sampler2D colorMap;


void main()
{
    int slide = 0;
    /* 
     * lightPosition is in eye space, so we use vertexEyeSpace (calculus already done in vertex)
     */
    vec3 L = normalize((lightPosition - vertexEyeSpace).xyz);
    float NL = dot(N, L);
    
    vec3 R = normalize(2*NL*N - L);
    vec3 obs = vec3(0);
    /* 
     * obs is in eye space, so we use vertexEyeSpace (calculus already done in vertex)
     */
    vec3 V = normalize(obs - vertexEyeSpace.xyz);
    float RV = dot(R, V);
    
    vec3 diffuseColor;
    if (int(time)%2 == 0) {
        diffuseColor = vec3(0);
    }
    if (int(time)%2 != 0) {
        diffuseColor = vec3(0.8);
    }
    else if (fract(time) != 0) {
        diffuseColor = mix(vec3(0), vec3(0.8), fract(time));
    }
    
	// we divide coordinates by 4 and 3, so they are limited to one slide
	vec2 reduceCoordinates = vec2(4, 3);
	vec2 finalCoordinates = (vtexCoord / reduceCoordinates) + offset;
	slide = int(time / 2);
	finalCoordinates.x += frameX * (slide / 3);
	finalCoordinates.y -= frameY * slide;
	
    vec4 reflectiveDiffuse = texture(colorMap, finalCoordinates);
    
    fragColor = vec4(diffuseColor, 1.0) * reflectiveDiffuse * max(0, NL);				// diffuse light
    fragColor = fragColor + matSpecular * lightSpecular * pow(max(0, RV), matShininess);// specular light
}

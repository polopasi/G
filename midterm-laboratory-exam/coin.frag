#version 330 core

in vec4 vertexEyeSpace;
in vec3 N;					// in eye space
in vec2 vtexCoord;
out vec4 fragColor;

uniform vec4 llumAmbient = vec4(0.2, 0.2, 0.2, 1.0);
uniform vec4 llumDifosa = vec4(0.7, 0.7, 0.7 , 1.0);
uniform vec4 lightSpecular;
uniform vec4 lightPosition; // will always be in eye space

uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;
uniform mat4 modelViewMatrix;

const vec3 golden = vec3(1.0, 0.84, 0.0);
const float shininess = 5.0;


void main()
{

    vec3 L = normalize((lightPosition - vertexEyeSpace).xyz);
//	vec3 L = (modelViewMatrix * vec4(-1, -1, -1, 1.0)).xyz;
    float NL = dot(N, L);
    
    vec3 R = normalize(2*NL*N - L);
    vec3 obs = vec3(0);
    vec3 V = normalize(obs - vertexEyeSpace.xyz);
    float RV = dot(R, V);
    
    
    fragColor = vec4(vec3(golden), 1.0) * llumAmbient;												// ambient light
    fragColor = fragColor + vec4(vec3(golden), 1.0) * llumDifosa * max(0, NL);						// diffuse light
    if (vtexCoord.s >= 0.5) fragColor = fragColor + matSpecular * lightSpecular * pow(max(0, RV), shininess) * 0.5;// specular light
    else fragColor = fragColor + matSpecular * lightSpecular * pow(max(0, RV), shininess);
}

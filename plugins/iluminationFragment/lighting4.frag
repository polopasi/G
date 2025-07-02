#version 330 core

in vec4 vertexEyeSpace;
in vec3 N;					// in eye space
out vec4 fragColor;

uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition; // will always be in eye space

uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;


void main()
{
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
    
    
    fragColor = matAmbient * lightAmbient;												// ambient light
    fragColor = fragColor + matDiffuse * lightDiffuse * max(0, NL);						// diffuse light
    fragColor = fragColor + matSpecular * lightSpecular * pow(max(0, RV), matShininess);// specular light
}

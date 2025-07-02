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

uniform int NUM = 5;
uniform float decay = 6.0;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;

void main()
{
    fragColor = vec4(0);
    float sizeX = boundingBoxMax.x - boundingBoxMin.x;
    float sizeY = boundingBoxMax.y - boundingBoxMin.y;
    float sizeZ = boundingBoxMax.z - boundingBoxMin.z;
    for (int i = 0; i < (NUM + 1); ++i) {
        for (int j = 0; j < (NUM + 1); ++j) {    
            for (int k = 0; k < (NUM + 1); ++k) {
                /* 
                 * lightPosition is in eye space, so we use vertexEyeSpace (calculus already done in vertex)
                 */
                vec3 coordinatesInsideBox = vec3(i, j, k);
                vec4 lightPos = vec4(float(sizeX/(NUM))*i + boundingBoxMin.x, 
                                     float(sizeY/(NUM))*j + boundingBoxMin.y, 
                                     float(sizeZ/(NUM))*k + boundingBoxMin.z, 1.0);
                lightPos = modelViewMatrix * lightPos;
                vec3 L = normalize((lightPos - vertexEyeSpace).xyz);
                float NL = dot(N, L);
                
                vec3 R = normalize(2*NL*N - L);
                vec3 obs = vec3(0);
                /* 
                 * obs is in eye space, so we use vertexEyeSpace (calculus already done in vertex)
                 */
                vec3 V = normalize(obs - vertexEyeSpace.xyz);
                float RV = dot(R, V);
                vec4 ilum = matAmbient * lightAmbient;												  // ambient light
                ilum = fragColor + matDiffuse * lightDiffuse * max(0, NL);						// diffuse light
                ilum += fragColor + matSpecular * lightSpecular * pow(max(0, RV), matShininess);// specular light
                float d = distance(vertexEyeSpace.xyz, lightPos.xyz);
                fragColor += ilum * exp(-decay*d);
            }}}
}

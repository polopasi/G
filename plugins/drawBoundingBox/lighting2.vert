#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;

uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition; // will always be in eye space

uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

void main()
{

    vec3 N = normalize(normalMatrix * normal);
    vec3 L = normalize(lightPosition - (modelViewMatrix * vec4(vertex, 1.0))).xyz;
    float NL = dot(N, L);
    vec3 R = normalize(2*NL*N - L);
    vec3 obs = vec3(0);
    vec3 V = normalize(obs - (modelViewMatrix * vec4(vertex, 1.0)).xyz);
    float RV = dot(R, V);
    
    frontColor = matAmbient * lightAmbient;								// ambient light
    frontColor = frontColor + matDiffuse * lightDiffuse * max(0, NL);	// diffuse light
    frontColor = frontColor + matSpecular * lightSpecular * pow(max(0, RV), matShininess);	// specular light
    vtexCoord = texCoord;
    
    
    vec3 diagonalBoundingBox = boundingBoxMax - boundingBoxMin;
    mat4 scaleMatrix = mat4(diagonalBoundingBox.x, 0, 0, 0,
                            0, diagonalBoundingBox.y, 0, 0,
                            0, 0, diagonalBoundingBox.z, 0,
                            0, 0, 0, 1);
    scaleMatrix = transpose(scaleMatrix);
    
    
    mat4 translationMatrix = mat4(1, 0, 0, boundingBoxMin.x,
                                  0, 1, 0, boundingBoxMin.y,
                                  0, 0, 1, boundingBoxMin.z,
                                  0, 0, 0, 1);
    translationMatrix = transpose(translationMatrix);
    
    gl_Position = modelViewProjectionMatrix * translationMatrix * scaleMatrix * vec4(vertex, 1.0);
}

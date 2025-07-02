#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform sampler2D positionMap;
uniform sampler2D normalMap1;
uniform int mode = 0;


uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition; // will always be in eye space

uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

vec3 phong (vec3 vertex, vec3 N) {
    vec3 L = normalize(lightPosition - (modelViewMatrix * vec4(vertex, 1.0))).xyz;
    float NL = dot(N, L);
    
    vec3 R = normalize(2*NL*N - L);
    vec3 obs = vec3(0);
    /* 
     * obs is in eye space, so in order to get L, 
     * we will have to convert vertex to eye space, too
     */
    vec3 V = normalize(obs - (modelViewMatrix * vec4(vertex, 1.0)).xyz);
    float RV = dot(R, V);
    
    
    frontColor = matAmbient * lightAmbient;								// ambient light
    if (mode == 2) frontColor = frontColor + matDiffuse * lightDiffuse * max(0, NL);	// diffuse light
    else if (mode == 3)  frontColor = frontColor + vec4(vertex, 1.0) * lightDiffuse * max(0, NL);
    frontColor = frontColor + matSpecular * lightSpecular * pow(max(0, RV), matShininess);	// specular light
    return frontColor.xyz;
}

void main()
{

    
    mat3 scaleMatrix = mat3(.496, 0, 0,
                            0, .496, 0,
                            0, 0, 1);
    scaleMatrix = transpose(scaleMatrix);
    
    mat3 translationMatrix = mat3( 1, 0, .500,
                                   0, 1, .500,
                                   0, 0, 1);
    translationMatrix = transpose(translationMatrix);
    
    // we first scale them to [-496, 496], then add them .500, so we obtain [.004, .996] 
    // important: T * R * S * [X]
    vec2 st = (translationMatrix * scaleMatrix * vertex.xyz).xy;
    vec3 P = texture2D(positionMap, st).rgb;
    vec3 N = texture2D(normalMap1, st).rgb;
    // N is in [0, 1] and we must convert them to [-1, 1]
    N.x = (N.x - 0.5)/0.5;
    N.y = (N.y - 0.5)/0.5;
    N.z = (N.z - 0.5)/0.5;
    
    
    
    N = normalize(normalMatrix * N);
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;
    if (mode == 0) frontColor = vec4(P, 1.0);
    else if (mode == 1) frontColor = vec4(P, 1.0) * N.z;
    else if (mode == 2 || mode == 3) frontColor = vec4(phong(P, N), 1.0);
    gl_Position = modelViewProjectionMatrix * vec4(P, 1.0);
}

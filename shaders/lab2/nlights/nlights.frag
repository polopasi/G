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

uniform int n = 4;
const float pi = 3.141592;


void main()
{

    vec3 lightPos = vec3(10, 0, 0);     // coordinates in eye space
    float rotation = 2*pi / n;          // lights are evenly distributed
    fragColor = vec4(0.0);              // we start with black color
    
    // for each light i to n, we iluminate with the given expression
    for (int i = 0; i < n; ++i) {
        
        // rotation matrix, it is not mandatory to do transpose(M), because we are in eye space
        mat4 rotationMatrix = mat4(cos(rotation*i), -sin(rotation*i), 0, 0,
                                   sin(rotation*i), cos(rotation*i), 0, 0,
                                   0, 0, 0, 0,
                                   0, 0, 0, 1);
        rotationMatrix = transpose(rotationMatrix);
        vec4 ilight = rotationMatrix * vec4(lightPos, 1.0);
        
        
        // lightPosition is in eye space, so we use vertexEyeSpace (calculus already done in vertex)
        vec3 L = normalize((ilight - vertexEyeSpace).xyz);
        float NL = dot(N, L);
        vec3 R = normalize(2*NL*N - L);
        
        vec3 obs = vec3(0);
        // obs is in eye space, so we use vertexEyeSpace (calculus already done in vertex)
        vec3 V = normalize(obs - vertexEyeSpace.xyz);
        float RV = dot(R, V);
        
        // the formula we are given in exercise
        fragColor += (matDiffuse * lightDiffuse * max(0, NL) / sqrt(n)) + matSpecular * lightSpecular * pow(max(0, RV), matShininess);
        }
}

#version 330 core

out vec4 fragColor;

uniform vec3 BoundingBoxMin;
uniform vec3 BoundingBoxMax;

uniform sampler2D colorAndSpecularMap;
uniform sampler2D normalMap;
uniform sampler2D positionMap;

uniform vec3 cameraPosition;

uniform float SIZE;

vec4 phong(vec3 N, vec3 V, vec3 L, vec3 color, float shininess)
{
    vec3 R = reflect(-L, N);
    float NdotL = max(0.0, dot(N, L));
    float RdotV = max(0.0, dot(R, V));
    float Idiff = NdotL;
    float Ispec = 0;
    if (NdotL > 0) Ispec = pow(RdotV, shininess);
    vec4 lightAmbient = vec4(0.2);
    vec4 lightDiffuse = vec4(1.0);
    vec4 lightSpecular = vec4(1.0);
    vec4 matAmbient = vec4(color, 1.0);
    vec4 matDiffuse = vec4(color, 1.0);
    vec4 matSpecular = vec4(1.0);
    return matAmbient * lightAmbient +
           matDiffuse * lightDiffuse * Idiff +
           matSpecular * lightSpecular * Ispec;
}

void main()
{
    vec2 st = (gl_FragCoord.xy - vec2(0.5)) / SIZE;

    vec4 colorAndSpecular = texture(colorAndSpecularMap, st);
    vec3 color = colorAndSpecular.rgb;
    float specular = colorAndSpecular.a;
    vec3 normal = (texture(normalMap, st).rgb - 0.5) * 2;
    vec3 fragmentPosition = texture(positionMap, st).rgb * (BoundingBoxMax - BoundingBoxMin) + BoundingBoxMin;

    vec3 lightPosition = cameraPosition;

    // TODO: compute ilumination with the Phong model
    vec3 N = normalize(normal);
    vec3 V = normalize(cameraPosition - fragmentPosition);
    vec3 L = normalize(lightPosition - fragmentPosition);
    // specular is shininess, but as it is in the range [-1, 1], we must convert it to the usual values of shininess
    // I used mix in this ocassion, the value 64.0 is arbitrarily selected to match to the exercise's picture
    fragColor = phong(N, V, L, color, mix(1.0, 64.0, specular));
}


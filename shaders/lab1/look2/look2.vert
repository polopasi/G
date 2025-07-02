#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float angle = 0.5;
uniform vec3 boundingBoxMin;

void main()
{

    mat4 rotationMatrix = mat4(vec4(cos(angle), 0, -sin(angle), 0),
                               vec4(0, 1, 0, 0),
                               vec4(sin(angle), 0, cos(angle), 0),
                               vec4(0, 0, 0, 1));
    vec4 vertexAux = rotationMatrix*vec4(vertex, 1.0);
    float t = smoothstep(1.45, 1.55, vertex.y);
    vec3 newVertex = mix(vertex, vertexAux.xyz, t);


    
    vec3 N = normalize(normalMatrix * normal);
    vec3 normalRotated = vec4(rotationMatrix * vec4(normal, 1.0)).xyz;
    vec3 newNormal = mix(normalRotated, normal, t);
    vec3 Nnew = normalize(normalMatrix * newNormal);
    frontColor = vec4(vec3(Nnew.z), 1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(newVertex, 1.0);
}

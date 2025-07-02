#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float t = 0.4;
uniform float scale = 4.0;
uniform vec3 boundingBoxMax;
uniform vec3 boundingBoxMin;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;
    
    float c = mix(boundingBoxMax.y, boundingBoxMin.y, t);
    mat4 scaleMatrix = mat4(vec4(1, 0, 0, 0),
                            vec4(0, 1, 0, 0),
                            vec4(0, 0, 1, 0),
                            vec4(0, 0, 0, 1));
    mat4 translationMatrix = mat4(vec4(1, 0, 0, 0),
                                  vec4(0, 1, 0, 0),
                                  vec4(0, 0, 1, 0),
                                  vec4(0, 0, 0, 1));
    
    if ((vertex.y - boundingBoxMin.y) < c) {
        scaleMatrix = mat4(vec4(1, 0, 0, 0),
                           vec4(0, scale, 0, 0),
                           vec4(0, 0, 1, 0),
                           vec4(0, 0, 0, 1));
    }
    else {
        float delta = c*scale - c;
        translationMatrix = mat4(vec4(1, 0, 0, 0),
                                 vec4(0, 1, 0, 0),
                                 vec4(0, 0, 1, 0),
                                 vec4(0, delta, 0, 1));
    }
    
    gl_Position = modelViewProjectionMatrix * translationMatrix * scaleMatrix * vec4(vertex, 1.0);
}

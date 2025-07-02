#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform int tiles = 1;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(normalize(normalMatrix * normal).z);
    /*
     * vtexCoord (texture coordinates) will go from (0, 0) to (tiles, tiles)
     * therefore all coordinates > (1, 1) will repeat, because OpenGL only takes
     * the fract part. For example, (0.2, 0.2) will have same color as (1.2, 1.2)
     */
    vtexCoord = tiles * texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}

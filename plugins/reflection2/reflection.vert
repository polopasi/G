#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform vec3 plane;
uniform vec3 whereMirrorIs;

void main()
{

    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    
    
    if (whereMirrorIs.x == 1.0)
        gl_Position =  modelViewProjectionMatrix * vec4(plane.x - (vertex.x - plane.x), vertex.y, vertex.z, 1.0);
    if (whereMirrorIs.y == 1.0)
        gl_Position =  modelViewProjectionMatrix * vec4(vertex.x, plane.y - (vertex.y - plane.y), vertex.z, 1.0);
    if (whereMirrorIs.z == 1.0)
        gl_Position =  modelViewProjectionMatrix * vec4(vertex.x, vertex.y, plane.z - (vertex.z - plane.z), 1.0);

}

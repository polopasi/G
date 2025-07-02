#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform int test = 0;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;
uniform vec2 mousePosition;
uniform float radius = 300;
uniform vec2 viewport;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

vec2 getMousePositionWindowSpace() {
    if(test == 0) return mousePosition;
    if(test == 1) return vec2(400,520);
    if(test == 2) return vec2(600,225);
    if(test == 3) return vec2(200,375);
    return vec2(400,300);
}

void main()
{
    
    
    vec3 P = (modelViewMatrix * vec4(vertex, 1.0)).xyz;
    float diagonal = distance(boundingBoxMax, boundingBoxMin);
    diagonal = 0.03*diagonal;
    vec3 Pprime = P + normal*diagonal;
    
    // we calculate vertex in window space (Pwindow)
    vec2 Pwindow = (modelViewProjectionMatrix * vec4(vertex, 1.0)).xy;
    // we divide by the homogeneous component in order to convert coordinates to screen space
    Pwindow /= (modelViewProjectionMatrix * vec4(vertex, 1.0)).w;
    /* 
     * once we have Pwindow in screen space (normalized coordinates 0..1) we transform it to pixels
     * 
     * extractedfrom learnOpenGL - Coordinates System
     * And lastly we transform the clip coordinates to screen coordinates in a process we call viewport 
     * transform that transforms the coordinates from -1.0 and 1.0 to the coordinate range defined by 
     * glViewport. The resulting coordinates are then sent to the rasterizer to turn them into fragments. 
     *
     * we add 1.0 to center the vertex into (0, 0) as clip coordinates are [-1..1] and we want the 
     * coordinates in pixels [0..720], so intead of [-1..1] we will have [0..2]. Then we multiply by the size 
     * of viewport to get the coordinates in pixels. However, due to adding 1.0, coordinates no longer have
     * the range of [-1..1], but [0..2], so we will get coordinates in pixels [0..1440]. In order to prevent
     * this we must divide by 2, so we have the correct pixels in range: [0..720].
     */
    Pwindow = (Pwindow + 1.0) * viewport/2;
    
    float d = distance(Pwindow, getMousePositionWindowSpace());
    float t = smoothstep(0.05*radius, 0.8*radius, d);
    vec3 vertexFinal = mix(Pprime, P, t);
    
    vec3 N = normalize(normalMatrix * normal);
    frontColor = mix(vec4(1, 0, 0, 1), vec4(1), t) * N.z;
    vtexCoord = texCoord;
    gl_Position = projectionMatrix * vec4(vertexFinal, 1.0);
}

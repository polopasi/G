#version 330 core

in vec4 frontColor;
in vec2 st;
in vec3 vertexEyeSpace;

out vec4 fragColor;

uniform sampler2D heightMap;
uniform float smoothness = 25.0;
uniform mat3 normalMatrix;

void main()
{

    float epsilon = 1.0/128;
    
    vec2 f = texture2D(heightMap, st).xy;
    
    
    float forwardX = (texture2D(heightMap, vec2(st.x + epsilon, st.y)).x - f.x) / epsilon;
    float forwardY = (texture2D(heightMap, vec2(st.x, st.y + epsilon)).x - f.y) / epsilon;
    
    // Calculate gradient G
    vec2 G = vec2(forwardX, forwardY);
    
    vec3 normalFrag = normalize(vec3(-G.x, -G.y, smoothness));
    normalFrag = normalize(normalMatrix * normalFrag);
    
    fragColor = vec4(normalFrag.z);
}

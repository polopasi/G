#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float time;
uniform vec3 boundingBoxMax;
uniform vec3 boundingBoxMin;

void main()
{

	vec3 centerBox = (boundingBoxMax + boundingBoxMin)/ 2;
	float xSize = boundingBoxMax.x - boundingBoxMin.x;
	float t = abs(sin(time*0.2));	
	float desplazamiento = mix(-0.75*xSize, 0.75*xSize, t);

	//TRANSFORMATIONS        
	vec3 finalVertex = vertex - centerBox;
    mat4 translationMatrix = mat4(1, 0, 0, desplazamiento,
                                  0, 1, 0, 0,
                                  0, 0, 1, 0,
                                  0, 0, 0, 1);
    translationMatrix = transpose(translationMatrix);
    finalVertex = vec4(translationMatrix * vec4(finalVertex, 1.0)).xyz;
    if (finalVertex.x > 0) finalVertex.z *= -1;
    
    gl_Position = modelViewProjectionMatrix * vec4(finalVertex, 1.0);
    
    
    vec3 N = normalize(normalMatrix * normal);
    if (finalVertex.x > 0) frontColor = vec4(color,1.0) * -N.z;
    else frontColor = vec4(1, 1, 1, 1) * N.z;
}

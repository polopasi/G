#version 330 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform bool replica;

out vec4 frontColor;

void main()
{
  // TODO:
  // Aquí has d'implementar el que calgui per a que es tractin les diferents instàncies
  // Recorda que ja està predefinida la variable: int gl_InstanceID

  vec3 N = normalize(normalMatrix * normal);
  frontColor = vec4(N.z);
  gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}

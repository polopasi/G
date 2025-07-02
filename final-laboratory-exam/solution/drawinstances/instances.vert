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

	mat4 scaleMatrix = mat4(.5, 0, 0, 0,
	                        0, .5, 0, 0,
	                        0, 0, .5, 0,
	                        0, 0, 0, 1);
	scaleMatrix = transpose(scaleMatrix);	                        

  vec3 N = normalize(normalMatrix * normal);
  frontColor = vec4(N.z);
  
  // para simplificar, supondre que la esquina inferior de la graella es el centro,
  // asi solo he de hacer traslaciones hacia +X y +Z. Al final, realizare un
  // desplazamiento diagonal en direccion -X y -Z para que el centro de la graella
  // sea el punto (0, 0, 0)
  mat4 Xtranslation = mat4(1, 0, 0, 1.0,
	                        0, 1, 0, 0,
	                        0, 0, 1, 0,
	                        0, 0, 0, 1);
  mat4 Ytranslation = mat4(1, 0, 0, 0,
	                        0, 1, 0, 0,
	                        0, 0, 1, 1.0,
	                        0, 0, 0, 1);	                    
 	Xtranslation = transpose(Xtranslation);	            
 	Ytranslation = transpose(Ytranslation);	 	        
	vec4 vertexAux = scaleMatrix * vec4(vertex, 1.0);
	int row = gl_InstanceID/3;
	int col = gl_InstanceID%3;
	for (int i = 0; i < row; ++i) vertexAux = Ytranslation * vertexAux;
	for (int i = 0; i < col; ++i) vertexAux = Xtranslation * vertexAux;
	
	// desplazamiento diagonal en direccion -X y -Z para que el centro de la graella
  // sea el punto (0, 0, 0)
  mat4 finalTranslation = mat4(1, 0, 0, -1.0,
								                0, 1, 0, 0,
								                0, 0, 1, -1.0,
								                0, 0, 0, 1);
	finalTranslation = transpose(finalTranslation);					               
	gl_Position = modelViewProjectionMatrix * finalTranslation * vertexAux;
}

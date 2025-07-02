#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 vertexObjectSpace[];
in vec3 normalObjectSpace[];
out vec4 gfrontColor;

uniform float time;
uniform mat4 modelViewProjectionMatrix;

const float speed = 0.5;

void main( void )
{

    // the exercise tells us that n is the arithmetic mean of normal of each vertex
    vec3 n = (normalObjectSpace[0] + normalObjectSpace[1] + normalObjectSpace[2])/3;
    
    /*
     * translation matrix speed * time * n, it could be done with
     * gl_in[i].gl_Position + vec4(speed * time * n, 0.0) and it would work 
     * I prefer using matrix to prevent errors
     */
    mat4 translationMatrix = mat4(1, 0, 0, speed * time * n.x,
                                  0, 1, 0, speed * time * n.y,
                                  0, 0, 1, speed * time * n.z,
                                  0, 0, 0, 1);
    translationMatrix = transpose(translationMatrix);

    // we translate the point, then we convert to clip space
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * translationMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
}

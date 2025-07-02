#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;

void main( void )
{


    
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
    
    
    // creates shadow doubling all vertex in the point Y = boundingBoxMin.y
    for( int i = 0; i < 3; ++i) {
		gfrontColor = vec4(0);
		vec4 P = gl_in[i].gl_Position;
		P = vec4(P.x, boundingBoxMin.y, P.z, P.w);
		gl_Position = modelViewProjectionMatrix * P;
		EmitVertex();        
    }
    EndPrimitive();
    
}

#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 30) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

void main( void )
{

    /*
     * I had an error where the last vertex added inside this if()
     * connected with the first primitive of the model. I fixed this
     * problem by changing the line 
     * layout(triangle_strip, max_vertices = 36) out;
     * to
     * layout(triangle_strip, max_vertices = 30) out;
    */
    
    // creates floor of the form boundingBox where boundingBox.y == boundingBoxMin.y

    if (gl_PrimitiveIDIn == 0) {
		gfrontColor = vec4(0, 1, 1, 1);
        float R = distance(boundingBoxMax, boundingBoxMin)/2.;
        vec3 C = (boundingBoxMax + boundingBoxMin)/2.;
        
        vec3 P = vec3(C.x + R, boundingBoxMin.y - 0.01, C.z + R);
        gl_Position = modelViewProjectionMatrix * vec4(P, 1.0);
		EmitVertex();
		P = vec3(C.x + R, boundingBoxMin.y - 0.01, C.z - R);
        gl_Position = modelViewProjectionMatrix * vec4(P, 1.0);
		EmitVertex();
		P = vec3(C.x - R, boundingBoxMin.y - 0.01, C.z - R);
        gl_Position = modelViewProjectionMatrix * vec4(P, 1.0);
		EmitVertex();
		
        EndPrimitive();
        
        
		P = vec3(C.x + R, boundingBoxMin.y - 0.01, C.z + R);
        gl_Position = modelViewProjectionMatrix * vec4(P, 1.0);
		EmitVertex();
		P = vec3(C.x - R, boundingBoxMin.y - 0.01, C.z - R);
        gl_Position = modelViewProjectionMatrix * vec4(P, 1.0);
		EmitVertex();
		P = vec3(C.x - R, boundingBoxMin.y - 0.01, C.z + R);
        gl_Position = modelViewProjectionMatrix * vec4(P, 1.0);
		EmitVertex();
		
        EndPrimitive();
    }

        
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
    
    
    // creates shadow doubling vertex in position Y = boundingBoxMin.y
    for( int i = 0; i < 3; ++i) {
		gfrontColor = vec4(0);
		vec4 P = gl_in[i].gl_Position;
		P = vec4(P.x, boundingBoxMin.y, P.z, P.w);
		gl_Position = modelViewProjectionMatrix * P;
		EmitVertex();        
    }
    EndPrimitive();
    
}

#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 40) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
out vec3 uv;

uniform float size = 0.07;
uniform float depth = -0.01;
uniform mat4 modelViewProjectionMatrix;

void main( void )
{

	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
    
    // calculate center of triangle
	vec4 c0 = gl_in[0].gl_Position;
	vec4 c1 = gl_in[1].gl_Position;	
	vec4 c2 = gl_in[2].gl_Position;		
	vec4 C = (c0 + c1 + c2)/3;
    
    // draw the rectangle emiting a total of four vertex of the form (C.x +- size, C.y +- size, C.z + depth, 1.0)
	gfrontColor = vec4(1, 1, 0, 1.0);
	uv = vec3(7, 7, 1);
    gl_Position = modelViewProjectionMatrix * vec4(C.x + size, C.y + size, C.z - depth, 1.0);
    EmitVertex();
    uv = vec3(7, 0, 1);
    gl_Position = modelViewProjectionMatrix * vec4(C.x + size, C.y - size, C.z - depth, 1.0);
    EmitVertex();   
    uv = vec3(0, 7, 1);
    gl_Position = modelViewProjectionMatrix * vec4(C.x - size, C.y + size, C.z - depth, 1.0);
    EmitVertex();
    uv = vec3(0, 0, 1);
    gl_Position = modelViewProjectionMatrix * vec4(C.x - size, C.y - size, C.z - depth, 1.0);
    EmitVertex();
    EndPrimitive(); 
    
}

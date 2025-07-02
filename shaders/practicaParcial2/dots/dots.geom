#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 N[];
out vec4 gfrontColor;
out vec3 P;
out vec3 C;

uniform mat4 modelViewProjectionMatrix;
uniform bool culling = true;

void main( void )
{
    
    float cx = (gl_in[0].gl_Position.x + gl_in[1].gl_Position.x + gl_in[2].gl_Position.x) / 3;
    float cy = (gl_in[0].gl_Position.y + gl_in[1].gl_Position.y + gl_in[2].gl_Position.y) / 3;
    float cz = (gl_in[0].gl_Position.z + gl_in[1].gl_Position.z + gl_in[2].gl_Position.z) / 3;
    C = vec3(cx, cy, cz);
    
    bool capZnegativa = true;
    
	for( int i = 0 ; i < 3 ; i++ )
	{
		if (N[i].z < 0) capZnegativa = false;
		// careful to NOT write the next line AFTER EmitVertex(). Otherwise, the shader starts with
		// an uncertain P value
        P = gl_in[i].gl_Position.xyz;
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();
    
    if (!(culling && capZnegativa)) EndPrimitive();
}

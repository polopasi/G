#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec2 vtexCoord[];
out vec4 gfrontColor;
out vec2 ftexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform float time;
uniform float PI = 3.1415;

void main( void )
{

	
	float t = smoothstep(0.0, 1.0, min(1.0, mod(time, 5.0)/5.0));
	float periode = time / 5;
	float alpha = (2*PI/5.0)*t;
	mat4 rotationMatrix = mat4(cos(alpha), -sin(alpha), 0, 0,
				   sin(alpha), cos(alpha), 0, 0,
				   0,0,0,0,
				   0, 0, 0, 1);
	rotationMatrix = transpose(rotationMatrix);			   

	mat4 translationMatrix = mat4(1, 0, 0, 0.75 * t,
				      0, 1, 0, 0,
				      0, 0, 1, 0,
				      0, 0, 0, 1);
	translationMatrix = transpose(translationMatrix);

	for( int i = 0 ; i < 3 ; i++ )
	{
		vec4 c0 = gl_in[0].gl_Position;
		vec4 c1 = gl_in[1].gl_Position;	
		vec4 c2 = gl_in[2].gl_Position;		
		vec4 C = (c0 + c1 + c2)/3;
		ftexCoord = vtexCoord[i];
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * rotationMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
    
	for( int i = 0 ; i < 3 ; i++ )
	{
		ftexCoord = vtexCoord[i];
		gfrontColor = vfrontColor[i];	
		// this vertex v0
		gl_Position = gl_in[i].gl_Position;
		// the next one v1
		vec4 positionNextVertex = gl_in[(i + 1)%3].gl_Position;
		// the new vertex will be in:
		gl_Position = modelViewProjectionMatrix * rotationMatrix * mix(gl_Position, positionNextVertex, .4);
		EmitVertex();
	}    
	EndPrimitive();
}

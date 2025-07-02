#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 80) out;

in vec4 vfrontColor[];
in vec3 vertexObjectSpace[];
in vec3 normalObjectSpace[];
in vec3 NeyeSpace[];
out vec4 gfrontColor;
out vec3 NeyeSpaceFrag;

uniform mat4 modelViewProjectionMatrix;
uniform float d = 2.;

void main( void )
{

    vec3 N = (normalObjectSpace[0] + normalObjectSpace[1] + normalObjectSpace[2])/3;
	for( int i = 0 ; i < 3 ; i++ )
	{
	    NeyeSpaceFrag = NeyeSpace[i];
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
		
	for( int i = 0 ; i < 3 ; i++ )
	{
	    NeyeSpaceFrag = NeyeSpace[i];
		vec4 P = gl_in[i].gl_Position + d * vec4(N, 0);
		gl_Position = modelViewProjectionMatrix * P;
		EmitVertex();
	}
    EndPrimitive();
    
    /*
     * the rest of the code is the create the faces other than
     * the base and the top (triangles v_0, v_1, v_2)
    */
    
    NeyeSpaceFrag = NeyeSpace[0];
	gl_Position = modelViewProjectionMatrix * gl_in[0].gl_Position;
	EmitVertex();
	NeyeSpaceFrag = NeyeSpace[0];
	vec4 P = gl_in[0].gl_Position + d * vec4(N, 0);
	gl_Position = modelViewProjectionMatrix * P;
	EmitVertex();
    NeyeSpaceFrag = NeyeSpace[1];
	gl_Position = modelViewProjectionMatrix * gl_in[1].gl_Position;
	EmitVertex();
	NeyeSpaceFrag = NeyeSpace[1];
	P = gl_in[1].gl_Position + d * vec4(N, 0);
	gl_Position = modelViewProjectionMatrix * P;
	EmitVertex();
    EndPrimitive();
    
        
    NeyeSpaceFrag = NeyeSpace[1];
	gl_Position = modelViewProjectionMatrix * gl_in[1].gl_Position;
	EmitVertex();
	NeyeSpaceFrag = NeyeSpace[1];
	P = gl_in[1].gl_Position + d * vec4(N, 0);
	gl_Position = modelViewProjectionMatrix * P;
	EmitVertex();
    NeyeSpaceFrag = NeyeSpace[2];
	gl_Position = modelViewProjectionMatrix * gl_in[2].gl_Position;
	EmitVertex();
	NeyeSpaceFrag = NeyeSpace[2];
	P = gl_in[2].gl_Position + d * vec4(N, 0);
	gl_Position = modelViewProjectionMatrix * P;
	EmitVertex();
    EndPrimitive();
    
    NeyeSpaceFrag = NeyeSpace[1];
    gl_Position = modelViewProjectionMatrix * gl_in[1].gl_Position;
    EmitVertex();
    NeyeSpaceFrag = NeyeSpace[1];
    P = gl_in[1].gl_Position + d * vec4(N, 0);
    gl_Position = modelViewProjectionMatrix * P;
    EmitVertex();
    NeyeSpaceFrag = NeyeSpace[0];
    gl_Position = modelViewProjectionMatrix * gl_in[0].gl_Position;
    EmitVertex();
    NeyeSpaceFrag = NeyeSpace[0];
    P = gl_in[0].gl_Position + d * vec4(N, 0);
    gl_Position = modelViewProjectionMatrix * P;
    EmitVertex();
    EndPrimitive();
}

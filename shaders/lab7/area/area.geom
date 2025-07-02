#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;

const float areamax = 0.0005;

void main( void )
{
    /*
     * this code does not work for some reason with other models
     * other than man!
    */
    
    // u and v are vectors from vertex_0 to the other two
    vec3 u = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    vec3 v = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    // area is the magnitude of the cross product of u and v (||u x v||)
    // the area obtained is the area of the parallelogram, so we divide by 2
    // to get the area of the triangle
    vec3 crossVectors = cross(u, v)/2;
    float area = length(crossVectors);
    area /= areamax;
    // we paint the triangle with yellow if area = 1.0 or red if area = 0.0
    vec3 color = vec3(1, area, 0);
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vec4(color, 1.0);
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
}

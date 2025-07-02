#version 330 core

in vec4 vertexEyeSpace;
in vec3 N;					// in eye space
out vec4 fragColor;

uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition; // will always be in eye space

uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

uniform mat4 viewMatrix;
uniform mat4 viewMatrixInverse;
uniform mat4 modelMatrix;

uniform bool world;


vec4 light(vec3 N, vec3 V, vec3 L) 
{
	N = normalize(N); V=normalize(V); L=normalize(L);
	vec3 R = normalize(2.0*dot(N, L)*N-L);
	float NdotL = max(0.0, dot(N, L));
	float RdotV = max(0.0, dot(R, V));
	float Idiff = NdotL;
	float Ispec = 0;
	if (NdotL > 0) Ispec = pow (RdotV, matShininess);
	return
		matAmbient * lightAmbient +
		matDiffuse * lightDiffuse * Idiff +
		matSpecular * lightSpecular * Ispec;
}


void main()
{
    /* 
     * lightPosition is in eye space, so we use vertexEyeSpace (calculus already done in vertex)
     */
    vec3 obs = vec3(0);
    /* 
     * obs is in eye space, so we use vertexEyeSpace (calculus already done in vertex)
     */
    
    vec3 V;
    vec3 L;
    /*
     * we declarate this Nfrag, because otherwise, in else block, we get an error
     * error C765: assignment to varying 'N'
     *
     * extracted from GLSL 4.20 spec, Page 38, Section 4.3.4: Input Variables:
     * Variables declared as inputs cannot be written to during shader execution.
     */
    vec3 Nfrag = N;
    
    if (!world) {
    	V = normalize(obs - vertexEyeSpace.xyz);
    	L = normalize((lightPosition - vertexEyeSpace).xyz);
    } else {
	    Nfrag = vec3(transpose(viewMatrix) * vec4(N, 1.0)).xyz;
	    
	    /*
	     * must be careful with calculing V and L in world space
         * an error I did at my first coding was calculing V and L in
         * Eye Space, then convert them to World. This is an error due to
         * matrix multiplication not being commutative. For example, doing
         * 
    	 *   V = obs - vertexEyeSpace.xyz;
	     *   V = normalize((viewMatrixInverse * vec4(V, 1.0)).xyz);
	     *
	     * does not equal to this
	     *
    	 *   V = normalize((viewMatrixInverse * vec4(obs, 1.0)).xyz - (viewMatrixInverse * vertexEyeSpace).xyz);
    	 *
    	 * so doing the next piece of code is wrong:
    	 *
    	 *
    	 * V = obs - vertexEyeSpace.xyz;
	     * V = normalize((viewMatrixInverse * vec4(V, 1.0)).xyz);
    	 * L = (lightPosition - vertexEyeSpace).xyz;
    	 * L = normalize((viewMatrixInverse * vec4(L, 1.0)).xyz);
    	 *
	    */
	    
    	
    	
    	V = normalize((viewMatrixInverse * vec4(obs, 1.0)).xyz - (viewMatrixInverse * vertexEyeSpace).xyz);
    	L = normalize((viewMatrixInverse * lightPosition).xyz - (viewMatrixInverse * vertexEyeSpace).xyz);
    }
    
    fragColor = light(Nfrag, V, L);
}

#version 330 core

in vec4 vertexEyeSpace;
in vec3 N;					// in eye space
in vec3 vertSpaceModel;
in vec3 colorShader;
out vec4 fragColor;

uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition; // will always be in eye space

uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;


void main()
{

    /* 
     * dFdx and dFdy returns the approximations to the derivatives.
     * Applying them to a position on a surface returns a tangent to 
     * that surface. As the ross-product of two vectors is perpendicular
     * to both vectors, the cross-product of two tangets is normal to
     * the surface
     */
    vec3 dx = dFdx(vertexEyeSpace.xyz);
    vec3 dy = dFdy(vertexEyeSpace.xyz);
    vec3 calculatedN = normalize(cross(dx, dy));
    
    // still works with Phong Illumination Model, but exercise tells you to do this
    fragColor = vec4(colorShader, 1.0) * calculatedN.z;
}

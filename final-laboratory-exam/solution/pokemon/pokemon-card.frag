#version 330 core

in vec4 frontColor;
in vec3 N;
in vec4 vertexEyeSpace;
out vec4 fragColor;

in vec2 vtexCoord;
uniform sampler2D pika0;		
uniform sampler2D pikaback1;		//back
uniform sampler2D pikafoil2;
uniform sampler2D pikamask3;
uniform int mode = 0;

uniform mat4 modelViewMatrixInverse;


vec3 foilColor(float hue) {

	float saturation = 1.0;
	float value = 1.0;
	vec3 hsv = vec3(hue, saturation, value);
	// convert HSV to RGB
	vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
	vec3 p = abs(fract(hsv.xxx + K.xyz) * 6.0 - K.www);
	vec3 rgb = hsv.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), hsv.y);
	return rgb;

}

void main()
{
    vec3 obs = vec3(0);
    vec3 V = normalize(obs - vertexEyeSpace.xyz);
    vec4 VinWorldSpace = modelViewMatrixInverse * vec4(V, 0.0);
    float NV = dot(N, V);

    
    vec4 albedo;
    // frontal
    if (NV < 1.0) {
    	albedo = texture(pika0, vtexCoord);
	  	if (mode >= 1) {
	  		vec2 foilMotion = V.xy * vec2(0.5, 0.3);
	  		vec2 foilTexCoordOffset = vtexCoord + foilMotion;
	  		float hue = fract(foilTexCoordOffset.x + foilTexCoordOffset.y);
	  		vec3 foil = foilColor(hue);
	  		
	  		float angle = cos(dot(V, vec3(0, 0, 1)));
	  		float reflectiveAngle = cos(angle);
	  		
	  		float reflectiveFactor = 1.4 - reflectiveAngle;
	  		reflectiveFactor = pow(reflectiveFactor, 0.5);
	  		reflectiveFactor = clamp(reflectiveFactor, 0.0, 1.0);
	  		fragColor = 1.0 - (1.0 - albedo) * (1.0 - vec4(foil, 1.0) * reflectiveFactor);
	  		
	  		if (mode == 2) {
		  		vec4 p1 = texture(pikafoil2, vtexCoord);
		  		vec4 p2 = texture(pikafoil2, vtexCoord * 0.5);
		  		vec4 p3 = texture(pikafoil2, vtexCoord * 0.25);
		  		
		  		vec3 f1 = foilColor(normalize(hue + .25));
		  		vec3 f2 = foilColor(normalize(hue + .50));		  		
		  		vec3 f3 = foilColor(normalize(hue + .75));		
		  		foil = foil * 0.7 + p1.xyz + p2.xyz * f2 + p3.xyz * f3;  	
		  		
		  		vec4 mask = texture(pikamask3, vtexCoord);
		  		// si mascara blanca escala por .75
		  		if (mask == vec4(1.0)) foil * 0.75;
				fragColor = 1.0 - (1.0 - albedo) * (1.0 - vec4(foil, 1.0) * reflectiveFactor);
		  					  		
	  		}
	  	}
	  	else fragColor = albedo;
	} // back face
    else {
    	albedo = texture(pikaback1, vtexCoord);
	}
  	
}

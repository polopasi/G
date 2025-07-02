#version 330 core

uniform sampler2D colorMap;
uniform vec2 offset = vec2(0, 0.8333);
uniform float frameX = 0.125;
uniform float frameY = 0.16666666667;
uniform float time;

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

void main()
{
    // the animation has 30 FPS, so each second contains 30 frames
	int tile = int(30 * time);
	
	// we divide coordinatesby 8 and 6, so they are limited to one slide
	vec2 reduceCoordinates = vec2(8, 6);
	vec2 finalCoordinates = (vtexCoord / reduceCoordinates) + offset;
	
	/*
	 * - Rows will "overflow", but due to the textures using 
	 *   REPEAT mode, they will take the fractional part
	 * - Columns will add +1 only per 8 slides
	 */
	finalCoordinates.x += frameX * tile;
	finalCoordinates.y -= frameY * (tile / 8);
	
	// the exercise ask us to multiply by color.a (opacity component), otherwise, we get
	// an orange circle in the back of the explosion
    fragColor = texture(colorMap, finalCoordinates) *  texture(colorMap, finalCoordinates).w;
}

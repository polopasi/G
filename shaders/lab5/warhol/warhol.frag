#version 330 core

uniform sampler2D colorMap;

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;


//http://gamedev.stackexchange.com/questions/59797/glsl-shader-change-hue-saturation-brightness

vec3 rgb2hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}



void main()
{
    vec3 color = texture2D(colorMap, 2*vtexCoord).xyz;
    vec3 hsv = rgb2hsv(color);
    hsv.y = 2*hsv.y;
    // when you increase ++x (from left to right) you must add 0.4 to hue
    // when you increase ++y (from down to up) you must add 0.2 to hue
    // due to coordinates being in form [0, 1], you must divide (/.5) to get the quadrant you are in
    hsv.x = hsv.x + 0.2 + int(vtexCoord.x/.5)*0.4 + int(vtexCoord.y/.5)*0.2;
    fragColor = vec4(hsv2rgb(hsv), 1.0);
}

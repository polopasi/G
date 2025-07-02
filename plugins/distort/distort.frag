
#version 330 core
out vec4 fragColor;

uniform sampler2D colorMap;
uniform float time;
uniform float SIZE;

const int W = 4; // filter size: 2W*2W

void main()
{
    vec2 st = (gl_FragCoord.xy - vec2(0.5)) / SIZE;
    float a = 1.0/SIZE;
    vec2 stNew = st;
    stNew.s += (0.01*sin(10.0*time + 30.0*st.s));
    fragColor = texture2D(colorMap, stNew);
    
}



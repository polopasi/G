#version 330 core

in vec4 frontColor;
in float zDepth;
out vec4 fragColor;

void main()
{
    fragColor = frontColor;
    /*
     * gl_FragDepth is a variable that defines the depth
     * in Z axis of this fragment.
    */
    gl_FragDepth = 1.0 - zDepth;
}

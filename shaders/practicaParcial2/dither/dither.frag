#version 330 core

in vec4 frontColor;
in vec3 N;
out vec4 fragColor;

uniform int mode = 1;

void main()
{
    float color = N.z;
    if (mode == 1) {
        if (N.z < 0.5) color = 0.0;
        else color = 1.0;
    }
    if (mode == 2) {
        int ix, iy; float fix, fiy;
        modf(gl_FragCoord.x, fix);
        modf(gl_FragCoord.y, fiy);
        ix = int(fix);
        iy = int(fiy);
        if (ix % 2 == 0 && iy % 2 ==0) color -= 0.5;
        else if (ix % 2 == 0 && iy % 2 == 1) color += 0.25;
        else if (ix % 2 == 1 && iy % 2 == 0) color += 0.0;
        else if (ix % 2 == 1 && iy % 2 == 1) color -= 0.25;
        if (color < 0.5) color = 0.0;
        else color = 1.0;
    }
    

    fragColor = vec4(color, color, color, 1.0);
}

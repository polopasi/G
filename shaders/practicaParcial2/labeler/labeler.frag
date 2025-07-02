#version 330 core

in vec4 gfrontColor;
out vec4 fragColor;

in vec3 uv;

void main()
{
    fragColor = gfrontColor;
    if(uv.z == 1){
    	if(uv.x >= 2 && uv.x <= 3 && uv.y >= 1 && uv.y <= 6) fragColor = vec4(0, 0, 0, 1);
    	if(uv.x >= 2 && uv.x <= 5 && uv.y >= 5 && uv.y <= 6) fragColor = vec4(0, 0, 0, 1);
    	if(uv.x >= 2 && uv.x <= 4 && uv.y >= 3 && uv.y <= 4) fragColor = vec4(0, 0, 0, 1);
    }
}

#version 330

out vec4 finalColor;

void main()
{
    vec3 color = vec3(.9, .6, .3);
    finalColor = vec4(color, 1.0);
}

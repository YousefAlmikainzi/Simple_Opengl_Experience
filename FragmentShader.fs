#version 330

uniform vec3 uColor;

in vec3 yColor;

out vec4 finalColor;


void main()
{
    vec3 color = (yColor.x + 1.0) * .5;
    finalColor = vec4(color, 1.0);
}

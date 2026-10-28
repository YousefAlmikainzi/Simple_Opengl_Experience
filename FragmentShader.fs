#version 330

uniform vec3 uColor;

in vec3 yColor;

out vec4 finalColor;


void main()
{
    float color = (yColor.y + 1.0) * .5;
    finalColor = vec4(vec3(color), 1.0);
}

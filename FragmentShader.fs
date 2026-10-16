#version 330

uniform vec3 uColor;

out vec4 finalColor;

void main()
{
    vec3 color = uColor;
    finalColor = vec4(color, 1.0);
}

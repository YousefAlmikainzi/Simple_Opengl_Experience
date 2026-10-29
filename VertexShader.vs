#version 330

layout(location = 0) in vec3 vertexPosition;
layout(location = 2) in vec3 vertexNormal;

out vec3 yColor;
out vec3 o_normal;

void main()
{
    yColor = vertexPosition;
    o_normal = normalize(vertexNormal);
    gl_Position = vec4(vertexPosition, 1.0);
}

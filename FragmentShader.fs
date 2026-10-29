#version 330

uniform vec3 uColor;

in vec3 yColor;
in vec3 o_normal;

out vec4 finalColor;


void main()
{
    vec3 lightdir = vec3(0.0,1.0,0.0);
    vec3 normals = normalize(o_normal);
    float diffFactor = max(dot(normals, lightdir), 0.0);


    float color = (yColor.y + 1.0) * .5;
    float ambient = .25;
    vec3 result = vec3(color) * diffFactor + ambient;
    finalColor = vec4(result, 1.0);
}

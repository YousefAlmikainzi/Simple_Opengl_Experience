#version 330

uniform vec3 uColor;

in vec3 yColor;
in vec3 o_normal;

out vec4 finalColor;


void main()
{
    vec3 lightdir = normalize(vec3(0.5,0.5,-0.5));
    vec3 normals = normalize(o_normal);

    float ambientFactor = .25;
    vec3 ambient = uColor * ambientFactor;

    float diffFactor = max(dot(normals, lightdir), 0.0)  * (1.0 - ambientFactor);

    vec3 result = uColor * diffFactor + ambient;
    finalColor = vec4(result, 1.0);
}

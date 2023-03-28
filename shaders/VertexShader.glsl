#version 460

in vec3 position;
in vec3 normal;

vec3 lightColor = vec3(1.0, 1.0, 1.0);
vec3 lightPos = vec3(-7.0, -7.0, 30.0);

uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 outColor;

void main()
{
    gl_Position = u_Projection * u_View * vec4(position, 1.0);
    float computeLight = dot(normalize(lightPos - position), normalize(normal));
    float c = clamp(computeLight, 0.0, 1.0);
    outColor = c * vec3(1.0, 1.0, 0.0);
}
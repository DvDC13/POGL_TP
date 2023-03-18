#version 460

layout (location = 0) in vec3 position;

uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 ourColor;

void main()
{
    gl_Position = u_Projection * u_View * vec4(position, 1.0);
    ourColor = vec3(0.5, 0.0, 0.0);
}
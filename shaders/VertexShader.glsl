#version 460

layout (location = 0) in vec3 position;

out vec3 ourColor;

void main()
{
    gl_Position = vec4(position, 1.0);
    ourColor = vec3(0.5, 0.0, 0.0);
}
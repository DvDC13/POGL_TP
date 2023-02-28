#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Vbo.h"
#include "Program.h"

MyGL::Program* program;
unsigned int Vao;

void display();
bool initGlut(int argc, char** argv);
bool initGlew();
bool init_gl();
bool init_shaders();

int main(int argc, char** argv)
{
    if (!initGlut(argc, argv))
    {
        std::cerr << "ERROR::GLUT::INIT_FAILED" << std::endl;
        return EXIT_FAILURE;
    }

    if (!initGlew())
    {
        std::cerr << "ERROR::GLEW::INIT_FAILED" << std::endl;
        return EXIT_FAILURE;
    }

    if (!init_gl())
    {
        std::cerr << "ERROR::GL::INIT_FAILED" << std::endl;
        return EXIT_FAILURE;
    }

    if (!init_shaders())
    {
        std::cerr << "ERROR::SHADERS::INIT_FAILED" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void display()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
}

bool initGlut(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitContextVersion(4, 5);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1024, 1024);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Test OpenGL - POGL");
    glutDisplayFunc(display);
    return true;
}

bool initGlew() { return glewInit() == GLEW_OK; }

bool init_gl()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    return true;
}

bool init_shaders()
{
    std::string vertex_shader_path = "shaders/VertexShader.glsl";
    std::string fragment_shader_path = "shaders/FragmentShader.glsl";
    program = MyGL::Program::make_program(vertex_shader_path, fragment_shader_path);
    if (!program)
    {
        std::cerr << "ERROR::SHADERS::INIT_FAILED" << std::endl;
        return false;
    }

    program->use();

    return true;
}
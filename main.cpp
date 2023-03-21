#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Error.h"
#include "Vao.h"
#include "Program.h"
#include "Structures.h"

MyGL::Program* program;
MyGL::Vao* Vao;

void display();
bool initGlut(int argc, char** argv);
bool initGlew();
bool init_gl();
bool init_shaders();
bool init_objects();
bool init_view();

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

    if (!init_objects())
    {
        std::cerr << "ERROR::OBJECTS::INIT_FAILED" << std::endl;
        return EXIT_FAILURE;
    }

    if (!init_view())
    {
        std::cerr << "ERROR::VIEW::INIT_FAILED" << std::endl;
        return EXIT_FAILURE;
    }

    glutMainLoop();

    Vao->destroy();
    program->delete_program();

    delete Vao;

    return EXIT_SUCCESS;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); CHECK_GL_ERROR();
    Vao->bind();
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3); CHECK_GL_ERROR();
    Vao->unbind();
    glutSwapBuffers();
}

bool initGlut(int argc, char** argv)
{
    glutInit(&argc, argv); CHECK_GL_ERROR();
    glutInitContextVersion(4, 5); CHECK_GL_ERROR();
    glutInitContextProfile(GLUT_CORE_PROFILE); CHECK_GL_ERROR();
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); CHECK_GL_ERROR();
    glutInitWindowSize(1024, 1024); CHECK_GL_ERROR();
    glutInitWindowPosition(10, 10); CHECK_GL_ERROR();
    glutCreateWindow("Test OpenGL - POGL - David Chemaly"); CHECK_GL_ERROR();
    glutDisplayFunc(display); CHECK_GL_ERROR();
    return true;
}

bool initGlew() { return glewInit() == GLEW_OK; }

bool init_gl()
{
    glEnable(GL_DEPTH_TEST); CHECK_GL_ERROR();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); CHECK_GL_ERROR();
    glEnable(GL_CULL_FACE); CHECK_GL_ERROR();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); CHECK_GL_ERROR();
    return true;
}

bool init_shaders()
{
    std::string vertex_shader_path = "/home/david/Desktop/Image/POGL/POGL_TP/shaders/VertexShader.glsl";
    std::string fragment_shader_path = "/home/david/Desktop/Image/POGL/POGL_TP/shaders/FragmentShader.glsl";
    program = MyGL::Program::make_program(vertex_shader_path, fragment_shader_path);
    if (!program)
    {
        std::cerr << "ERROR::SHADERS::INIT_FAILED" << std::endl;
        return false;
    }

    program->use();

    return true;
}

bool init_objects()
{
    Vao = new MyGL::Vao();
    Vao->bind();

    MyGL::Vbo Vbo;
    Vbo.bind();
    Vbo.setData(vertices.data(), vertices.size() * sizeof(float), GL_STATIC_DRAW); CHECK_GL_ERROR();

    MyGL::Vbl Vbl;
    Vbl.push<float>(3);

    Vao->addBuffer(Vbo, Vbl);

    Vao->unbind();

    Vbo.unbind();
    Vbo.destroy();
    return true;
}

bool init_view()
{
    MyGL::Matrix4 matrix = MyGL::Matrix4::Identity();

    MyGL::look_at(matrix, 0, 0, 5, 0, 0, 0, 0, 1, 0);
    program->set_uniform_Mat4fv("u_View", matrix);

    MyGL::frustum(matrix, -1, 1, -1, 1, 1, 100);
    program->set_uniform_Mat4fv("u_Projection", matrix);

    return true;
}
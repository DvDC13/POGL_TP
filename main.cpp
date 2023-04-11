#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Error.h"
#include "Vao.h"
#include "Program.h"
#include "Structures.h"
#include "Bunny_dec.h"

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
    glDrawArrays(GL_TRIANGLES, 0, vertex_buffer_data_bunny.size() / 3); CHECK_GL_ERROR();
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
    glutReshapeFunc([](int w, int h) { glViewport(0, 0, w, h); CHECK_GL_ERROR(); }); CHECK_GL_ERROR();
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
    int max_vbo = 0;
    int nb_vbo = 0;
    int index = 0;

    Vao = new MyGL::Vao();
    Vao->bind();

    GLint position = glGetAttribLocation(program->get_program_id(), "position"); CHECK_GL_ERROR();
    GLint normalPosition = glGetAttribLocation(program->get_program_id(), "normal"); CHECK_GL_ERROR();

    GLuint vbos[max_vbo];

    if (position != -1) nb_vbo++;
    if (normalPosition != -1) nb_vbo++;

    glGenBuffers(nb_vbo, vbos); CHECK_GL_ERROR();

    if (position != -1)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbos[index++]); CHECK_GL_ERROR();
        glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data_bunny.size() * sizeof(float), vertex_buffer_data_bunny.data(), GL_STATIC_DRAW); CHECK_GL_ERROR();
        glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 0, 0); CHECK_GL_ERROR();
        glEnableVertexAttribArray(position); CHECK_GL_ERROR();
    }

    if (normalPosition != -1)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbos[index++]); CHECK_GL_ERROR();
        glBufferData(GL_ARRAY_BUFFER, normal_smooth_buffer_data_bunny.size() * sizeof(float), normal_smooth_buffer_data_bunny.data(), GL_STATIC_DRAW); CHECK_GL_ERROR();
        glVertexAttribPointer(normalPosition, 3, GL_FLOAT, GL_FALSE, 0, 0); CHECK_GL_ERROR();
        glEnableVertexAttribArray(normalPosition); CHECK_GL_ERROR();
    }

    Vao->unbind();
    
    return true;
}

bool init_view()
{
    MyGL::Matrix4 matrix = MyGL::Matrix4::Identity();

    MyGL::look_at(matrix, 0, 0.25, 1, 0, 0, 0, 0, 1, 0);
    program->set_uniform_Mat4fv("u_View", matrix);

    MyGL::frustum(matrix, -1, 1, -1, 1, 1, 100);
    program->set_uniform_Mat4fv("u_Projection", matrix);

    return true;
}
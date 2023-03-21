#pragma once

#include <GL/glew.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "Error.h"
#include "Matrix4.h"

namespace MyGL
{
    class Program
    {
    public:
        struct Shaders
        {
            std::string vertex_shader_path;
            std::string fragment_shader_path;
        };

    public:
        Program(); 

        static Program* make_program(std::string& vertex_shader_path, std::string& fragment_shader_path);
        char* get_log();
        bool is_ready();
        void use();

        inline unsigned int get_program_id() const { return m_ProgramID; }

        void set_uniform_Mat4fv(const std::string& name, const Matrix4& matrix);

        void delete_program();

    private:
        Shaders storeShaders(std::string& vertex_shader_path, std::string& fragment_shader_path);
        bool is_shader_ready(unsigned int shader_id);
        char* get_shader_log(unsigned int shader_id);
        unsigned int compileShader(unsigned int type, const std::string& source);
        int getUniformLocation(const std::string& name);

    private:
        unsigned int m_ProgramID;
        std::unordered_map<std::string, int> m_UniformLocationCache;
    };
}
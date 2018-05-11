/** ---------------------------------------------------------------------------
 * @file: shader.cpp
 *
 * Copyright (c) 2017 Yann Herklotz Grave <ymherklotz@gmail.com>
 * MIT License, see LICENSE file for more details.
 * ----------------------------------------------------------------------------
 */

#include "shader.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <vector>

namespace
{

void checkCompileStatus(unsigned shader);
void checkLinkStatus(unsigned program);
std::string loadFile(std::string file_name);

} // namespace

Shader::Shader(std::string vertex_path, std::string fragment_path)
{
    std::string vsource = loadFile(vertex_path);
    std::string fsource = loadFile(fragment_path);

    const char *vertex_source_c   = vsource.c_str();
    const char *fragment_source_c = fsource.c_str();

    unsigned vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_source_c, NULL);
    glCompileShader(vertex_shader);
    checkCompileStatus(vertex_shader);

    unsigned fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_source_c, NULL);
    glCompileShader(fragment_shader);
    checkCompileStatus(fragment_shader);

    program_id_ = glCreateProgram();
    glAttachShader(program_id_, vertex_shader);
    glAttachShader(program_id_, fragment_shader);
    glLinkProgram(program_id_);
    checkLinkStatus(program_id_);

    glDetachShader(program_id_, vertex_shader);
    glDetachShader(program_id_, fragment_shader);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

Shader::~Shader()
{
    /// cleans up all the shaders and the program
    if (program_id_ != 0) {
        glDeleteProgram(program_id_);
    }
}

void Shader::use() const
{
    glUseProgram(program_id_);
}

void Shader::setUniform(std::string name, int value) const
{
    glUniform1i(getUniformLocation(name), static_cast<GLint>(value));
}

void Shader::setUniform(std::string name, float value) const
{
    glUniform1f(getUniformLocation(name), static_cast<GLfloat>(value));
}

void Shader::setUniform(std::string name, const glm::mat4 &matrix) const
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &(matrix[0][0]));
}

void Shader::setUniform(std::string name, const glm::vec4 &vec) const
{
    glUniform4f(getUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
}

GLint Shader::getUniformLocation(std::string uniform_name) const
{
    GLuint location = glGetUniformLocation(program_id_, uniform_name.c_str());
    if (location == GL_INVALID_INDEX) {
        throw std::runtime_error("'" + uniform_name + "' not found");
    }
    return location;
}

namespace
{

void checkCompileStatus(unsigned shader)
{
    int success;
    char infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
    assert(success);
}

void checkLinkStatus(unsigned program)
{
    int success;
    char infoLog[512];

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
    assert(success);
}

std::string loadFile(std::string file_name)
{
    std::ifstream t(file_name);
    std::string str;

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)),
               std::istreambuf_iterator<char>());

    return str;
}

} // namespace

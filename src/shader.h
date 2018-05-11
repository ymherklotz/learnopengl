/** ---------------------------------------------------------------------------
 * @file: shader.h
 *
 * Copyright (c) 2017 Yann Herklotz Grave <ymherklotz@gmail.com>
 * MIT License, see LICENSE file for more details.
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

class Shader
{
public:
    Shader(std::string vertex_path, std::string fragment_path);
    Shader(const Shader &) = delete;
    Shader(Shader &&)      = delete;
    ~Shader();

    Shader &operator=(const Shader &) = delete;
    Shader &operator=(Shader &&) = delete;

    /// compiles vertex and fragment shader
    void use() const;

    /// set uniforms of different type
    void setUniform(std::string name, int value) const;
    void setUniform(std::string name, float value) const;
    void setUniform(std::string name, const glm::mat4 &matrix) const;
    void setUniform(std::string name, const glm::vec4 &vec) const;

private:
    /// compiled shader program id
    GLuint program_id_ = 0;

    GLint getUniformLocation(std::string uniform_name) const;
};

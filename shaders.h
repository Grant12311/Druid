#ifndef DRUID_SHADERS_H
#define DRUID_SHADERS_H

#include <fstream>
#include <sstream>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "guards.h"

namespace Druid
{
    struct ShaderProgramSource
    {
        std::string VertexSource;
        std::string FragmentSource;
    };

    struct Shader
    {
        unsigned int id;

        std::unordered_map<const char*, unsigned int> uniformLocations;

        void fillUniform(const char* a_name, const int a_value);
        void fillUniform(const char* a_name, const float a_value1, const float a_value2, const float a_value3);
        void fillUniform(const char* a_name, const float a_value1, const float a_value2, const float a_value3, const float a_value4);
        void fillUniform(const char* a_name, const float a_value);
        void fillUniform(const char* a_name, const int a_count, const bool a_transpose, const glm::mat4 &a_matrix);

        void use();
        void deactivate();

        Shader(const char* a_path);
        Shader(const char* a_vertexShader, const char* a_fragmentShader);
        ~Shader();
    private:
        ShaderProgramSource parseShader(const std::string &a_filepath);
        unsigned int compileSource(const unsigned int a_type, const std::string &a_source);
    };

    void Shader::fillUniform(const char* a_name, const int a_value)
    {
        if (this->uniformLocations.find(a_name) == this->uniformLocations.end())
        {
            glCall(this->uniformLocations[a_name] = glGetUniformLocation(this->id, a_name));
        }
        glCall(glUniform1i(this->uniformLocations[a_name], a_value));
    }

    void Shader::fillUniform(const char* a_name, const float a_value1, const float a_value2, const float a_value3)
    {
        if (this->uniformLocations.find(a_name) == this->uniformLocations.end())
        {
            glCall(this->uniformLocations[a_name] = glGetUniformLocation(this->id, a_name));
        }
        glCall(glUniform3f(this->uniformLocations[a_name], a_value1, a_value2, a_value3));
    }

    void Shader::fillUniform(const char* a_name, const float a_value1, const float a_value2, const float a_value3, const float a_value4)
    {
        if (this->uniformLocations.find(a_name) == this->uniformLocations.end())
        {
            glCall(this->uniformLocations[a_name] = glGetUniformLocation(this->id, a_name));
        }
        glCall(glUniform4f(this->uniformLocations[a_name], a_value1, a_value2, a_value3, a_value4));
    }

    void Shader::fillUniform(const char* a_name, const float a_value)
    {
        if (this->uniformLocations.find(a_name) == this->uniformLocations.end())
        {
            glCall(this->uniformLocations[a_name] = glGetUniformLocation(this->id, a_name));
        }
        glCall(glUniform1f(this->uniformLocations[a_name], a_value));
    }

    void Shader::fillUniform(const char* a_name, const int a_count, const bool a_transpose, const glm::mat4 &a_matrix)
    {
        if (this->uniformLocations.find(a_name) == this->uniformLocations.end())
        {
            glCall(this->uniformLocations[a_name] = glGetUniformLocation(this->id, a_name));
        }
        glCall(glUniformMatrix4fv(this->uniformLocations[a_name], a_count, a_transpose, glm::value_ptr(a_matrix)));
    }

    void Shader::use()
    {
        glCall(glUseProgram(this->id));
    }

    void Shader::deactivate()
    {
        glCall(glUseProgram(0));
    }

    Shader::Shader(const char* a_path)
    {
        ShaderProgramSource source = this->parseShader(a_path);

        glCall(this->id = glCreateProgram());
        glCall(unsigned int vs = this->compileSource(GL_VERTEX_SHADER, source.VertexSource));
        glCall(unsigned int fs = this->compileSource(GL_FRAGMENT_SHADER, source.FragmentSource));

        glCall(glAttachShader(this->id, vs));
        glCall(glAttachShader(this->id, fs));
        glCall(glLinkProgram(this->id));
        glCall(glValidateProgram(this->id));

        glCall(glDeleteShader(vs));
        glCall(glDeleteShader(fs));
    }

    Shader::Shader(const char* a_vertexShader, const char* a_fragmentShader)
    {
        ShaderProgramSource source{a_vertexShader, a_fragmentShader};

        glCall(this->id = glCreateProgram());
        glCall(unsigned int vs = this->compileSource(GL_VERTEX_SHADER, source.VertexSource));
        glCall(unsigned int fs = this->compileSource(GL_FRAGMENT_SHADER, source.FragmentSource));

        glCall(glAttachShader(this->id, vs));
        glCall(glAttachShader(this->id, fs));
        glCall(glLinkProgram(this->id));
        glCall(glValidateProgram(this->id));

        glCall(glDeleteShader(vs));
        glCall(glDeleteShader(fs));
    }

    Shader::~Shader()
    {
        glCall(glDeleteProgram(this->id));
    }

    ShaderProgramSource Shader::parseShader(const std::string &a_filepath)
    {
        std::ifstream stream(a_filepath);

        enum class ShaderType
        {
            NONE = -1,
            VERTEX = 0,
            FRAGMENT = 1
        };

        ShaderType type = ShaderType::NONE;

        std::string line;
        std::stringstream ss[2];
        while (getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                    type = ShaderType::VERTEX;
                else if (line.find("fragment") != std::string::npos)
                    type = ShaderType::FRAGMENT;
            }else{
                ss[(int)type] << line << "\n";
            }
        }

        return {ss[0].str(), ss[1].str()};
    }

    unsigned int Shader::compileSource(const unsigned int a_type, const std::string &a_source)
    {
        glCall(unsigned int id = glCreateShader(a_type));
        const char* src = a_source.c_str();
        glCall(glShaderSource(id, 1, &src, nullptr));
        glCall(glCompileShader(id));

        int result;
        glCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

        if (result == GL_FALSE)
        {
            int length;
            glCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
            char* message = (char*)alloca(length * sizeof(char));
            glCall(glGetShaderInfoLog(id, length, &length, message));
            std::cout << "Failed to compile shader of type " << a_type << "!" <<std::endl;
            std::cout << message << std::endl;
            glCall(glDeleteShader(id));
            return 0;
        }

        return id;
    }
}

#endif

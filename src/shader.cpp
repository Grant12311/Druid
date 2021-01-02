#include <iostream>
#include <string>
#include <algorithm>

#include <Druid/gl_include.h>

#include <Druid/shader.h>

namespace Druid
{
    void Shader::fillUniform(const char* a_name, const int a_value)
    {
        glCall(glUniform1i(this->uniformLocations[a_name], a_value));
    }

    void Shader::fillUniform(const char* a_name, const float a_value)
    {
        glCall(glUniform1f(this->uniformLocations[a_name], a_value));
    }

    void Shader::fillUniform(const char* a_name, const float a_value1, const float a_value2, const float a_value3)
    {
        glCall(glUniform3f(this->uniformLocations[a_name], a_value1, a_value2, a_value3));
    }

    void Shader::fillUniform(const char* a_name, const float a_value1, const float a_value2, const float a_value3, const float a_value4)
    {
        glCall(glUniform4f(this->uniformLocations[a_name], a_value1, a_value2, a_value3, a_value4));
    }

    void Shader::fillUniform(const char* a_name, const int a_count, const bool a_transpose, const glm::mat4 &a_matrix)
    {
        glCall(glUniformMatrix4fv(this->uniformLocations[a_name], a_count, a_transpose, glm::value_ptr(a_matrix)));
    }

    void Shader::bind() const
    {
        glCall(glUseProgram(this->id));
    }

    void Shader::unbind() const
    {
        glCall(glUseProgram(0));
    }

    Shader::Shader(const char* a_path)
    {
        ShaderProgramSource source = this->parseShader(a_path);

        this->genShader(source);
        this->loadUniforms();
    }

    Shader::Shader(const char* a_vertexShader, const char* a_fragmentShader)
    {
        ShaderProgramSource source{a_vertexShader, a_fragmentShader};

        this->genShader(source);
        this->loadUniforms();
    }

    Shader::~Shader()
    {
        glCall(glDeleteProgram(this->id));
    }

    void Shader::loadUniforms()
    {
        int count;
        glGetProgramiv(this->id, GL_ACTIVE_UNIFORMS, &count);

        int length;
        int size;
        unsigned int type;

        for (int i = 0; i < count; i++)
        {
            char name[256];

            glGetActiveUniform(this->id, i, 256, &length, &size, &type, name);

            if (this->uniformLocations.find(name) == this->uniformLocations.end())
            {
                this->uniformLocations[name] = glGetUniformLocation(this->id, name);
            }
        }
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
        glCall(unsigned int toReturn = glCreateShader(a_type));
        const char* src = a_source.c_str();
        glCall(glShaderSource(toReturn, 1, &src, nullptr));
        glCall(glCompileShader(toReturn));

        int result;
        glCall(glGetShaderiv(toReturn, GL_COMPILE_STATUS, &result));

        if (result == GL_FALSE)
        {
            int length;
            glCall(glGetShaderiv(toReturn, GL_INFO_LOG_LENGTH, &length));
            char* message = (char*)alloca(length * sizeof(char));
            glCall(glGetShaderInfoLog(toReturn, length, &length, message));
            std::cout << "Failed to compile shader of type " << a_type << "!" <<std::endl;
            std::cout << message << std::endl;
            glCall(glDeleteShader(toReturn));
            return 0;
        }

        return toReturn;
    }

    void Shader::genShader(const ShaderProgramSource &a_sources)
    {
        glCall(this->id = glCreateProgram());
        glCall(unsigned int vs = this->compileSource(GL_VERTEX_SHADER, a_sources.VertexSource));
        glCall(unsigned int fs = this->compileSource(GL_FRAGMENT_SHADER, a_sources.FragmentSource));

        glCall(glAttachShader(this->id, vs));
        glCall(glAttachShader(this->id, fs));
        glCall(glLinkProgram(this->id));
        glCall(glValidateProgram(this->id));

        glCall(glDeleteShader(vs));
        glCall(glDeleteShader(fs));
    }
}

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

#include <Druid/gl_include.h>

#include <Druid/shader.h>

namespace Druid
{
    Shader::Shader(const LoadFromFileType /*a_source*/, const std::string &a_path)
    {
        std::ifstream infile(a_path);
        const ProgramSource source = this->m_parseUnifiedShader(infile);

        this->m_genShader(source);
        this->m_loadUniforms();
    }

    Shader::Shader(const LoadFromStringType /*a_source*/, const std::string &a_source)
    {
        std::stringstream ss;
        ss << a_source;
        const ProgramSource source = this->m_parseUnifiedShader(ss);

        this->m_genShader(source);
        this->m_loadUniforms();
    }

    Shader::Shader(const LoadFromFileType /*a_source*/, const std::string &a_vertexPath, const std::string &a_fragmentPath)
    {
        ProgramSource source;

        std::ifstream infile;
        std::string line;

        infile.open(a_vertexPath);
        while (std::getline(infile, line))
        {
            source.vertexSource += line + '\n';
        }

        infile.open(a_fragmentPath);
        while (std::getline(infile, line))
        {
            source.fragmentSource += line + '\n';
        }

        this->m_genShader(source);
        this->m_loadUniforms();
    }

    Shader::Shader(const LoadFromStringType /*a_source*/, const std::string &a_vertexSource, const std::string &a_fragmentSource)
    {
        this->m_genShader({a_vertexSource, a_fragmentSource});
        this->m_loadUniforms();
    }

    Shader::Shader(Shader &&a_other) :
        m_id(a_other.m_id), m_uniformLocations(std::move(a_other.m_uniformLocations))
    {
        a_other.m_id = 0;
    }

    Shader::~Shader()
    {
        glCall(glDeleteProgram(this->m_id));
    }

    void Shader::bind() const
    {
        glCall(glUseProgram(this->m_id));
    }

    void Shader::unbind()
    {
        glCall(glUseProgram(0));
    }

    void Shader::fillUniform(const char* const a_name, const int a_value)
    {
        glCall(glUniform1i(this->m_uniformLocations[a_name], a_value));
    }

    void Shader::fillUniform(const char* const a_name, const float a_value)
    {
        glCall(glUniform1f(this->m_uniformLocations[a_name], a_value));
    }

    void Shader::fillUniform(const char* const a_name, const float a_value1, const float a_value2, const float a_value3)
    {
        glCall(glUniform3f(this->m_uniformLocations[a_name], a_value1, a_value2, a_value3));
    }

    void Shader::fillUniform(const char* const a_name, const float a_value1, const float a_value2, const float a_value3, const float a_value4)
    {
        glCall(glUniform4f(this->m_uniformLocations[a_name], a_value1, a_value2, a_value3, a_value4));
    }

    void Shader::fillUniform(const char* const a_name, const bool a_transpose, const glm::mat4 &a_matrix)
    {
        glCall(glUniformMatrix4fv(this->m_uniformLocations[a_name], 1, a_transpose, glm::value_ptr(a_matrix)));
    }

    Shader& Shader::operator=(Shader &&a_rhs)
    {
        if (this == &a_rhs)
            return *this;

        glCall(glDeleteProgram(this->m_id));

        this->m_id = a_rhs.m_id;
        this->m_uniformLocations = std::move(a_rhs.m_uniformLocations);

        a_rhs.m_id = 0;

        return *this;
    }

    [[nodiscard]]
    Shader::ProgramSource Shader::m_parseUnifiedShader(std::istream &a_source) const
    {
        enum class ShaderType
        {
            none = -1,
            vertex,
            fragment
        };

        ShaderType type = ShaderType::none;

        std::string line;
        std::array<std::stringstream, 2> streams;
        while (getline(a_source, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                    type = ShaderType::vertex;
                else if (line.find("fragment") != std::string::npos)
                    type = ShaderType::fragment;
            }else{
                streams[static_cast<size_t>(type)] << line << '\n';
            }
        }

        return {streams[0].str(), streams[1].str()};
    }

    void Shader::m_loadUniforms()
    {
        int count;
        glGetProgramiv(this->m_id, GL_ACTIVE_UNIFORMS, &count);

        int length;
        int size;
        unsigned int type;

        for (int i = 0; i < count; i++)
        {
            char name[256];

            glGetActiveUniform(this->m_id, i, 256, &length, &size, &type, name);

            if (this->m_uniformLocations.find(name) == this->m_uniformLocations.end())
            {
                this->m_uniformLocations[name] = glGetUniformLocation(this->m_id, name);

                if (size > 1)
                {
                    const std::string coreName = std::string(name).substr(0, std::string(name).find('[') + 1);

                    for (int i = 1; i < size; i++)
                    {
                        const std::string fullName = coreName + std::to_string(i) + std::string("]");
                        this->m_uniformLocations[fullName] = glGetUniformLocation(this->m_id, fullName.c_str());
                    }
                }
            }
        }
    }

    void Shader::m_genShader(const ProgramSource &a_sources)
    {
        glCall(this->m_id = glCreateProgram());
        glCall(const unsigned int vs = this->m_compileSource(GL_VERTEX_SHADER, a_sources.vertexSource));
        glCall(const unsigned int fs = this->m_compileSource(GL_FRAGMENT_SHADER, a_sources.fragmentSource));

        glCall(glAttachShader(this->m_id, vs));
        glCall(glAttachShader(this->m_id, fs));
        glCall(glLinkProgram(this->m_id));
        glCall(glValidateProgram(this->m_id));

        glCall(glDeleteShader(vs));
        glCall(glDeleteShader(fs));
    }

    [[nodiscard]]
    unsigned int Shader::m_compileSource(const unsigned int a_type, const std::string &a_source)
    {
        glCall(unsigned int toReturn = glCreateShader(a_type));
        const char* const src = a_source.c_str();
        glCall(glShaderSource(toReturn, 1, &src, nullptr));
        glCall(glCompileShader(toReturn));

        int result;
        glCall(glGetShaderiv(toReturn, GL_COMPILE_STATUS, &result));

        if (!result)
        {
            int length;
            glCall(glGetShaderiv(toReturn, GL_INFO_LOG_LENGTH, &length));
            char* const message = new char[length];
            glCall(glGetShaderInfoLog(toReturn, length, &length, message));
            std::cerr << "Failed to compile shader of type " << a_type << "!\n";
            std::cerr << message << '\n';
            glCall(glDeleteShader(toReturn));
            delete message;
            return 0;
        }

        return toReturn;
    }
}

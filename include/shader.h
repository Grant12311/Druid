#ifndef DRUID_SHADERS_H
#define DRUID_SHADERS_H

#include <fstream>
#include <sstream>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "guard.h"

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
        void fillUniform(const char* a_name, const float a_value);
        void fillUniform(const char* a_name, const float a_value1, const float a_value2, const float a_value3);
        void fillUniform(const char* a_name, const float a_value1, const float a_value2, const float a_value3, const float a_value4);
        void fillUniform(const char* a_name, const int a_count, const bool a_transpose, const glm::mat4 &a_matrix);

        void use() const;
        void deactivate() const;

        Shader(const char* a_path);
        Shader(const char* a_vertexShader, const char* a_fragmentShader);
        ~Shader();
    private:
        ShaderProgramSource parseShader(const std::string &a_filepath);
        unsigned int compileSource(const unsigned int a_type, const std::string &a_source);
    };
}

#endif

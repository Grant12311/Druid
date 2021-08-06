#ifndef DRUID_SHADERS_H
#define DRUID_SHADERS_H

#include <string>
#include <unordered_map>

#include <glm/mat4x4.hpp>

#include "guard.h"

namespace Druid
{
    struct LoadFromStringType {};
    constexpr LoadFromStringType loadFromString;

    struct LoadFromFileType {};
    constexpr LoadFromStringType loadFromFile;

    class Shader
    {
    public:
        Shader(const LoadFromFileType /*a_source*/, const std::string &a_path);
        Shader(const LoadFromStringType /*a_source*/, const std::string &a_source);
        Shader(const LoadFromFileType /*a_source*/, const std::string &a_vertexPath, const std::string &a_fragmentPath);
        Shader(const LoadFromStringType /*a_source*/, const std::string &a_vertexSource, const std::string &a_fragmentSource);
        ~Shader();

        void bind() const;
        static void unbind();

        void fillUniform(const char* const a_name, const int a_value);
        void fillUniform(const char* const a_name, const float a_value);
        void fillUniform(const char* const a_name, const float a_value1, const float a_value2, const float a_value3);
        void fillUniform(const char* const a_name, const float a_value1, const float a_value2, const float a_value3, const float a_value4);
        void fillUniform(const char* const a_name, const bool a_transpose, const glm::mat4 &a_matrix);
    private:
        struct ProgramSource
        {
            std::string vertexSource;
            std::string fragmentSource;
        };

        unsigned int m_id;
        std::unordered_map<std::string, unsigned int> m_uniformLocations;

        [[nodiscard]]
        ProgramSource m_parseUnifiedShader(std::istream &a_source) const;
        void m_loadUniforms();
        void m_genShader(const ProgramSource &a_sources);
        [[nodiscard]]
        unsigned int m_compileSource(const unsigned int a_type, const std::string &a_source);
    };
}

#endif

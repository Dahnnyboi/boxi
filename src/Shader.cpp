#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath) {
    // vertex shader
    std::string vertexCode = loadShaderSource(vertexFilePath);
    
    // fragment shader
    std::string fragmentCode = loadShaderSource(fragmentFilePath); 
    
    const char* vertexShaderSource = vertexCode.c_str();
    const char* fragmentShaderSource = fragmentCode.c_str();
    m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
    m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // vertex shader compilation
    glShaderSource(m_VertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(m_VertexShader);
    checkCompileShaderError(m_VertexShader, "vertex");
    
    // fragment shader compilation
    glShaderSource(m_FragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(m_FragmentShader);
    checkCompileShaderError(m_FragmentShader, "fragment");
    
    // Creation of program
    m_ProgramId = glCreateProgram();
    glAttachShader(m_ProgramId, m_VertexShader);
    glAttachShader(m_ProgramId, m_FragmentShader);
    glLinkProgram(m_ProgramId);
    checkLinkProgramError();

    glDeleteShader(m_VertexShader);
    glDeleteShader(m_FragmentShader);
}

void Shader::useProgram() {
    // use program
    glUseProgram(m_ProgramId);
}

void Shader::deleteProgram() {
    // delete program
    glDeleteProgram(m_ProgramId);
}

void Shader::setFloat(const std::string& name, float value) {
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setInt(const std::string& name, int value) {
    glUniform1i(getUniformLocation(name), value);
}

std::string Shader::loadShaderSource(const char* filepath)
{
    std::ifstream file(filepath);

    if (!file.is_open())
    {
        std::cout << "Failed to open shader file: " << filepath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void Shader::checkCompileShaderError(unsigned int shader, const char* type) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Error shader compilation on" << type << "\n" << infoLog << std::endl;
    }
}

void Shader::checkLinkProgramError() {
    int success;
    char infoLog[512];
    glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_ProgramId, 512, NULL, infoLog);
        std::cout << "Error program linking\n" << infoLog << std::endl;
    }
}

int Shader::getUniformLocation(const std::string& name) {
    if (m_UniformCache.find(name) != m_UniformCache.end()) 
        return m_UniformCache[name];

    int location = glGetUniformLocation(m_ProgramId, name.c_str());
    m_UniformCache[name] = location;
    return location;
}
#pragma once
#include <string>
#include <unordered_map>

class Shader {
  public:
    Shader(const char* vertexFilePath, const char* fragmentFilePath);
    void useProgram();
    void deleteProgram();

    void setFloat(const std::string& name, float value);
    void setInt(const std::string& name, int value);

  private:
    unsigned int m_ProgramId;
    unsigned int m_VertexShader;
    unsigned int m_FragmentShader;
    std::unordered_map<std::string, int> m_UniformCache;

    std::string loadShaderSource(const char* filepath);
    void checkCompileShaderError(unsigned int shader, const char* type);
    void checkLinkProgramError();
    int getUniformLocation(const std::string& name);
};
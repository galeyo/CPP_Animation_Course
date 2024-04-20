#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
	bool LoadShaders(std::string vertexShaderFilename, std::string fragmentShaderFilename);	
	void Use();
	void Cleanup();

private:
	GLuint ReadShader(std::string shaderFilename, GLuint shaderType);

private:
	GLuint m_ShaderProgram = 0;
};
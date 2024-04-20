#include <fstream>
#include "Shader.h"
#include "../Logger.h"

bool Shader::LoadShaders(std::string vertexShaderFilename, std::string fragmentShaderFilename)
{
	GLuint vertexShader = ReadShader(vertexShaderFilename, GL_VERTEX_SHADER);
	if (!vertexShader)
	{
		return false;
	}

	GLuint fragmentShader = ReadShader(fragmentShaderFilename, GL_FRAGMENT_SHADER);
	if (!fragmentShader)
	{
		return false;
	}

	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, vertexShader);
	glAttachShader(m_ShaderProgram, fragmentShader);
	glLinkProgram(m_ShaderProgram);
	GLint isProgramLinked;
	glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &isProgramLinked);
	if (!isProgramLinked)
	{
		GLchar errorLog[512]{};
		GLint size = 0;
		glGetProgramInfoLog(m_ShaderProgram, 512, &size, errorLog);
		errorLog[511] = '\0';
		Logger::Log(Logger::ERROR, "%s: Error while shader linking: %s\n", __FUNCTION__, errorLog);
		return false;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return true;
}

void Shader::Use()
{
	glUseProgram(m_ShaderProgram);
}

void Shader::Cleanup()
{
	glDeleteProgram(m_ShaderProgram);
}

GLuint Shader::ReadShader(std::string shaderFilename, GLuint shaderType)
{
	GLuint shader;
	std::string shaderAsText;
	std::ifstream inFile(shaderFilename);
	if (inFile.is_open())
	{
		inFile.seekg(0, std::ios::end);
		shaderAsText.reserve(inFile.tellg());
		inFile.seekg(0, std::ios::beg);
		shaderAsText.assign((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
		inFile.close();
	}
	else
	{
		return 0;
	}

	if (inFile.bad() || inFile.fail())
	{
		inFile.close();
		return 0;
	}
	const char * shaderSource = shaderAsText.c_str();
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, (const GLchar**) &shaderSource, 0);
	glCompileShader(shader);
	GLint isShaderCompiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isShaderCompiled);
	if (!isShaderCompiled)
	{
		GLchar errorLog[512]{};
		GLint size = 0;
		glGetShaderInfoLog(m_ShaderProgram, 512, &size, errorLog);
		errorLog[511] = '\0';
		Logger::Log(Logger::ERROR, "%s: Error while shader compile: %s\n", __FUNCTION__, errorLog);
		return 0;
	}
	return shader;
}

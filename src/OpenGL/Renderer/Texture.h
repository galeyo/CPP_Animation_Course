#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture
{
public: 
	bool LoadTexture(std::string textureFilename);
	void Bind();
	void Unbind();
	void Cleanup();

private:
	GLuint m_Texture = 0;
	int m_TextureWidth = 0;
	int m_TextureHeight = 0;
	int m_NumberOfChannels = 0;
};
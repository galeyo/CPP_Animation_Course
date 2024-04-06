#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Framebuffer
{
public:
	bool Init(uint32_t width, uint32_t height);
	bool Resize(uint32_t newWidth, uint32_t newHeight);
	void Bind();
	void Unbind();
	void DrawToScreen();
	void Cleanup();

private:
	bool CheckComplete();

private:
	uint32_t m_BufferWidth = 0;
	uint32_t m_BufferHeight = 0;
	GLuint m_Buffer = 0;
	GLuint m_ColorTexture = 0;
	GLuint m_DepthBuffer = 0;
};
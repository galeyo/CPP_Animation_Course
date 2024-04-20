#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
// Glad header must be before GLFW 
// as it's change GLFW behavior and 
// will not include basic OpenGL headers 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Logger.h"
#include "Framebuffer.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Shader.h"


class OGLRenderer 
{
public:
	bool Init(uint32_t width, uint32_t height);
	void SetSize(uint32_t width, uint32_t height);
	void Cleanup();
	void UploadData(OGLMesh vertexData);
	void Draw();

private:
	Shader m_Shader{};
	Framebuffer m_Framebuffer{};
	VertexBuffer m_VertexBuffer{};
	Texture m_Texture{};
	uint32_t m_TriangleCount = 0;
};
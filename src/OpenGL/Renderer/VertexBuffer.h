#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OGLRenderData.h"

class VertexBuffer
{
public:
	void Init();
	void UploadData(OGLMesh vertexData);
	void Bind();
	void Unbind();
	void Draw(GLuint mode, uint32_t start, uint32_t num);
	void Cleanup();

private:
	GLuint m_VAO = 0;
	GLuint m_VertexVBO = 0;
};
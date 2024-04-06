#include "VertexBuffer.h"

void VertexBuffer::Init()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VertexVBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexVBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OGLVertex), (void*) offsetof(OGLVertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(OGLVertex), (void*) offsetof(OGLVertex, uv));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VertexBuffer::UploadData(OGLMesh vertexData)
{
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexVBO);
	glBufferData(GL_ARRAY_BUFFER, vertexData.vertices.size() * sizeof(OGLVertex), &vertexData.vertices.at(0), GL_DYNAMIC_DRAW);
	glBindVertexArray(0);
}

void VertexBuffer::Bind()
{
	glBindVertexArray(m_VAO);
}

void VertexBuffer::Unbind()
{
	glBindVertexArray(0);
}

void VertexBuffer::Draw(GLuint mode, uint32_t start, uint32_t num)
{
	glDrawArrays(mode, start, num);
}

void VertexBuffer::Cleanup()
{
	glDeleteBuffers(1, &m_VertexVBO);
	glDeleteVertexArrays(1, &m_VAO);
}

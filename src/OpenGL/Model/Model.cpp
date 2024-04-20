#include "Model.h"

static const int MODEL_VERTEX_COUNT = 6;

void Model::Init()
{
	m_VertexData.vertices.reserve(MODEL_VERTEX_COUNT);

	m_VertexData.vertices.push_back(OGLVertex{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0, 0.0) });
	m_VertexData.vertices.push_back(OGLVertex{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0, 1.0) });
	m_VertexData.vertices.push_back(OGLVertex{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0, 1.0) });
	m_VertexData.vertices.push_back(OGLVertex{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0, 0.0) });
	m_VertexData.vertices.push_back(OGLVertex{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.0, 0.0) });
	m_VertexData.vertices.push_back(OGLVertex{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0, 1.0) });
	//m_VertexData.vertices[0].position = glm::vec3(-0.5f, -0.5f, 0.5f);
	//m_VertexData.vertices[1].position = glm::vec3(0.5f, 0.5f, 0.5f);
	//m_VertexData.vertices[2].position = glm::vec3(-0.5f, 0.5f, 0.5f);
	//m_VertexData.vertices[3].position = glm::vec3(-0.5f, -0.5f, 0.5f);
	//m_VertexData.vertices[4].position = glm::vec3(0.5f, -0.5f, 0.5f);
	//m_VertexData.vertices[5].position = glm::vec3(0.5f, 0.5f, 0.5f);

	//m_VertexData.vertices[0].uv = glm::vec2(0.0, 0.0);
	//m_VertexData.vertices[1].uv = glm::vec2(1.0, 1.0);
	//m_VertexData.vertices[2].uv = glm::vec2(0.0, 1.0);
	//m_VertexData.vertices[3].uv = glm::vec2(0.0, 0.0);
	//m_VertexData.vertices[4].uv = glm::vec2(1.0, 0.0);
	//m_VertexData.vertices[5].uv = glm::vec2(1.0, 1.0);
}

OGLMesh Model::GetVertexData()
{
	return m_VertexData;
}

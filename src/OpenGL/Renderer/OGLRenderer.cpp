#include "OGLRenderer.h"


bool OGLRenderer::Init(uint32_t width, uint32_t height)
{
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		Logger::Log(Logger::ERROR, "%s: Glad initialization error.\n", __FUNCTION__);
		return false;
	}

	if (!GLAD_GL_VERSION_4_6)
	{
		Logger::Log(Logger::ERROR, "%s: Glad wrong version.\n", __FUNCTION__);
		return false;
	}

	if (!m_Framebuffer.Init(width, height))
	{
		return false;
	}

	if (!m_Texture.LoadTexture("Textures/crate.png"))
	{
		return false;
	}
	m_VertexBuffer.Init();

	if (!m_Shader.LoadShaders("Shaders/basic.vert", "Shaders/basic.frag"))
	{
		return false;
	}

	return true;
}

void OGLRenderer::SetSize(uint32_t width, uint32_t height)
{
	m_Framebuffer.Resize(width, height);
	glViewport(0, 0, width, height);
}

void OGLRenderer::UploadData(OGLMesh vertexData)
{
	m_TriangleCount = vertexData.vertices.size();
	m_VertexBuffer.UploadData(vertexData);
}

void OGLRenderer::Draw()
{
	m_Framebuffer.Bind();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);

	m_Shader.Use();
	m_Texture.Bind();
	m_VertexBuffer.Bind();
	m_VertexBuffer.Draw(GL_TRIANGLES, 0, m_TriangleCount);
	m_VertexBuffer.Unbind();
	m_Texture.Unbind();
	m_Framebuffer.Unbind();

	m_Framebuffer.DrawToScreen();
}

void OGLRenderer::Cleanup()
{
	m_Shader.Cleanup();
	m_Texture.Cleanup();
	m_VertexBuffer.Cleanup();
	m_Framebuffer.Cleanup();
}
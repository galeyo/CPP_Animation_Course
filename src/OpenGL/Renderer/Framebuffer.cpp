#include "Framebuffer.h"

bool Framebuffer::Init(uint32_t width, uint32_t height)
{
	m_BufferWidth = width;
	m_BufferHeight = height;
	// Create framebuffer (first param - count)
	glGenFramebuffers(1, &m_Buffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_Buffer);
	// Create texture buffer
	glGenTextures(1, &m_ColorTexture);
	glBindTexture(GL_TEXTURE_2D, m_ColorTexture);
	// https://docs.gl/gl4/glTexImage2D create image texture without data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	// Additional properties for displaying don't set texture
	// Handling downscaling the texture if it is drawn far away
	// Set both to the GL_NEAREST value, which is the
	// fastest as it does no filtering at all
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// Handling upscaling the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Unbind the texture for avoiding further modification
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_ColorTexture, 0);

	glGenRenderbuffers(1, &m_DepthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBuffer);

	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return CheckComplete();
}

bool Framebuffer::Resize(uint32_t newWidth, uint32_t newHeight)
{
	m_BufferWidth = newWidth;
	m_BufferHeight = newHeight;

	Unbind();
	glDeleteTextures(1, &m_ColorTexture);
	glDeleteRenderbuffers(1, &m_DepthBuffer);
	glDeleteFramebuffers(1, &m_Buffer);

	return Init(newWidth, newHeight);
}

void Framebuffer::Bind()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_Buffer);
}

void Framebuffer::Unbind()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void Framebuffer::DrawToScreen()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_Buffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, m_BufferWidth, m_BufferHeight, 0, 0, m_BufferWidth, m_BufferHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

void Framebuffer::Cleanup()
{
	Unbind();
	glDeleteTextures(1, &m_ColorTexture);
	glDeleteRenderbuffers(1, &m_DepthBuffer);
	glDeleteFramebuffers(1, &m_Buffer);
}

bool Framebuffer::CheckComplete()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_Buffer);
	GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (result != GL_FRAMEBUFFER_COMPLETE)
	{
		return false;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return true;
}

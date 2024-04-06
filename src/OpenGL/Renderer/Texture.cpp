#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Texture.h"
#include "../Logger.h"

bool Texture::LoadTexture(std::string textureFilename)
{
	stbi_set_flip_vertically_on_load(true);
	uint8_t * textureData = stbi_load(textureFilename.c_str(), &m_TextureWidth, &m_TextureHeight, &m_NumberOfChannels, 0);
	if (!textureData)
	{
		Logger::Log(Logger::ERROR, "%s: Error while loading texture from file: %s\n", __FUNCTION__, textureFilename.c_str());
		stbi_image_free(textureData);
		return false;
	}
	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	// Additional properties
	// For the minification, use trilinear sampling
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// For magnification, use linear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Repeat the texture outside of the range
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_TextureWidth, m_TextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(textureData);
	return true;
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_Texture);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Cleanup()
{
	glDeleteTextures(1, &m_Texture);
}

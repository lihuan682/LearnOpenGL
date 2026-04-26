#include "Texture.h"
#include"glew.h"
#include"stb_image.h"
Texture::Texture(const std::string& filepath)
{
	stbi_set_flip_vertically_on_load(true);
	float borderColor[] = { 1.0f,1.0f,1.0f,1.0f };
	glGetTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glGenTextures(1, &m_ID);
	m_data = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_nrChannels,0);
	glBindTexture(GL_TEXTURE_2D, m_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
	glGenerateMipmap(GL_TEXTURE_2D);
	if (!m_data)
	{
		std::cout << "texture load error" << std::endl;
	}
	stbi_image_free(m_data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_ID);
}

void Texture::Bind(const int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

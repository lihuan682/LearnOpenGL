#include "EBO.h"
#include"glew.h"
EBO::EBO(const void* data, const unsigned int& size)
{
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

EBO::~EBO()
{
	glDeleteBuffers(1, &m_ID);
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void EBO::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

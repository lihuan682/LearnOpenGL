#include"VBO.h"
#include"glew.h"
VBO::VBO(const void* data, const unsigned int &size)
{
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_VERTEX_ARRAY, m_ID);
	glBufferData(GL_VERTEX_ARRAY, size, data, GL_STATIC_DRAW);
}

VBO::~VBO()
{
	glDeleteBuffers(1, &m_ID);
}

void VBO::Bind()
{
	glBindBuffer(GL_VERTEX_ARRAY, m_ID);
}

void VBO::UnBind()
{
	glBindBuffer(GL_VERTEX_ARRAY, 0);
}

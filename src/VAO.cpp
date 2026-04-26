#include "VAO.h"
#include "VBO.h"
#include"VertexBufferLayout.h"
#include"glew.h"
VAO::VAO()
{
	glGenVertexArrays(1, &m_ID);
	glBindVertexArray(m_ID);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &m_ID);
}

void VAO::Bind()
{
	glBindVertexArray(m_ID);
}

void VAO::UnBind()
{
	glBindVertexArray(0);
}

void VAO::Add_VBO(VBO&vbo, VertexBufferLayout layout)
{
	Bind();
	vbo.Bind();
	unsigned int offset = 0;
	const auto& elements = layout.m_Element;
	for (int i = 0;i<elements.size();i++)
	{
		glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].nomalized, layout.m_Stride, (void*)offset);
		offset += elements[i].count * VertexBufferElement::GetSizeOfType(elements[i].type);
		glEnableVertexAttribArray(i);
	}
}

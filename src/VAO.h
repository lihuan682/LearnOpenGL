#pragma once
class VBO;
class VertexBufferLayout;
class VAO
{
public:
	VAO();
	~VAO();
	unsigned int m_ID;
	void Bind();
	void UnBind();
	void Add_VBO(VBO& vbo, VertexBufferLayout layout);
};
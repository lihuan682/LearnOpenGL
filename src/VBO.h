#pragma once
class VBO
{
public:
	unsigned int m_ID;
	VBO(const void* data, const unsigned int &size);
	~VBO();
	void Bind();
	void UnBind();

};
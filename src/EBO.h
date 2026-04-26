#pragma once
class EBO
{public:
	unsigned int m_ID;
	EBO(const void*data,const unsigned int& size);
	~EBO();
	void Bind();
	void UnBind();
};
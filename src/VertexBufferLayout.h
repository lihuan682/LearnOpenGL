#pragma once
#include"glew.h"
#include<vector>
struct VertexBufferElement
{
	unsigned int count;
	unsigned int type;
	unsigned int nomalized;
	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT : return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
		}
		return 0;
	}
};
class VertexBufferLayout
{
public:
	std::vector<VertexBufferElement>m_Element;
	unsigned int m_Stride;
	VertexBufferLayout() :m_Stride(0) {};
	~VertexBufferLayout() {};
	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}
	template<>
	void Push<float>(unsigned int count)
	{
		m_Element.push_back(VertexBufferElement(count, GL_FLOAT, GL_FALSE));
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}
	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Element.push_back(VertexBufferElement(count, GL_UNSIGNED_INT, GL_FALSE));
		m_Stride+=count* VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}
	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Element.push_back(VertexBufferElement(count, GL_UNSIGNED_BYTE, GL_FALSE));
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}
};
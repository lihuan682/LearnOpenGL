#pragma once
#include"iostream"

class Texture
{
public:
unsigned int m_ID;
unsigned char* m_data;
int m_Width;
int m_Height;
int m_nrChannels;
Texture(const std::string&filepath);
~Texture();
void Bind(const int slot);
void UnBind();

};
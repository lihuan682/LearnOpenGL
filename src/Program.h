#pragma once
#include<string>
struct ShaderSource
{
	std::string VertexShaderSource;
	std::string fragmentShaderSource;
};
class Program
{
	public:
		 Program(const std::string& filepath);
		~Program();
		void Bind();
		void UnBind();
		unsigned int m_ID;
		std::string FilePath;
		ShaderSource ParseShaderSource(std::string fliepath);
		unsigned int CreateProgram(std::string VertexShaderSource, std::string fragmentShaderSource);
		unsigned int CompileShader(unsigned int type, std::string Source);
};
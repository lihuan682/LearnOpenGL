#include "Program.h"
#include"glew.h"
#include"iostream"
#include"string"
#include<fstream>
#include<sstream>
Program::Program(const std::string& filepath):FilePath(filepath)
{
	ShaderSource Source = ParseShaderSource(FilePath);
	m_ID = CreateProgram(Source.VertexShaderSource, Source.fragmentShaderSource);
}

Program::~Program()
{
	glDeleteProgram(m_ID);
}
void Program::Bind()
{
	glUseProgram(m_ID);
}
void Program::UnBind()
{
	glUseProgram(0);
}
ShaderSource Program::ParseShaderSource(std::string fliepath)
{
	std::ifstream stream(fliepath);
	std::stringstream ss[2];
	std::string line;
	if (!stream.is_open())
	{
		std::cerr << "Open Failed" << std::endl;
	}
	enum class shaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	shaderType Type = shaderType::NONE;
	while (getline(stream,line))
	{
		if (line.find("#Shader") != std::string::npos)
		{
			if (line.find("Vertex")!=std::string::npos)
			{
				Type = shaderType::VERTEX;
			}
			else if (line.find("Fragment") != std::string::npos)
			{
				Type = shaderType::FRAGMENT;
			}
	}
		else
		{
			ss[int(Type)] << line << "\n";
		}
	}
	return { ss[1].str(), ss[2].str() };
}

unsigned int Program::CreateProgram(std::string VertexShaderSource, std::string fragmentShaderSource)
{
	unsigned int program = glCreateProgram();
	unsigned int VertexShader = CompileShader(GL_VERTEX_SHADER, VertexShaderSource);
	unsigned int FragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	glAttachShader(program, VertexShader);
	glAttachShader(program, FragmentShader);
	glLinkProgram(program);
 GLint success;
 char infoLog[50];
	 glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);
	 if (!success)
	 {
		 glGetShaderInfoLog(VertexShader, 50, NULL, infoLog);
		 std::cout << " ERROR 1: " <<infoLog<< std::endl;
	 }
	 glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
	 if (!success)
	 {
		 glGetShaderInfoLog(VertexShader,50, NULL, infoLog);
		 std::cout << " ERROR 2: " <<infoLog<< std::endl;
	 }
 glGetProgramiv(program, GL_LINK_STATUS, &success);
	 if (!success)
	 {
		 glGetProgramInfoLog(program, 50, NULL, infoLog);
		 std::cout << " ERROR 3: " <<infoLog<< std::endl;
	 }
 glDeleteShader(VertexShader);
 glDeleteShader(FragmentShader);
 return program;
}

unsigned int Program::CompileShader(unsigned int type, std::string Source)
{
	const char* src = Source.c_str();
	unsigned int id = glCreateShader(type);
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);
	return id;
}

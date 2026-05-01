#define GLFW_INCLUDE_NONE
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#include"glew.h"
#include"glfw3.h"
#include"stb_image.h"
#include"iostream"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"
#include<string>
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float lastX = 500, lastY = 400;
float yaw=-90;
float pitch=0;
bool firstMouse = false;
float fov = 45;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}
static void key_callback(GLFWwindow* windon, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(windon, GLFW_TRUE);
}
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow*, double xoffset, double yyoffset);



int main()
{//Init Context
	if (!glfwInit())
	{
		std::cout << "glewInitialization failed" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
	glfwSetErrorCallback(error_callback);




	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Let us start", NULL, NULL);
	if (!window)
	{
		std::cout << "window created failed" << std::endl;
	}
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)
	{
		std::cout << " NOT_OK" << std::endl;
		return -1;
	}

	
	//Init Data

	stbi_set_flip_vertically_on_load(true);
	float Vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,0.0f,-1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,0.0f,-1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,0.0f,-1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,0.0f,-1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,0.0f,-1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,0.0f,-1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,0.0f,1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,0.0f,1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,0.0f,1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,0.0f,1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,0.0f,1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,0.0f,1.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,0.0f,0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,0.0f,0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,0.0f,0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,0.0f,0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,0.0f,0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,0.0f,0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f,0.0f,0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f,0.0f,0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f,0.0f,0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f,0.0f,0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,0.0f,0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f,0.0f,0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f,-1.0f,0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f,-1.0f,0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f,-1.0f,0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f,-1.0f,0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f,-1.0f,0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f,-1.0f,0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,1.0f,0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,1.0f,0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,1.0f,0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,1.0f,0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0f,1.0f,0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,1.0f,0.0f
	};


	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(0.0f,  0.0f,  1.0f),
	glm::vec3(0.0f,  0.0f,  2.0f),
	glm::vec3(0.0f,  1.0f,  0.0f),
	glm::vec3(0.0f,  1.0f,  1.0f),
	glm::vec3(0.0f,  1.0f,  2.0f),
	glm::vec3(0.0f,  2.0f,  0.0f),
	glm::vec3(0.0f,  2.0f,  1.0f),
	glm::vec3(0.0f,  2.0f,  2.0f),
	glm::vec3(1.0f,  0.0f,  0.0f),
	glm::vec3(1.0f,  0.0f,  1.0f),
	glm::vec3(1.0f,  0.0f,  2.0f),
	glm::vec3(1.0f,  1.0f,  0.0f),
	glm::vec3(1.0f,  1.0f,  1.0f),
	glm::vec3(1.0f,  1.0f,  2.0f),
	glm::vec3(1.0f,  2.0f,  0.0f),
	glm::vec3(1.0f,  2.0f,  1.0f),
	glm::vec3(1.0f,  2.0f,  2.0f),
	glm::vec3(2.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  0.0f,  1.0f),
	glm::vec3(2.0f,  0.0f,  2.0f),
	glm::vec3(2.0f,  1.0f,  0.0f),
	glm::vec3(2.0f,  1.0f,  1.0f),
	glm::vec3(2.0f,  1.0f,  2.0f),
	glm::vec3(2.0f,  2.0f,  0.0f),
	glm::vec3(2.0f,  2.0f,  1.0f),
	glm::vec3(2.0f,  2.0f,  2.0f),

	glm::vec3(4,4,4)
	};


	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	float borderColor[] = { 1.0f,1.0f,0.f,1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	



	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)20);
	glEnableVertexAttribArray(2);

	unsigned int texture1;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture1);
	int width, height, nrChannels;
	unsigned char* data = stbi_load("res/TEXTURE/container.png", &width, &height, &nrChannels, 0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	
	unsigned int texture2; 
	int width1, height1, nrChannels1;
	glActiveTexture(GL_TEXTURE1);
	unsigned char* data1 = stbi_load("res/TEXTURE/face.png", &width1, &height1, &nrChannels1, 0);
	glGenTextures(1,&texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	if (data1)
	{
		std::cout << "OK" << std::endl;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data1);


	unsigned int texture3;
	int width2, height2, nrChannels2;
	unsigned char* data2 = stbi_load("res/TEXTURE/face1.png", &width2, &height2, &nrChannels2, 0);
	glGenTextures(1, &texture3);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D,texture3);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_RGBA,GL_UNSIGNED_BYTE,data2);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data2);

	const char* vertexShaderSource = "#version 330 core\n"
		"layout(location=0) in vec3 aPos;\n"
		"layout(location=1) in vec2 aTexCoord;\n"
		"layout(location=2) in vec3 aNormal;\n"
		"out vec2 TexCoord;\n"
		"out vec3 Normal;\n"
		"out vec3 FragPos;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main()\n"
		"{\n"
		"gl_Position=projection*view*model*vec4(aPos,1.0);\n"
		"TexCoord=aTexCoord;\n"
		"FragPos=vec3(model*vec4(aPos,1.0));"
		"Normal=aNormal;\n"
		"}\n";
	unsigned int VertexShader;
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, &vertexShaderSource, NULL);
	int success;
	char infoLog[512];
	glCompileShader(VertexShader);
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(VertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::Vertex::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

//"	"FragColor=mix(texture(texture1,TexCoord),texture(texture2,TexCoord),1.0);\n"(light.direction)
unsigned int FragmentShader;
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec2 TexCoord;\n"
		"in vec3 Normal;\n"
		"in vec3 FragPos;\n"

		"struct Material{\n"
		"vec3 ambient;\n"
		"sampler2D diffuse;\n"
		"sampler2D specular;\n"
		"float shininess;\n"
		"};\n"
		
		"struct DirLight{\n"
		"vec3 direction;\n"
		"vec3 ambient;\n"
		"vec3 diffuse;\n"
		"vec3 specular;\n"
		"};\n"

		"struct PointLight{\n"
		"vec3 ambient;\n"
		"vec3 diffuse;\n"
		"vec3 specular;\n"
		"vec3 position;\n"
		"float constant;\n"
		"float linear;\n"
		"float quadratic;\n"
		"};\n"

		"struct SpotLight{\n"
		"vec3 position;\n"
		"vec3 direction;\n"
		"vec3 diffuse;\n"
		"vec3 ambient;\n"
		"float constant;\n"
		"float linear;\n"
		"float quadratic;\n"
		"vec3 specular;\n"
		"float CutOff;\n"
		"float OutCutOff;\n"
		"};\n"

		"uniform vec3 viewPos;\n"
		"uniform DirLight dirLight;\n"
		"uniform SpotLight spotLight;\n"
		"#define NR_POINT_LIGHTS 6\n"
		"uniform PointLight pointLights[NR_POINT_LIGHTS];\n"
		"uniform Material material;\n"
		"uniform sampler2D face;\n"

		"vec3 CalcSpotLight(SpotLight light,vec3 normal,vec3 fragPos,vec3 viewDir)\n"
		"{\n"
		"float distance=length(light.position-fragPos);\n"
		"vec3 lightDir=normalize(light.position-fragPos);\n"
		"float diff=max(dot(normal,lightDir),0.0);\n"
		"vec3 reflectDir=reflect(-lightDir,normal);\n"
		"float spec=pow(max(dot(reflectDir,viewDir),0.0),material.shininess);\n"
		"float theta=dot(lightDir, normalize(-light.direction));\n"
		"float epsilon=light.CutOff-light.OutCutOff;\n"
		"float intensity=clamp((theta-light.OutCutOff)/epsilon,0.0,1.0);\n"
		"float attenuation=1.0/(light.constant+light.linear*distance+light.quadratic*distance*distance);\n"
		"vec3 ambient=light.ambient*vec3(texture(material.diffuse,TexCoord));\n"
		"vec3 diffuse=light.diffuse*vec3(texture(material.diffuse,TexCoord));\n"
		"vec3 specular=light.specular*vec3(texture(material.specular,TexCoord))*spec;\n"
		"ambient*=attenuation;\n"
		"diffuse*=attenuation;\n"
		"specular*=attenuation;\n"
		"ambient*=intensity;\n"
		"diffuse*=intensity;\n"
		"specular*=intensity;\n"
		"return (ambient+diffuse+specular);\n"
		"}\n"

		"vec3 CalcDirLight(DirLight light,vec3 normal,vec3 viewDir)\n"
		"{\n"
		"vec3 lightDir=normalize(-light.direction);\n"
		"float diff=max(dot(normal,lightDir),0.0);\n"
		"vec3 reflectDir=reflect(-lightDir,normal);\n"
		"float spec=pow(max(dot(viewDir,reflectDir),0.0),material.shininess);\n"
		"vec3 ambient=light.ambient*vec3(texture(material.diffuse,TexCoord));\n"
		"vec3 diffuse=light.diffuse*vec3(texture(material.diffuse,TexCoord))*diff;\n"
		"vec3 specular=light.specular*vec3(texture(material.specular,TexCoord))*spec;\n"
		"return (ambient+diffuse+specular);\n"
		"}\n"

		"vec3 CalcPointLight(PointLight light,vec3 normal,vec3 fragPos,vec3 viewDir)\n"
		"{\n"
		"vec3 lightDir=normalize(light.position-fragPos);\n"
		"float diff=max(dot(normal,lightDir),0.0);\n"
		"vec3 reflectDir=reflect(-lightDir,normal);\n"
		"float spec=pow(max(dot(viewDir,reflectDir),0.0),material.shininess);\n"
		"float distance=length(light.position-fragPos);\n"
		"float attenuation=1.0/(light.constant+light.linear*distance+light.quadratic*distance*distance);\n"
		"vec3 ambient=light.ambient*vec3(texture(material.diffuse,TexCoord));\n"
		"vec3 diffuse=light.diffuse*vec3(texture(material.diffuse,TexCoord));\n"
		"vec3 specular=light.specular*vec3(texture(material.specular,TexCoord))*spec;\n"
		"ambient*=attenuation;\n"
		"diffuse*=attenuation;\n"
		"specular*=attenuation;\n"
		"return (ambient+diffuse+specular);\n"
		"}\n"



		"void main()\n"
		"{\n"
		"vec3 norm=normalize(Normal);\n"
		"vec3 viewDir=normalize(viewPos-FragPos);\n"
		"vec3 result;\n"
		"result=CalcDirLight(dirLight,norm,viewDir);\n"
		"for(int i=0;i<NR_POINT_LIGHTS;i++)\n"
		"result+=CalcPointLight(pointLights[i],norm,FragPos,viewDir);\n"
		"result+=CalcSpotLight(spotLight,norm,FragPos,viewDir);\n"
		"FragColor=vec4(result,1.0);\n"
		"}\n";
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(FragmentShader);
	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(FragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::Fragment::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
    
	const char* SunShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"\n"
		"void main()\n"
		"{\n"
		"    FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
		"}\n";
	unsigned int Sun = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(Sun, 1, &SunShaderSource, NULL);
	glCompileShader(Sun);



	unsigned int ShaderProgram;
	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
	glGetProgramInfoLog(ShaderProgram, 512, NULL, infoLog);
	glUseProgram(ShaderProgram);
	
	glDeleteShader(FragmentShader);


	unsigned int SunProgram = glCreateProgram();
	glAttachShader(SunProgram, Sun);
	glAttachShader(SunProgram, VertexShader);
	glLinkProgram(SunProgram);
	glDeleteShader(VertexShader);
	glDeleteShader(Sun);

	int Width, Height;
	glfwGetFramebufferSize(window, &Width, &Height);
	glViewport(0, 0, Width, Height);

	glBindVertexArray(VAO);
	double time = glfwGetTime();

	unsigned int  transformLoc = glGetUniformLocation(ShaderProgram, "transform");
	
	
	glm::mat4 view(1.0f);

	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
	int modelLoc = glGetUniformLocation(ShaderProgram, "model");
	int viewLoc = glGetUniformLocation(ShaderProgram, "view");
	int projectionlLoc = glGetUniformLocation(ShaderProgram, "projection");
	

	glEnable(GL_DEPTH_TEST);
	glfwSetKeyCallback(window, key_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	unsigned int CameraLoc = glGetUniformLocation(ShaderProgram, "viewPos");
	

	
	
	struct Material
	{
		glm::vec3 ambient;
		glm::vec3 specular;
		float shininess;
	};
	
	Material material = {
	glm::vec3(0.01,0.01,0.01),
	glm::vec3(1.f,1.f,1.f),
	128.f
	};

	glUniform3fv(glGetUniformLocation(ShaderProgram, "material.ambient"), 1, &material.ambient[0]);
	glUniform1i(glGetUniformLocation(ShaderProgram, "material.diffuse"),0);
	glUniform1i(glGetUniformLocation(ShaderProgram, "material.specular"), 1);
	glUniform1f(glGetUniformLocation(ShaderProgram, "material.shininess"),material.shininess);
struct DirLight {
		glm::vec3 direction;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	DirLight dirlight = {
	glm::vec3(0.f, 0.0f, -1.f), // direction
	glm::vec3(0.1f, 0.1f, 0.1f), // ambient
	glm::vec3(0.4f, 0.4f, 0.4f),    // diffuse
	glm::vec3(1.f, 1.f, 1.f)     // specular
	};
	glUniform3fv(glGetUniformLocation(ShaderProgram, "dirLight.direction"), 1, &dirlight.direction[0]);
	glUniform3fv(glGetUniformLocation(ShaderProgram, "dirLight.ambient"), 1, &dirlight.ambient[0]);
	glUniform3fv(glGetUniformLocation(ShaderProgram, "dirLight.diffuse"), 1, &dirlight.diffuse[0]);
	glUniform3fv(glGetUniformLocation(ShaderProgram, "dirLight.specular"), 1, &dirlight.specular[0]);
	
	struct PointLight {
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		glm::vec3 position;
		float constant;
		float linear;
		float quadratic;
	};
		PointLight pointlight = {
		glm::vec3(1.0f,1.0f,1.0f),  // ambient
		glm::vec3(1.0f,1.0f,1.0f),   // diffuse
		glm::vec3(1.00f,1.00f,1.00f),   // specular
		glm::vec3(-1.f,1.f, -1.f), // position
		1.0f,   // constant
		5.f,  // linear
		10.f  // quadratic
	};
	for (int i = 0;i < 6;i++)
	{
		std::string idx = std::to_string(i);

		glUniform3fv(glGetUniformLocation(ShaderProgram, ("pointLights[" + idx + "].position").c_str()), 1, &pointlight.position[0]);
		glUniform3fv(glGetUniformLocation(ShaderProgram, ("pointLights[" + idx + "].ambient").c_str()), 1, &pointlight.ambient[0]);
		glUniform3fv(glGetUniformLocation(ShaderProgram, ("pointLights[" + idx + "].diffuse").c_str()), 1, &pointlight.diffuse[0]);
		glUniform3fv(glGetUniformLocation(ShaderProgram, ("pointLights[" + idx + "].specular").c_str()), 1, &pointlight.specular[0]);

		glUniform1f(glGetUniformLocation(ShaderProgram, ("pointLights[" + idx + "].constant").c_str()), pointlight.constant);
		glUniform1f(glGetUniformLocation(ShaderProgram, ("pointLights[" + idx + "].linear").c_str()), pointlight.linear);
		glUniform1f(glGetUniformLocation(ShaderProgram, ("pointLights[" + idx + "].quadratic").c_str()), pointlight.quadratic);
	}

	struct SpotLight {
		glm::vec3 position;
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 ambient;
		glm::vec3 specular;
		float constant;
		float linear;
		float quadratic;
		float CutOff;
		float OutCutOff;
	};
	SpotLight spotlight = {
		cameraPos,          // position
		cameraFront,        // direction
		glm::vec3(1.0f,1.0f,1.0f),    // diffuse
		glm::vec3(1.0f,1.0f,1.0f),   // ambient
		glm::vec3(1.00f,1.00f,1.00f),    // specular
		1.0f,
		0.09f,
		0.032f,
		glm::cos(glm::radians(12.5f)), // CutOff
		glm::cos(glm::radians(17.5f))  // OutCutOff
	};
	glUniform3fv(glGetUniformLocation(ShaderProgram, "spotLight.position"), 1, &spotlight.position[0]);
	glUniform3fv(glGetUniformLocation(ShaderProgram, "spotLight.direction"), 1, &spotlight.direction[0]);
	glUniform3fv(glGetUniformLocation(ShaderProgram, "spotLight.ambient"), 1, &spotlight.ambient[0]);
	glUniform3fv(glGetUniformLocation(ShaderProgram, "spotLight.diffuse"), 1, &spotlight.diffuse[0]);
	glUniform3fv(glGetUniformLocation(ShaderProgram, "spotLight.specular"), 1, &spotlight.specular[0]);

	glUniform1f(glGetUniformLocation(ShaderProgram, "spotLight.constant"), spotlight.constant);
	glUniform1f(glGetUniformLocation(ShaderProgram, "spotLight.linear"), spotlight.linear);
	glUniform1f(glGetUniformLocation(ShaderProgram, "spotLight.quadratic"), spotlight.quadratic);
	glUniform1f(glGetUniformLocation(ShaderProgram, "spotLight.CutOff"), spotlight.CutOff);
	glUniform1f(glGetUniformLocation(ShaderProgram, "spotLight.OutCutOff"), spotlight.OutCutOff);


	
	glUniform1i(glGetUniformLocation(ShaderProgram, "face"), 2);

	glfwSwapInterval(1);
	while (!glfwWindowShouldClose(window))
	{	
		
		glfwPollEvents();
		processInput(window);
		float currrentFrame = glfwGetTime();
		deltaTime = currrentFrame - lastFrame;
		lastFrame = currrentFrame;
		GLenum err=glGetError();
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.02, 0.01, 0.08, 1.0f);
		glUseProgram(ShaderProgram);
		glBindVertexArray(VAO);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		
		glUniform3fv(glGetUniformLocation(ShaderProgram, "spotLight.position"), 1, &cameraPos[0]);
		glUniform3fv(glGetUniformLocation(ShaderProgram, "spotLight.direction"), 1, &cameraFront[0]);

		//dirlight.direction = { sin(glfwGetTime()), sin(glfwGetTime())+cos(glfwGetTime()),cos(glfwGetTime()) };
		//glUniform3fv(glGetUniformLocation(ShaderProgram, "dirLight.direction"), 1, &dirlight.direction[0]);
		for (unsigned int i = 0; i <28; i++)
		{
			glm::mat4 model(1.0f);
			projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
			model = glm::translate(model, cubePositions[i]);
			view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
			float angle = 20.0f+glfwGetTime()*20.0f;
			//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(projectionlLoc, 1, GL_FALSE, glm::value_ptr(projection));
			glUniform3fv(CameraLoc, 1,&cameraPos[0]);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	glfwDestroyWindow(window);
}
void processInput(GLFWwindow* window)
{
		float cameraSpeed =2.f*deltaTime; 
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if(glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp))*cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if(firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	glm::vec3 front;
	front.y = sin(glm::radians(pitch));
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);
}
void scroll_callback(GLFWwindow*, double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}
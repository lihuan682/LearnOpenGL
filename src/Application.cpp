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
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float lastX = 500, lastY = 500;
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

	glfwSetKeyCallback(window, key_callback);
	//Init Data

	stbi_set_flip_vertically_on_load(true);
	float Vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)12);
	glEnableVertexAttribArray(1);

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


	const char* vertexShaderSource = "#version 330 core\n"
		"layout(location=0) in vec3 aPos;\n"
		"layout(location=1) in vec2 aTexCoord;\n"
		"out vec2 TexCoord;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main()\n"
		"{\n"
		"gl_Position=projection*view*model*vec4(aPos,1.0);\n"
		"TexCoord=aTexCoord;\n"
		"}\0";
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
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}



unsigned int FragmentShader;
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec2 TexCoord;\n"  
		"uniform sampler2D texture1;\n"
		"uniform sampler2D texture2;\n"
		"void main()\n"
		"{\n"
		"FragColor =mix(texture(texture1,TexCoord),texture(texture2,TexCoord),0.2);\n"
		"}\n";
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(FragmentShader);
	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(FragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
    

	unsigned int ShaderProgram;
	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
	glGetProgramInfoLog(ShaderProgram, 512, NULL, infoLog);
	glUseProgram(ShaderProgram);
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);


	int Width, Height;
	glfwGetFramebufferSize(window, &Width, &Height);
	glViewport(0, 0, Width, Height);

	glBindVertexArray(VAO);
	double time = glfwGetTime();

	glUniform1i(glGetUniformLocation(ShaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(ShaderProgram, "texture2"), 1);
	unsigned int  transformLoc = glGetUniformLocation(ShaderProgram, "transform");
	
	
	glm::mat4 view(1.0f);
	view=glm::translate(view, glm::vec3(0.f, 0.f,-3.0f));
	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
	int modelLoc = glGetUniformLocation(ShaderProgram, "model");
	int viewLoc = glGetUniformLocation(ShaderProgram, "view");
	int projectionlLoc = glGetUniformLocation(ShaderProgram, "projection");
	
		
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	

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
	  //glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		
		for (unsigned int i = 0; i <27; i++)
		{
			glm::mat4 model(1.0f);
			projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
			model = glm::translate(model, cubePositions[i]);
			view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
			float angle = 20.0f+glfwGetTime()*20.0f;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glUniformMatrix4fv(projectionlLoc, 1, GL_FALSE, glm::value_ptr(projection));
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
		float cameraSpeed =10.f*deltaTime; 
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
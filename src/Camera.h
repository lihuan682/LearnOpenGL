#pragma once
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"
#include"glfw3.h"
class Camera
{
public:
	Camera();
	~Camera();
	void Updata(float delta);


	glm::vec3 WorldX = glm::vec3(1.0, 0.0, 0.0);
	glm::vec3 WorldY=glm::vec3(0.0,1.0,0.0);
	glm::vec3 WorldZ=glm::vec3(0.0,0.0,1.0);

	glm::vec3 CameraPos=glm::vec3(0.0,0.0,1.0);
	glm::vec3 CameraFront= CameraPos-glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 CameraRight= glm::normalize(glm::cross(WorldZ,CameraFront));
	glm::vec3 CameraUp =glm::normalize(glm::cross(CameraFront,CameraRight));
	glm::mat4 view=glm::lookAt(CameraPos,CameraPos+CameraFront,CameraUp);
	
	float pitch;
	float yaw;
	float deltaTime = 0.0f;
	float CameraSpeed= 5.0f;


	float W_divide_H;
	float fov = 45.0;
	glm::mat4 projection = glm::perspective(glm::radians(fov), (float)W_divide_H, 0.1f, 100.0f);
};
#include "Camera.h"
#include"glfw3.h"
Camera::Camera(GLFWwindow* window)
{
	SetCallBack(window);
}s
Camera::~Camera()
{
}
void Camera::Updata(float delta)
{
	deltaTime = delta;
}
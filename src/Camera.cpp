#include "Camera.h"
#include"glfw3.h"
Camera::Camera()
{
}
Camera::~Camera()
{
}
void Camera::Updata(float delta)
{
	deltaTime = delta;
	view = glm::lookAt(CameraPos, CameraPos + CameraFront, CameraUp);

}
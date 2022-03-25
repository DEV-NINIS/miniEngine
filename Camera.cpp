#include "Camera.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) :
    camFront(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    yaw = YAW; pitch = PITCH;
    camPos = position;
    camUp = up;
    Yaw = yaw;
    Pitch = pitch;
}
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : camFront(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    camPos = glm::vec3(posX, posY, posZ);
    camUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
}
Camera::~Camera() {}

void Camera::processInputCamera(GLFWwindow* window, float deltaTime, float CameraSpeedValue) {
	cameraSpeed = CameraSpeedValue * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_D) == true) {
		camPos += camFront * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == true) {
		camPos -= camFront * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == true) {
		camPos -= glm::normalize(glm::cross(camUp, camFront)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == true) {
		camPos += glm::normalize(glm::cross(camUp, camFront)) * cameraSpeed;
	}
}
glm::mat4 Camera::getViewMatrix() { return glm::lookAt(camPos, camPos + camFront, camUp); }

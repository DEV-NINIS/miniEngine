#include "Camera.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Camera::Camera() {
	cameraSpeed; 
	camPos = glm::vec3(0.0f, 0.0f, -3.0f);
	camFront = glm::vec3(0.0f, 0.0f, 1.0f);
	camUp = glm::vec3(0.0f, 1.0f, 0.0f);
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

#include "Camera.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Camera::Camera() {
	camPos = glm::vec3(0.0f, 0.0f, 1.0f); camFront = glm::vec3(0.0f, 0.0f, 1.0f); camUp = glm::vec3(0.0f, 1.0f, 0.0f); cameraSpeed;
    yaw; pitch; lastX; lastY; firstMouse;
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
void Camera::setCameraPitchYaw(GLFWwindow* window, Camera& camera, float& lastX, float& lastY, float Xpos, float Ypos) {
	lastX = (glfwGetVideoMode(glfwGetPrimaryMonitor())->width) / 2;
	lastY = (glfwGetVideoMode(glfwGetPrimaryMonitor())->height) / 2;
	float xoffset = Xpos - lastX;
	float yoffset = lastY - Ypos; // il faut inverser car ypos est donné de haut en bas
	lastX = Xpos;
	lastY = Ypos;

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
}
void Camera::scroll_callback(GLFWwindow* window, float xoffset, float yoffset, float &FOV) {
    if (FOV >= 1.0f && FOV <= 45.0f)
        FOV -= yoffset;
    if (FOV <= 1.0f)
        FOV = 1.0f;
    if (FOV >= 45.0f)
        FOV = 45.0f;
}
void Camera::mouseCallBack(GLFWwindow* window, float XposIn, float YposIn, float& FOV) {
    float xpos = static_cast<float>(XposIn);
    float ypos = static_cast<float>(YposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camFront = glm::normalize(front);
    scroll_callback(window, xoffset, yoffset, FOV);
}
glm::vec3 Camera::getcamFront() { return camFront; }
glm::vec3 Camera::getcamUp() { return camUp; }
glm::vec3 Camera::getcamPos() { return camPos; }
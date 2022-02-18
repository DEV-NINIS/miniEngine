#include "Camera.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Camera::Camera() {
	camPos; camFront; camUp;
}
Camera::~Camera() {}

void Camera::processInputCamera() {
	camUp = glm::vec3(1.0f);
	camFront = glm::vec3(1.0f);
	camPos = glm::vec3(1.0f);
}
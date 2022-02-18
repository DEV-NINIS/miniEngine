#pragma once
#ifndef DEF_CAMERA
#define DEF_CAMERA	

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Camera
{
public:
	Camera();
	~Camera();
	void processInputCamera();
	// getting values of camera
	glm::vec3 getcamPos();
	glm::vec3 getcamFront();
	glm::vec3 getcamUp
protected:
	glm::vec3 camPos;
	glm::vec3 camFront;
	glm::vec3 camUp;
};


#endif //


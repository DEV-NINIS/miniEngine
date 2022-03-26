#pragma once
#ifndef DEF_CAMERA
#define DEF_CAMERA	

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	Camera();
	~Camera();
	void processInputCamera(GLFWwindow* window, float deltaTime, float CameraSpeedValue);
	
	
	// getting values of camera
	glm::mat4 getViewMatrix();
	glm::vec3 camPos;
	glm::vec3 camFront;
	glm::vec3 camUp;
	float Zoom;

protected:
	bool firstMouse = true;
	

	glm::vec3 camRight; 
	float cameraSpeed;
	float Yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float Pitch = 0.0f;
	float MovementSpeed;
	float MouseSensitivity;
	float lastX;
	float lastY;
};


#endif //


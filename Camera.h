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
	void processInputCamera(GLFWwindow* window, float deltaTime, float CameraSpeedValue);
	void mouseCallBack(GLFWwindow* window, float XposIn, float YposIn, float& FOV);
	void setCameraPitchYaw(GLFWwindow* window, Camera& camera, float& lastX, float& lastY, float Xpos, float Ypos);
	void scroll_callback(GLFWwindow* window, float xoffset, float yoffset, float &FOV);
	
	// getting values of camera
	glm::vec3 getcamPos();
	glm::vec3 getcamFront();
	glm::vec3 getcamUp();
protected:
	bool firstMouse = true;
	glm::vec3 camPos;
	glm::vec3 camFront;
	glm::vec3 camUp;
	float cameraSpeed;
	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;
	float lastX;
	float lastY;
};


#endif //


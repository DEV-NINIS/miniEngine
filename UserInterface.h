#ifndef DEF_USER_INTERFACE
#define DEF_USER_INTERFACE

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glmAnimation3D.h"

class UserInterface 
{
public:
	UserInterface(GLFWwindow* window);
	virtual ~UserInterface();
	bool inputDemandingScaleCube();
	bool inputDemandingScaleCubeX();
	bool inputDemandingScaleCubeY();
	bool inputDemandingScaleCubeZ();
	char inputFileTexture();
	float setScaleCube();
	float setScaleCubeX();
	float setScaleCubeY();
	float setScaleCubeZ();
	void setSettingFrame();
	void setLastedmatrix();
	void endFrame();
	float LastedFloatFrame;
	float LastedFloatFrameX;
	float LastedFloatFrameY;
	float LastedFloatFrameZ;
	protected:
		float* size1 = nullptr;
};

#endif // !1


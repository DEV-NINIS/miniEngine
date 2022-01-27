#ifndef DEF_USER_INTERFACE
#define DEF_USER_INTERFACE

#include <iostream>
#include <vector>
#include "glmAnimation3D.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class UserInterface : public glmAnimation3D
{
public:
	UserInterface(GLFWwindow* window);
	bool inputDemandingScaleCube();
	char inputFileTexture();
	float setScaleCube(GLuint shader);
	void setSettingFrame();
	void endFrame();
	virtual ~UserInterface();
	float LastedFloatFrame;
protected:

};

#endif // !1


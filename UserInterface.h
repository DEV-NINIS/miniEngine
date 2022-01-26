#ifndef DEF_USER_INTERFACE
#define DEF_USER_INTERFACE

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class UserInterface
{
public:
	UserInterface(GLFWwindow* window);
	void BasicFonction();
	void setSettingFrame();
	void endFrame();
	virtual ~UserInterface();
protected:

};

#endif // !1


#include <iostream>
#include <string>
#include "cube.h"
#include "stbi_image.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "UserInterface.h"
#include "imgui/imgui_impl_opengl3.h"
#include "glmAnimation3D.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
//												_____
//               /\         |\		|	 |	   |
//				/  \		| \		|	 |	   |
//			   /	\		|  \	|	 |	   |_____
//			  /------\		|	\	|	 |			 |
//			 /		  \		|	 \	|	 |			 |
//			/		   \	|	  \	|	 |		_____|
//


void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
int main() {
	// set parametters of OpenGL
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.6);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4.6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef _APPLE_
	glfwwindowhint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // _APPLE_

	//
	int* resY = new int; *resY = 1440; float resX2 = 2560;
	int* resX = new int; *resX = 2560; float resY2 = 1440;
	GLFWwindow* window = glfwCreateWindow(*resX, *resY, "Engine by @dev_ninis", NULL, NULL);
	if (window == NULL) { 
		std::cout << "failed to initialise glad " << std::endl; 
		return -1; 
	}
	glfwMakeContextCurrent(window);
	// set glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << " failed to initialise glad " << std::endl;
		return -1;
	}
	// 
	glViewport(0, 0, *resX, *resY);
	float FOV = 45.0f;
	delete resX; delete resY;
	cube* Cube; Cube = new cube;
	glmAnimation3D* matrixAnimation; matrixAnimation = new glmAnimation3D;
	// initialise imgui
	UserInterface* Interface = nullptr; Interface = new UserInterface(window); // in the builder of this class they create a imgui context is because in argument they have GLFWwindow* ...
	//
	Cube->setShader();
	Cube->setBuffer();
	Cube->setTexture();
	while (!glfwWindowShouldClose(window)) // render
	{
		processInput(window);
		glClearColor(0.9f, 0.33f, 0.25f, 0.9f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Interface->setSettingFrame();
		Interface->BasicFonction();
		Interface->BasicFonction();
		Cube->useShaderCube();
		matrixAnimation->initialiseMatrix();
		matrixAnimation->setModelProjection();
		matrixAnimation->setViewProjection();
		matrixAnimation->setMatrixPerspectiveProjection(FOV, resX2, resY2);
		matrixAnimation->setTransformValue();
		matrixAnimation->frameMatrix(Cube->getshaderCube());
		Cube->drawElements();
		glEnable(GL_DEPTH_TEST);
		Interface->endFrame();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	Interface->~UserInterface();
	Cube->~cube();
	delete Cube;

}
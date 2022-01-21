#include <iostream>
#include <string>
#include "cube.h"
#include "stbi_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
	int* resY = new int; *resY = 1440;
	int* resX = new int; *resX = 2560;
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
	delete resX; delete resY;
	cube* Cube; Cube = new cube;
	Cube->setShader();
	Cube->setBuffer();
	Cube->setTexture();
	while (!glfwWindowShouldClose(window)) // render
	{
		processInput(window);
		glClearColor(0.9f, 0.33f, 0.25f, 0.9f);
		glClear(GL_COLOR_BUFFER_BIT);
		Cube->drawElements();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete Cube;

}
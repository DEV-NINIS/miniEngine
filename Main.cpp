#include <iostream>
#include <string>
#include "cube.h"
#include "stbi_image.h"
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
	Cube->setShader();
	Cube->setBuffer();
	Cube->setTexture();
	while (!glfwWindowShouldClose(window)) // render
	{
		processInput(window);
		glClearColor(0.9f, 0.33f, 0.25f, 0.9f);
		glClear(GL_COLOR_BUFFER_BIT);
		Cube->useShaderCube();
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		glm::mat4 transform = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::translate(view, glm::vec3(1.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)resX2 / (float)resY2, 0.1f, 100.0f);
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(-0.0f, 0.0f, 0.0f));
		transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(1.0f, 1.0, 1.0f));
		glUniformMatrix4fv(glGetAttribLocation(Cube->getshaderCube(), "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetAttribLocation(Cube->getshaderCube(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetAttribLocation(Cube->getshaderCube(), "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetAttribLocation(Cube->getshaderCube(), "transform"), 1, GL_FALSE, glm::value_ptr(transform));
		matrixAnimation->initialiseMatrix();
		matrixAnimation->setModelProjection();
		matrixAnimation->setViewProjection();
		matrixAnimation->setMatrixPerspectiveProjection(FOV, resX2, resY2);
		Cube->drawElements();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	Cube->~cube();
	delete Cube;

}
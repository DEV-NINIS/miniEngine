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
	bool drawingCube = true;
	float lastedLoadFrameX = 1.0f; float lastedLoadFrameY = 1.0f; float lastedLoadFrameZ = 1.0f;
	int* IndicatorScaleDemanding = nullptr; IndicatorScaleDemanding = new int; *IndicatorScaleDemanding = 0;
	int* IndicatorScaleDemandingX = nullptr; IndicatorScaleDemandingX = new int; *IndicatorScaleDemandingX = 0;
	int* IndicatorScaleDemandingY = nullptr; IndicatorScaleDemandingY = new int; *IndicatorScaleDemandingY = 0;
	int* IndicatorScaleDemandingZ = nullptr; IndicatorScaleDemandingZ = new int; *IndicatorScaleDemandingZ = 0;
	cube* Cube; Cube = new cube;
	glmAnimation3D* matrixAnimation; matrixAnimation = new glmAnimation3D(window);
	// initialise imgui
	UserInterface* Interface = nullptr; Interface = new UserInterface(window); // in the builder of this class they create a imgui context is because in argument they have GLFWwindow* ...
	//
	Cube->setShader();
	Cube->setBuffer();
	Cube->setTexture();
	Interface->LastedFloatFrame = 1;
	while (!glfwWindowShouldClose(window)) // render
	{
		processInput(window);
		glClearColor(0.4f, 0.1f, 0.9f, 0.2f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Interface->setSettingFrame();
		Cube->useShaderCube();
		matrixAnimation->initialiseMatrix();
		matrixAnimation->setModelProjection();
		matrixAnimation->setViewProjection();
		matrixAnimation->setMatrixPerspectiveProjection(FOV, resX2, resY2);
		matrixAnimation->setTransformValue();
		matrixAnimation->setRotateLeft(-45.0f);
		matrixAnimation->setScaleValue(Cube->getshaderCube(), Interface->LastedFloatFrame);
		ImGui::Checkbox(" draw ", &drawingCube);
		// echelle du cube
		if (Interface->inputDemandingScaleCube() == true) {
			*IndicatorScaleDemanding = *IndicatorScaleDemanding + 1;
		}
		if (*IndicatorScaleDemanding == 1) {
			if (*IndicatorScaleDemandingX == 0 && *IndicatorScaleDemandingY == 0 && *IndicatorScaleDemandingZ == 0) {
				Interface->setScaleCube();
				matrixAnimation->setScaleValue(Cube->getshaderCube(), Interface->LastedFloatFrame);
				if (Interface->inputDemandingScaleCubeX() == true) {
					*IndicatorScaleDemandingX = *IndicatorScaleDemandingX + 1;
				}
				else if (Interface->inputDemandingScaleCubeY() == true) {
					*IndicatorScaleDemandingY = *IndicatorScaleDemandingY + 1;
				}
				else if (Interface->inputDemandingScaleCubeZ() == true) {
					*IndicatorScaleDemandingZ = *IndicatorScaleDemandingZ + 1;
				}
			}
			// demand x
			if (*IndicatorScaleDemandingX == 1) {
				if (Interface->inputDemandingScaleCubeX() == true) {
					*IndicatorScaleDemandingX = *IndicatorScaleDemandingX + 1;
				}
				matrixAnimation->setScaleValueX(Cube->getshaderCube());
				matrixAnimation->setScaleValue(Cube->getshaderCube(), Interface->LastedFloatFrame);
				matrixAnimation->frameMatrix(Cube->getshaderCube());
			}
			else if (*IndicatorScaleDemandingX > 1) {
				*IndicatorScaleDemandingX = 0;
			}
			// demand y
			if (*IndicatorScaleDemandingY == 1) {
				if (Interface->inputDemandingScaleCubeY() == true) {
					*IndicatorScaleDemandingY = *IndicatorScaleDemandingY + 1;
				}
				lastedLoadFrameX = matrixAnimation->setScaleValueY(Cube->getshaderCube());
				matrixAnimation->setScaleValue(Cube->getshaderCube(), Interface->LastedFloatFrame);
				matrixAnimation->frameMatrix(Cube->getshaderCube());
			}
			else if (*IndicatorScaleDemandingY > 1) {
				*IndicatorScaleDemandingY = 0;
			}
			// demand z
			if (*IndicatorScaleDemandingZ == 1) {
				if (Interface->inputDemandingScaleCubeZ() == true) {
					*IndicatorScaleDemandingZ = *IndicatorScaleDemandingZ + 1;
				}
				matrixAnimation->setScaleValueZ(Cube->getshaderCube());
				matrixAnimation->setScaleValue(Cube->getshaderCube(), Interface->LastedFloatFrame);
				matrixAnimation->frameMatrix(Cube->getshaderCube());
			}
			else if (*IndicatorScaleDemandingZ > 1) {
				*IndicatorScaleDemandingZ = 0;
			}
			std::cout << Interface->LastedFloatFrame << std::endl;
			std::cout << Interface->LastedFloatFrameX << std::endl;
			std::cout << Interface->LastedFloatFrameY << std::endl;
			std::cout << Interface->LastedFloatFrameZ << std::endl;
			matrixAnimation->setScaleValue(Cube->getshaderCube(), Interface->LastedFloatFrame);
		}
		else if (*IndicatorScaleDemanding == 2) {
			*IndicatorScaleDemanding = 0;
		}
		//
		matrixAnimation->setScaleValue(Cube->getshaderCube(), Interface->LastedFloatFrame);
		matrixAnimation->frameMatrix(Cube->getshaderCube());
		if (drawingCube == true) {
			Cube->drawElements();
		}
		glEnable(GL_DEPTH_TEST);
		Interface->endFrame();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	Interface->~UserInterface();
	Cube->~cube();
	delete Cube; 
	delete IndicatorScaleDemanding; delete IndicatorScaleDemandingX; 
	delete IndicatorScaleDemandingY; delete IndicatorScaleDemandingZ;

}
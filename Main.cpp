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
	float FOV = 45.0f; float RotateValue = -55.0f;
	delete resX; delete resY;
	bool drawingCube = true;
	int* IndicatorDemandingRotate = nullptr; IndicatorDemandingRotate = new int; *IndicatorDemandingRotate = 0;
	int* IndicatorDemandingRotateRight = nullptr; IndicatorDemandingRotateRight = new int; *IndicatorDemandingRotateRight = 0;
	int* IndicatorDemandingRotateLeft = nullptr; IndicatorDemandingRotateLeft = new int; *IndicatorDemandingRotateLeft = 0;
	int* IndicatorDemandingAnimation = nullptr; IndicatorDemandingAnimation = new int; *IndicatorDemandingAnimation = 0;
	int* IndicatorSetColorFrameDemanding = nullptr; IndicatorSetColorFrameDemanding = new int; *IndicatorSetColorFrameDemanding = 0;
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
	float valueXColor = 0.2f; float ValueYcolor = 0.6f; float ValueZColor = 0.9f; float ValueWColor = 0.1f;
	while (!glfwWindowShouldClose(window)) // render
	{
		processInput(window);
		glClearColor(valueXColor, ValueYcolor, ValueZColor, ValueWColor);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		Cube->useShaderCube();
		matrixAnimation->initialiseMatrix();
		matrixAnimation->setViewProjection();
		matrixAnimation->setModelProjection(RotateValue);
		matrixAnimation->setMatrixPerspectiveProjection(FOV, resX2, resY2);
		matrixAnimation->setTransformValue();
		matrixAnimation->setRotateLeft(-45.0f);
		matrixAnimation->setScaleValue(Cube->getshaderCube(), Interface->LastedFloatFrame);
		ImGui::Begin("Engine");
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
				Interface->setLastedmatrix();
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
				Interface->setLastedmatrix();
				matrixAnimation->setScaleValueY(Cube->getshaderCube());
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
				Interface->setLastedmatrix();
				matrixAnimation->setScaleValueZ(Cube->getshaderCube());
				matrixAnimation->setScaleValue(Cube->getshaderCube(), Interface->LastedFloatFrame);
				matrixAnimation->frameMatrix(Cube->getshaderCube());
			}
			else if (*IndicatorScaleDemandingZ > 1) {
				*IndicatorScaleDemandingZ = 0;
			}
			matrixAnimation->setScaleValue(Cube->getshaderCube(), Interface->LastedFloatFrame);
		}
		else if (*IndicatorScaleDemanding == 2) {
			*IndicatorScaleDemanding = 0;
		}
		//
		matrixAnimation->setScaleValue(Cube->getshaderCube(), Interface->LastedFloatFrame);
		matrixAnimation->frameMatrix(Cube->getshaderCube());
		// Animation
		if (Interface->inputDemandingAnimation() == true) {
			*IndicatorDemandingAnimation = *IndicatorDemandingAnimation + 1;
		}
		if (*IndicatorDemandingAnimation == 1) {
			if (Interface->inputDemandingRotate() == true) {
				*IndicatorDemandingRotate = *IndicatorDemandingRotate + 1;
			}
			if (*IndicatorDemandingRotate == 1) {
				// rotate right or left
				if (Interface->inputDemandingRotateRight() == true) {
					*IndicatorDemandingRotateRight = *IndicatorDemandingRotateRight + 1;
				}
				if (*IndicatorDemandingRotateRight == 1) {
					// fonction
					RotateValue += 1;
					matrixAnimation->setModelProjection(RotateValue);
				}
				else if (*IndicatorDemandingRotateRight > 1) {
					*IndicatorDemandingRotateRight = 0;
				}
				if (Interface->inputDemandingRotateLeft() == true) {
					*IndicatorDemandingRotateLeft = *IndicatorDemandingRotateLeft + 1;
				}
				if (*IndicatorDemandingRotateLeft == 1) {
					// fonction
					RotateValue -= 1;
					matrixAnimation->setModelProjection(RotateValue);
				}
				else if (*IndicatorDemandingRotateLeft > 1) {
					*IndicatorDemandingRotateLeft = 0;
				}
			}
			else if (*IndicatorDemandingRotate > 1) {
				*IndicatorDemandingRotate = 0;
			}
		}
		else if (*IndicatorDemandingAnimation > 1) {
			*IndicatorDemandingAnimation = 0;
		}
		// settings 
		if (Interface->setSettings() == true) {
			*IndicatorSetColorFrameDemanding = *IndicatorSetColorFrameDemanding + 1;
		}
		if (*IndicatorSetColorFrameDemanding == 1) {
			matrixAnimation->setColorValueFrame();
		}
		else if (*IndicatorSetColorFrameDemanding >= 2)
		{
			*IndicatorSetColorFrameDemanding = 0;
		}
		if (drawingCube == true) {
			Cube->drawElements();
		}
		ImGui::End();
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
	delete IndicatorDemandingRotate; delete IndicatorDemandingRotateLeft;
	delete IndicatorDemandingRotateRight; delete IndicatorDemandingAnimation;
	delete IndicatorSetColorFrameDemanding;

}
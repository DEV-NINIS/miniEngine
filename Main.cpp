#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>  // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>  // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include <iostream>
#include <string>
#include "cube.h"
#include "stbi_image.h"
#include "file.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "UserInterface.h"
#include "imgui/imgui_impl_opengl3.h"
#include "glmAnimation3D.h"
#include "Camera.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <commdlg.h>
#include <shellapi.h>
#include <fileapi.h>
#include <commdlg.h>
#include <filesystem> // C++17 standard header file name
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
char* unconstchar(const char* s) {
	if (!s)
		return NULL;
	int i;
	char* res = NULL;
	res = (char*)malloc(strlen(s) + 1);
	if (!res) {
		fprintf(stderr, "Memory Allocation Failed! Exiting...\n");
		exit(EXIT_FAILURE);
	}
	else {
		for (i = 0; s[i] != '\0'; i++) {
			res[i] = s[i];
		}
		res[i] = '\0';
		return res;
	}
}
int main() {
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
	FreeConsole();
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
	glViewport(2560/4.5, 0, *resX, *resY);
	float FOV = 55.0f; float RotateValue = -55.0f;
	delete resX; delete resY;
	bool drawingCube = true;
	char* filePathTex1; filePathTex1 = new char;
	char* filePathTex2; filePathTex2 = new char;
	int indicatorNumberTexVector = 0;
	int* IndicatorDemandCamera = nullptr; IndicatorDemandCamera = new int; *IndicatorDemandCamera = 0;
	int* IndicatorDemandChangeCameraSpeed = nullptr; IndicatorDemandChangeCameraSpeed = new int; *IndicatorDemandChangeCameraSpeed = 0;
	int* IndicatorChgangePositionCube = nullptr; IndicatorChgangePositionCube = new int; *IndicatorChgangePositionCube = 0;
	int* IndicatorChgangePositionCubeX = nullptr; IndicatorChgangePositionCubeX = new int; *IndicatorChgangePositionCubeX = 0;
	int* IndicatorChgangePositionCubeY = nullptr; IndicatorChgangePositionCubeY = new int; *IndicatorChgangePositionCubeY = 0;
	int* IndicatorChgangePositionCubeZ = nullptr; IndicatorChgangePositionCubeZ = new int; *IndicatorChgangePositionCubeZ = 0;
	int* IndicatorDemandingChangeCubePosition = nullptr; IndicatorDemandingChangeCubePosition = new int; *IndicatorDemandingChangeCubePosition = 0;
	int* IndicatorDemandingChangeCubePositionX = nullptr; IndicatorDemandingChangeCubePositionX = new int; *IndicatorDemandingChangeCubePositionX = 0;
	int* IndicatorDemandingChangeCubePositionY = nullptr; IndicatorDemandingChangeCubePositionY = new int; *IndicatorDemandingChangeCubePositionY = 0;
	int* IndicatorDemandingChangeCubePositionZ = nullptr; IndicatorDemandingChangeCubePositionZ = new int; *IndicatorDemandingChangeCubePositionZ = 0;
	int* IndicatorDemandingChangeColorCube = nullptr; IndicatorDemandingChangeColorCube = new int; *IndicatorDemandingChangeColorCube = 0;
	int* IndicatorDemandingChangeColorCubeR = nullptr; IndicatorDemandingChangeColorCubeR = new int; *IndicatorDemandingChangeColorCubeR = 0;
	int* IndicatorDemandingChangeColorCubeG = nullptr; IndicatorDemandingChangeColorCubeG = new int; *IndicatorDemandingChangeColorCubeG = 0;
	int* IndicatorDemandingChangeColorCubeB = nullptr; IndicatorDemandingChangeColorCubeB = new int; *IndicatorDemandingChangeColorCubeB = 0;
	int* IndicatorDemandingChangeFOV = nullptr; IndicatorDemandingChangeFOV = new int; *IndicatorDemandingChangeFOV = 0;
	int* IndicatorDemandingColorR = nullptr; IndicatorDemandingColorR = new int; *IndicatorDemandingColorR = 0;
	int* IndicatorDemandingColorG = nullptr; IndicatorDemandingColorG = new int; *IndicatorDemandingColorG = 0;
	int* IndicatorDemandingColorB = nullptr; IndicatorDemandingColorB = new int; *IndicatorDemandingColorB = 0;
	int* IndicatorDemandingTexture = nullptr; IndicatorDemandingTexture = new int; *IndicatorDemandingTexture = 0;
	int* IndicatorDemandingRotateAroundX = nullptr; IndicatorDemandingRotateAroundX = new int; *IndicatorDemandingRotateAroundX = 0;
	int* IndicatorDemandingRotateAroundY = nullptr; IndicatorDemandingRotateAroundY = new int; *IndicatorDemandingRotateAroundY = 0;
	int* IndicatorDemandingRotateAroundZ = nullptr; IndicatorDemandingRotateAroundZ = new int; *IndicatorDemandingRotateAroundZ = 0;
	int* IndicatorDemandingRotate = nullptr; IndicatorDemandingRotate = new int; *IndicatorDemandingRotate = 0;
	int* IndicatorDemandingRotateRight = nullptr; IndicatorDemandingRotateRight = new int; *IndicatorDemandingRotateRight = 0;
	int* IndicatorDemandingRotateLeft = nullptr; IndicatorDemandingRotateLeft = new int; *IndicatorDemandingRotateLeft = 0;
	int* IndicatorDemandingAnimation = nullptr; IndicatorDemandingAnimation = new int; *IndicatorDemandingAnimation = 0;
	int* IndicatorSetColorFrameDemanding = nullptr; IndicatorSetColorFrameDemanding = new int; *IndicatorSetColorFrameDemanding = 0;
	int* IndicatorScaleDemanding = nullptr; IndicatorScaleDemanding = new int; *IndicatorScaleDemanding = 0;
	int* IndicatorScaleDemandingX = nullptr; IndicatorScaleDemandingX = new int; *IndicatorScaleDemandingX = 0;
	int* IndicatorScaleDemandingY = nullptr; IndicatorScaleDemandingY = new int; *IndicatorScaleDemandingY = 0;
	int* IndicatorScaleDemandingZ = nullptr; IndicatorScaleDemandingZ = new int; *IndicatorScaleDemandingZ = 0;
	int indicatorFolderTexture1 = 0; int indicatorFolderTexture2 = 0;
	const char* filePath;
	cube* Cube; Cube = new cube(window);
	glmAnimation3D* matrixAnimation; matrixAnimation = new glmAnimation3D(window);
	// initialise imgui
	UserInterface* Interface = nullptr; Interface = new UserInterface(window); // in the builder of this class they create a imgui context is because in argument they have GLFWwindow* ...
	std::string formatFile; formatFile = ".dev_ninis";
	Camera camera; writing::save Save; reading::read Read;
	int* IndicatorFilepath = nullptr; IndicatorFilepath = new int; *IndicatorFilepath = Interface->getIndicatorTextureFilePath();
	Cube->setShader();
	Cube->setBuffer();
	Cube->setTexture1(Interface->filePathPointer[0]);
	Interface->LastedFloatFrame = 1;
	float valueXColor = 0.2f; float ValueYcolor = 0.6f; float ValueZColor = 0.9f; float ValueWColor = 0.1f;
	float deltatime = 0, currentFrame = 0, lastedFrame = 0;
	TCHAR filepath = 100; char filePathBuffer[100]; filePathBuffer[100];
	TCHAR nBufferLength = 102; char lpFileName[2]; char* lpFilePart = nullptr; lpFilePart = &filePathBuffer[1];
	while (!glfwWindowShouldClose(window)) // render
	{
		currentFrame = glfwGetTime();
		deltatime = currentFrame - lastedFrame;
		lastedFrame = currentFrame;
		processInput(window);
		glClearColor(Interface->getColorR(), Interface->getColorG(), Interface->getColorB(), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera.processInputCamera(window, deltatime, Interface->getCmerraSpeed());
		Cube->useShaderCube();
		matrixAnimation->initialiseMatrix();
		matrixAnimation->setLookAtMatrixCamera(camera.getcamPos(), camera.getcamFront(), camera.getcamUp());
		matrixAnimation->setRotateLeft(RotateValue, Interface->getValueRotateX(), Interface->getValueRotateY(), Interface->getValueRotateZ());
		matrixAnimation->setMatrixPerspectiveProjection(FOV, resX2, resY2);
		matrixAnimation->setTransformValue();
		matrixAnimation->setScaleValue(Cube->getshaderCube(), Interface->LastedFloatFrame);
		Interface->setSettingFrame();
		Interface->interfacebeginCanvas();
		matrixAnimation->setPercentTexture(Cube->getshaderCube(), Interface->getpercentTexture());
		ImGui::Begin("Engine");
		ImGui::Columns(2);
		ImGui::SetColumnOffset(1, 2560/4/2);

		{
			//Left side
			if (ImGui::BeginMainMenuBar()) {
				if (ImGui::BeginMenu("file")) {
					if (ImGui::MenuItem("Open")) {
						Read.setValueFile(Read.selectPath(window));

						Interface = new UserInterface(window, Read.getValueColorFrameRFile(), Read.getValueColorFrameGFile(), Read.getValueColorFrameBFile(),
							Read.getLastedScaleXFile(), Read.getLastedScaleYFile(), Read.getLastedScaleZFile(), Read.getValueTransformXFile(),
							Read.getValueTransformYFile(), Read.getValueTransformZFile(), Read.getcolorObjectFileR(),
							Read.getcolorObjectFileG(), Read.getcolorObjectFileB(), Read.getValuePositionObjectFileX(), Read.getValuePositionObjectFileY(),
							Read.getValuePositionObjectFileZ(), Read.getValueCameraSpeedFile(), Read.getfiletextureFile());
						matrixAnimation->frameMatrix(Cube->getshaderCube());
						Cube->setTexture1(Interface->filePathPointer[0]);
						Cube->setTexture2(Interface->filePathPointer[0]);
						matrixAnimation->setPercentTexture(Cube->getshaderCube(), Interface->getpercentTexture());
						matrixAnimation->setScaleValue(Cube->getshaderCube(), Interface->LastedFloatFrame);
						matrixAnimation->setPositionObject(Cube->getshaderCube(), Interface->getPositionObjectX(), Interface->getPositionObjectY(), Interface->getPositionObjectZ());
						matrixAnimation->setColorObject(Cube->getshaderCube(), Interface->getColorObjectR(), Interface->getColorObjectG(), Interface->getColorObjectB());
						matrixAnimation->setRotateLeft(RotateValue, Interface->getValueRotateX(), Interface->getValueRotateY(), Interface->getValueRotateZ());
					}
					if (ImGui::MenuItem("Save")) {
						Save.setFileContent(Cube->getfinalPathTexture()[0], Interface->getColorObjectR(),
							Interface->getColorObjectG(), Interface->getColorObjectB(), Interface->getPositionObjectX(), Interface->getPositionObjectY()
							, Interface->getPositionObjectZ(), Interface->getValueRotateX(), Interface->getValueRotateY(), Interface->getValueRotateZ()
							, Interface->getColorR(), Interface->getColorG(), Interface->getColorB(), Interface->getCmerraSpeed(), Interface->getFOV_Value()
							, Interface->getScaleCubeX(), Interface->getScaleCubeY(), Interface->getScaleCubeZ(), Read.getLastedFilepath());
					}
					if (ImGui::MenuItem("Save as")) {

						Save.setFileContent(Cube->getfinalPathTexture()[0], Interface->getColorObjectR(),
							Interface->getColorObjectG(), Interface->getColorObjectB(), Interface->getPositionObjectX(), Interface->getPositionObjectY()
							, Interface->getPositionObjectZ(), Interface->getValueRotateX(), Interface->getValueRotateY(), Interface->getValueRotateZ()
							, Interface->getColorR(), Interface->getColorG(), Interface->getColorB(), Interface->getCmerraSpeed(), Interface->getFOV_Value()
							, Interface->getScaleCubeX(), Interface->getScaleCubeY(), Interface->getScaleCubeZ(), Save.setFilePath(window) + formatFile);
					}
					if (ImGui::MenuItem("Wiew Source Code ")) {
						ShellExecuteA(NULL, "open", "https://github.com/DEV-NINIS/miniEngine", NULL, NULL, SW_SHOWDEFAULT);
					}
					ImGui::EndMenu();
				}
				ImGui::EndMainMenuBar();
			}
			// end menubar



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
			// position cube
			if (Interface->inputDemandingPositionObject() == true) {
				*IndicatorChgangePositionCube = *IndicatorChgangePositionCube + 1;
			}
			if (*IndicatorChgangePositionCube == 1) {
				// fonction
				// x
				if (Interface->inputDemandingPositionObjectX() == true) {
					*IndicatorChgangePositionCubeX = *IndicatorChgangePositionCubeX + 1;
				}
				if (*IndicatorChgangePositionCubeX == 1) {
					// fonction
					Interface->setPositionObjectX();
					matrixAnimation->setPositionObject(Cube->getshaderCube(), Interface->getPositionObjectX(), Interface->getPositionObjectY(), Interface->getPositionObjectZ());
				}
				else if (*IndicatorChgangePositionCubeX > 1) {
					*IndicatorChgangePositionCubeX = 0;
				}
				// y
				if (Interface->inputDemandingPositionObjectY() == true) {
					*IndicatorChgangePositionCubeY = *IndicatorChgangePositionCubeY + 1;
				}
				if (*IndicatorChgangePositionCubeY == 1) {
					// fonction
					Interface->setPositionObjectY();
					matrixAnimation->setPositionObject(Cube->getshaderCube(), Interface->getPositionObjectX(), Interface->getPositionObjectY(), Interface->getPositionObjectZ());
				}
				else if (*IndicatorChgangePositionCubeY > 1) {
					*IndicatorChgangePositionCubeY = 0;
				}
				// z
				if (Interface->inputDemandingPositionObjectZ() == true) {
					*IndicatorChgangePositionCubeZ = *IndicatorChgangePositionCubeZ + 1;
				}
				if (*IndicatorChgangePositionCubeZ == 1) {
					// fonction
					Interface->setPositionObjectZ();
					matrixAnimation->setPositionObject(Cube->getshaderCube(), Interface->getPositionObjectX(), Interface->getPositionObjectY(), Interface->getPositionObjectZ());
				}
				else if (*IndicatorChgangePositionCubeZ > 1) {
					*IndicatorChgangePositionCubeZ = 0;
				}
				matrixAnimation->setPositionObject(Cube->getshaderCube(), Interface->getPositionObjectX(), Interface->getPositionObjectY(), Interface->getPositionObjectZ());
			}
			else if (*IndicatorChgangePositionCube > 1) {
				*IndicatorChgangePositionCube = 0;
			}
			// Animation
			if (Interface->ButtonForSetAnimation() == true) {
				*IndicatorDemandingAnimation = *IndicatorDemandingAnimation + 1;
			}
			if (*IndicatorDemandingAnimation == 1) {
				if (Interface->inputDemandingRotate() == true) {
					*IndicatorDemandingRotate = *IndicatorDemandingRotate + 1;
				}
				if (*IndicatorDemandingRotate == 1) {
					// x
					if (Interface->inputDemandingRotateAroundX() == true) {
						*IndicatorDemandingRotateAroundX = *IndicatorDemandingRotateAroundX + 1;
					}
					if (*IndicatorDemandingRotateAroundX == 1) {
						Interface->setRotateAroundXValue();
						matrixAnimation->setRotateLeft(RotateValue, Interface->getValueRotateX(), Interface->getValueRotateY(), Interface->getValueRotateZ());

					}
					else if (*IndicatorDemandingRotateAroundX > 1) {
						*IndicatorDemandingRotateAroundX = 0;
					}
					// y
					if (Interface->inputDemandingRotateAroundY() == true) {
						*IndicatorDemandingRotateAroundY = *IndicatorDemandingRotateAroundY + 1;
					}
					if (*IndicatorDemandingRotateAroundY == 1) {
						Interface->setRotateAroundYValue();
						matrixAnimation->setRotateLeft(RotateValue, Interface->getValueRotateX(), Interface->getValueRotateY(), Interface->getValueRotateZ());

					}
					else if (*IndicatorDemandingRotateAroundY > 1) {
						*IndicatorDemandingRotateAroundY = 0;
					}
					// z
					if (Interface->inputDemandingRotateAroundZ() == true) {
						*IndicatorDemandingRotateAroundZ = *IndicatorDemandingRotateAroundZ + 1;
					}
					if (*IndicatorDemandingRotateAroundZ == 1) {
						Interface->setRotateAroundZValue();
						matrixAnimation->setRotateLeft(RotateValue, Interface->getValueRotateX(), Interface->getValueRotateY(), Interface->getValueRotateZ());

					}
					else if (*IndicatorDemandingRotateAroundZ > 1) {
						*IndicatorDemandingRotateAroundZ = 0;
					}
					// rotate right or left
					if (Interface->inputDemandingRotateRight() == true) {
						*IndicatorDemandingRotateRight = *IndicatorDemandingRotateRight + 1;
					}
					if (*IndicatorDemandingRotateRight == 1) {
						// fonction
						RotateValue += 1;
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
			if (Interface->inputDemandingChangeColorObject() == true) {
				*IndicatorDemandingChangeColorCube = *IndicatorDemandingChangeColorCube + 1;
			}
			if (*IndicatorDemandingChangeColorCube == 1) {
				// colors
				if (Interface->inputColorR() == true) {
					*IndicatorDemandingChangeColorCubeR = *IndicatorDemandingChangeColorCubeR + 1;
				}
				if (*IndicatorDemandingChangeColorCubeR == 1) {
					//fonction 
					Interface->setColorObjectR();
				}
				else if (*IndicatorDemandingChangeColorCubeR > 1) {
					*IndicatorDemandingChangeColorCubeR = 0;
				}
				if (Interface->inputColorG() == true) {
					*IndicatorDemandingChangeColorCubeG = *IndicatorDemandingChangeColorCubeG + 1;
				}
				if (*IndicatorDemandingChangeColorCubeG == 1) {
					// fonction
					Interface->setColorObjectG();
				}
				else if (*IndicatorDemandingChangeColorCubeG > 1) {
					*IndicatorDemandingChangeColorCubeG = 0;
				}
				if (Interface->inputColorB() == true) {
					*IndicatorDemandingChangeColorCubeB = *IndicatorDemandingChangeColorCubeB + 1;
				}
				if (*IndicatorDemandingChangeColorCubeB == 1) {
					// fonction 
					Interface->setColorObjectB();
				}
				else if (*IndicatorDemandingChangeColorCubeB > 1) {
					*IndicatorDemandingChangeColorCubeB = 0;
				}
				matrixAnimation->setColorObject(Cube->getshaderCube(), Interface->getColorObjectR(), Interface->getColorObjectG(), Interface->getColorObjectB());
			}
			else if (*IndicatorDemandingChangeColorCube > 1) {
				*IndicatorDemandingChangeColorCube = 0;
			}
			// texture
			if (Interface->inputDemandingTexture1() == true) {
				*IndicatorDemandingTexture = *IndicatorDemandingTexture + 1;
			}
			if (*IndicatorDemandingTexture == 1) {
				if (Interface->inputDemandSelectFolderForTex1() == true) {
					indicatorFolderTexture1 = 1;
					filePathTex1 = unconstchar(static_cast<const char*>(Read.selectPath(window).c_str()));
				}
				if (indicatorFolderTexture1 == 1) {
					Interface->inputFileTexture1(filePathTex1);
				}
				if (Interface->inputDemandSelectFolderForTex2() == true) {
					indicatorFolderTexture2 = 1;
					filePathTex2 = unconstchar(static_cast<const char*>(Read.selectPath(window).c_str()));
				}
				if (indicatorFolderTexture2 == 1) {
					Interface->inputFileTexture2(filePathTex2);
				}
				Interface->setPercentTexture();
				if (Interface->confirmFilePath() == true) {
					Cube->setTexture1(filePathTex1);
					Cube->setTexture2(filePathTex2);
				}
				matrixAnimation->setPercentTexture(Cube->getshaderCube(), Interface->getpercentTexture());
				Cube->setParametterTexture();
			}
			else if (*IndicatorDemandingTexture > 1) {
				*IndicatorDemandingTexture = 0;
			}

			
		}
		ImGui::NextColumn();


		// menubar
		
		// settings 
		// colors
		if (Interface->inputDemandingChangeColorFrame() == true) {
			*IndicatorSetColorFrameDemanding = *IndicatorSetColorFrameDemanding + 1;
		}
		if (*IndicatorSetColorFrameDemanding == 1) {

			if (Interface->inputColorR() == true) {
				*IndicatorDemandingColorR = *IndicatorDemandingColorR + 1;
			}
			if (*IndicatorDemandingColorR == 1) {
				Interface->setColorR();
			}
			else if (*IndicatorDemandingColorR > 1) {
				*IndicatorDemandingColorR = 0;
			}

			if (Interface->inputColorG() == true) {
				*IndicatorDemandingColorG = *IndicatorDemandingColorG + 1;
			}
			if (*IndicatorDemandingColorG == 1) {
				Interface->setColorG();
			}
			else if (*IndicatorDemandingColorG > 1) {
				*IndicatorDemandingColorG = 0;
			}

			if (Interface->inputColorB() == true) {
				*IndicatorDemandingColorB = *IndicatorDemandingColorB + 1;
			}
			if (*IndicatorDemandingColorB == 1) {
				Interface->setColorB();
			}
			else if (*IndicatorDemandingColorB > 1) {
				*IndicatorDemandingColorB = 0;
			}
		}
		else if (*IndicatorSetColorFrameDemanding > 1)
		{
			*IndicatorSetColorFrameDemanding = 0;
		}
		// camera
		if (Interface->inputDemandingCamera() == true) {
			*IndicatorDemandCamera = *IndicatorDemandCamera + 1;
		}
		if (*IndicatorDemandCamera == 1) {
			// FONCTION
			if (Interface->inputDemandCameraSpeed() == true) {
				*IndicatorDemandChangeCameraSpeed = *IndicatorDemandChangeCameraSpeed + 1;
			}
			if (*IndicatorDemandChangeCameraSpeed == 1) {
				Interface->setCameraSpeed();
			}
			else if (*IndicatorDemandChangeCameraSpeed > 1) {
				*IndicatorDemandChangeCameraSpeed = 0;
			}
			ImGui::Text("press E to forward");
			ImGui::Text("press D to move back");
			ImGui::Text("press S to move right");
			ImGui::Text("press F to move left");
		}
		else if (*IndicatorDemandCamera > 1) {
			*IndicatorDemandCamera = 0;
		}
		// FOV
		if (Interface->inputDemandingChangeFOV() == true) {
			*IndicatorDemandingChangeFOV = *IndicatorDemandingChangeFOV + 1;
		}
		if (*IndicatorDemandingChangeFOV == 1) {
			Interface->setChangeFOV();
			FOV = Interface->getFOV_Value();
		}
		else if (*IndicatorDemandingChangeFOV > 1) {
			*IndicatorDemandingChangeFOV = 0;
		}
		ImGui::Checkbox(" draw ", &drawingCube);
		if (drawingCube == true) {
			matrixAnimation->drawAllObject(Cube->getshaderCube(), Cube->getVertexArray());
		}
		matrixAnimation->setLookAtMatrixCamera(camera.getcamPos(), camera.getcamPos() - camera.getcamFront(), camera.getcamUp());
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
	delete IndicatorSetColorFrameDemanding; delete IndicatorDemandingRotateAroundZ;
	delete IndicatorDemandingRotateAroundX; delete IndicatorDemandingRotateAroundY;
	delete IndicatorDemandingTexture; delete IndicatorDemandingColorB;
	delete IndicatorDemandingColorG; delete IndicatorDemandingColorR; delete IndicatorDemandingChangeFOV;
	delete IndicatorDemandingChangeColorCube; delete IndicatorDemandingChangeColorCubeR;
	delete IndicatorDemandingChangeColorCubeG; delete IndicatorDemandingChangeColorCubeB;
	delete IndicatorDemandingChangeCubePosition; delete IndicatorDemandingChangeCubePositionX;
	delete IndicatorDemandingChangeCubePositionY; delete IndicatorDemandingChangeCubePositionZ;
	delete IndicatorChgangePositionCube; delete IndicatorChgangePositionCubeX;
	delete IndicatorChgangePositionCubeY; delete IndicatorChgangePositionCubeZ;
	delete IndicatorDemandCamera; delete IndicatorDemandChangeCameraSpeed;
}
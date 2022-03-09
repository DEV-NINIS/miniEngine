#include <glad/glad.h>
#include <GLFW/glfw3.h>
// Initialize with gl3wInit()


#include <iostream>
#include <string>
#include "object.h"
#include "Render.h"
#include "stbi_image.h"
#include "file.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "UserInterface.h"
#include "imgui/imgui_impl_opengl3.h"
#include "glmAnimation3D.h"
#include "Camera.h"
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



static bool HOTreload = false;
//												_____
//               /\         |\		|	 |	   |
//				/  \		| \		|	 |	   |
//			   /	\		|  \	|	 |	   |_____
//			  /------\		|	\	|	 |			 |
//			 /		  \		|	 \	|	 |			 |
//			/		   \	|	  \	|	 |		_____|
//
void abc() {

}
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
	GLFWmonitor* MyMonitor = glfwGetPrimaryMonitor(); // The primary monitor.. Later Occulus?..

	const GLFWvidmode* mode = glfwGetVideoMode(MyMonitor);
	*resX = mode->width;
	*resY = mode->height;
#ifdef HOT_REALOAD
	GLFWwindow* window = glfwCreateWindow(glfwGetVideoMode(glfwGetPrimaryMonitor())->width,
		glfwGetVideoMode(glfwGetPrimaryMonitor())->height, "DevNinisEngineMotion",
		glfwGetPrimaryMonitor(), nullptr);
#endif // HOT_REALOAD
#ifndef HOT_REALOAD
	std::vector<GLFWwindow*> window; window.push_back(glfwCreateWindow(glfwGetVideoMode(glfwGetPrimaryMonitor())->width,
		glfwGetVideoMode(glfwGetPrimaryMonitor())->height, "DevNinisEngineMotion",
		nullptr, nullptr));
#endif

	if (window[0] == NULL) {
		MessageBoxA(0, static_cast<const char*>("failed to initialise glad"), "ERROR", 0);
		return -1;
	}
	glfwMakeContextCurrent(window[0]);
	// set glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		MessageBoxA(0, static_cast<const char*>("failed to initialise glad"), "ERROR", 0);
		return -1;
	}

	// 


	else {

		glViewport(*resX / 4.5, 0, *resX, *resY);

	}

	float FOV = 55.0f; float RotateValue = -55.0f;
	bool drawingCube = true;
	char* filePathTex1; filePathTex1 = new char;
	char* filePathTex2; filePathTex2 = new char;
	int indicatorNumberTexVector = 0;
	int* IndicatorDemandCamera = nullptr; IndicatorDemandCamera = new int; *IndicatorDemandCamera = 0;
	int* IndicatorDemandChangeCameraSpeed = nullptr; IndicatorDemandChangeCameraSpeed = new int; *IndicatorDemandChangeCameraSpeed = 0;
	int* IndicatorDemandingChangeFOV = nullptr; IndicatorDemandingChangeFOV = new int; *IndicatorDemandingChangeFOV = 0;
	int* IndicatorDemandingTexture = nullptr; IndicatorDemandingTexture = new int; *IndicatorDemandingTexture = 0;
	int* IndicatorDemandingRotateAroundX = nullptr; IndicatorDemandingRotateAroundX = new int; *IndicatorDemandingRotateAroundX = 0;
	int* IndicatorDemandingRotateAroundY = nullptr; IndicatorDemandingRotateAroundY = new int; *IndicatorDemandingRotateAroundY = 0;
	int* IndicatorDemandingRotateAroundZ = nullptr; IndicatorDemandingRotateAroundZ = new int; *IndicatorDemandingRotateAroundZ = 0;
	int* IndicatorDemandingRotate = nullptr; IndicatorDemandingRotate = new int; *IndicatorDemandingRotate = 0;
	int* IndicatorDemandingRotateRight = nullptr; IndicatorDemandingRotateRight = new int; *IndicatorDemandingRotateRight = 0;
	int* IndicatorDemandingRotateLeft = nullptr; IndicatorDemandingRotateLeft = new int; *IndicatorDemandingRotateLeft = 0;
	int* IndicatorDemandingAnimation = nullptr; IndicatorDemandingAnimation = new int; *IndicatorDemandingAnimation = 0;
	int indicatorFolderTexture1 = 0; int indicatorFolderTexture2 = 0;
	const char* filePath;
	basicObject::cube* Cube; Cube = new basicObject::cube(window[0]);
	glmAnimation3D* matrixAnimation; matrixAnimation = new glmAnimation3D(window[0]);
	// initialise imgui
	UserInterface* Interface = nullptr; Interface = new UserInterface(window[0]); // in the builder of this class they create a imgui context is because in argument they have GLFWwindow* ...
	if (HOTreload == false) {
		Interface->setStyleSettingFrame(window[0]);
	}
	std::string formatFile; formatFile = ".dev_ninis";
	Camera camera; writing::save Save; reading::read Read;
	Render rendering(window[0]); objectUser::Mesh mesh(window[0]);
	int* IndicatorFilepath = nullptr; IndicatorFilepath = new int; *IndicatorFilepath = Interface->getIndicatorTextureFilePath();
	Cube->setShader();
	Cube->setBuffer();
	Cube->setTexture1(Interface->filePathPointer[0]);
	Interface->LastedFloatFrame = 1;
	float valueXColor = 0.2f; float ValueYcolor = 0.6f; float ValueZColor = 0.9f; float ValueWColor = 0.1f;
	float deltatime = 0, currentFrame = 0, lastedFrame = 0;
	TCHAR filepath = 100; char filePathBuffer[100]; filePathBuffer[100];
	TCHAR nBufferLength = 102; char lpFileName[2]; char* lpFilePart = nullptr; lpFilePart = &filePathBuffer[1];
	std::string a = "VertexShaderObject.glsl"; std::string b = "FragmentShaderObject.glsl";
	while (!glfwWindowShouldClose(window[0])) // render
	{


		currentFrame = glfwGetTime();
		deltatime = currentFrame - lastedFrame;
		lastedFrame = currentFrame;
		processInput(window[0]);
		glClearColor(Interface->getColorR(), Interface->getColorG(), Interface->getColorB(), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (int i(0); i < window.size(); i++) {
			camera.processInputCamera(window[i], deltatime, Interface->getCmerraSpeed());
		}
		Cube->useShaderCube();
		matrixAnimation->initialiseMatrix();
		matrixAnimation->setLookAtMatrixCamera(camera.getcamPos(), camera.getcamFront(), camera.getcamUp());
		matrixAnimation->setRotateLeft(RotateValue, Interface->getValueRotateX(), Interface->getValueRotateY(), Interface->getValueRotateZ());
		matrixAnimation->setMatrixPerspectiveProjection(FOV, resX2, resY2);
		matrixAnimation->setTransformValue();
		matrixAnimation->frameMatrix(Cube->getshaderCube());
		matrixAnimation->setScaleValue(Cube->getshaderCube(), Interface->LastedFloatFrame);
		if (HOTreload == false) {
			Interface->setSettingFrame();
			Interface->interfacebeginCanvas();
		}
		matrixAnimation->setPercentTexture(Cube->getshaderCube(), Interface->getpercentTexture());

		if (HOTreload == false) {
			ImGui::Begin("Engine");
			if (ImGui::Button("PLAY", ImVec2(2560 / 4.5, 60.0f))) {
				HOTreload = true;
				window.push_back(glfwCreateWindow(glfwGetVideoMode(glfwGetPrimaryMonitor())->width,
					glfwGetVideoMode(glfwGetPrimaryMonitor())->height, "DevNinisEngineMotion",
					glfwGetPrimaryMonitor(), nullptr));
				glViewport(0, 0, *resX, *resY);
				
			}
			if (ImGui::CollapsingHeader("size")) {
				ImGui::Separator();
				Interface->setScaleCube();
				matrixAnimation->setScaleValue(Cube->getshaderCube(), Interface->LastedFloatFrame);
				ImGui::Separator();
				Interface->setLastedmatrix();
				matrixAnimation->setScaleValue(Cube->getshaderCube(), Interface->LastedFloatFrame);
				matrixAnimation->setScaleValueX(Cube->getshaderCube());
				matrixAnimation->frameMatrix(Cube->getshaderCube());
				ImGui::Separator();
				Interface->setLastedmatrix();
				matrixAnimation->setScaleValue(Cube->getshaderCube(), Interface->LastedFloatFrame);
				matrixAnimation->setScaleValueY(Cube->getshaderCube());
				matrixAnimation->frameMatrix(Cube->getshaderCube());
				ImGui::Separator();


				Interface->setLastedmatrix();
				matrixAnimation->setScaleValue(Cube->getshaderCube(), Interface->LastedFloatFrame);
				matrixAnimation->setScaleValueZ(Cube->getshaderCube());
				matrixAnimation->frameMatrix(Cube->getshaderCube());
				ImGui::Separator();
			}
			if (ImGui::CollapsingHeader("positions")) {
				ImGui::Spacing();
				Interface->setPositionObjectX();
				ImGui::Separator();
				matrixAnimation->setPositionObject(Cube->getshaderCube(), Interface->getPositionObjectX(), Interface->getPositionObjectY(), Interface->getPositionObjectZ());
				Interface->setPositionObjectY();
				ImGui::Separator();
				matrixAnimation->setPositionObject(Cube->getshaderCube(), Interface->getPositionObjectX(), Interface->getPositionObjectY(), Interface->getPositionObjectZ());
				Interface->setPositionObjectZ();
				ImGui::Separator();
				matrixAnimation->setPositionObject(Cube->getshaderCube(), Interface->getPositionObjectX(), Interface->getPositionObjectY(), Interface->getPositionObjectZ());
				matrixAnimation->setPositionObject(Cube->getshaderCube(), Interface->getPositionObjectX(), Interface->getPositionObjectY(), Interface->getPositionObjectZ());
			}
		}

		if (HOTreload == true) {
			matrixAnimation->setScaleValue(Cube->getshaderCube(), Interface->LastedFloatFrame);
		}





		//Left side
		if (HOTreload == false) {
			if (ImGui::BeginMainMenuBar()) {
				if (ImGui::BeginMenu("file")) {
					if (ImGui::MenuItem("Open")) {
						Read.setValueFile(Read.selectPath(window[0]));

						Interface = new UserInterface(window[0], Read.getValueColorFrameRFile(), Read.getValueColorFrameGFile(), Read.getValueColorFrameBFile(),
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
					ImGui::Spacing();
					if (ImGui::MenuItem("Save")) {
						Save.setFileContent(Cube->getfinalPathTexture()[0], Interface->getColorObjectR(),
							Interface->getColorObjectG(), Interface->getColorObjectB(), Interface->getPositionObjectX(), Interface->getPositionObjectY()
							, Interface->getPositionObjectZ(), Interface->getValueRotateX(), Interface->getValueRotateY(), Interface->getValueRotateZ()
							, Interface->getColorR(), Interface->getColorG(), Interface->getColorB(), Interface->getCmerraSpeed(), Interface->getFOV_Value()
							, Interface->getScaleCubeX(), Interface->getScaleCubeY(), Interface->getScaleCubeZ(), Read.getLastedFilepath());
					}
					ImGui::Spacing();
					if (ImGui::MenuItem("Save as")) {

						Save.setFileContent(Cube->getfinalPathTexture()[0], Interface->getColorObjectR(),
							Interface->getColorObjectG(), Interface->getColorObjectB(), Interface->getPositionObjectX(), Interface->getPositionObjectY()
							, Interface->getPositionObjectZ(), Interface->getValueRotateX(), Interface->getValueRotateY(), Interface->getValueRotateZ()
							, Interface->getColorR(), Interface->getColorG(), Interface->getColorB(), Interface->getCmerraSpeed(), Interface->getFOV_Value()
							, Interface->getScaleCubeX(), Interface->getScaleCubeY(), Interface->getScaleCubeZ(), Save.setFilePath(window[0]) + formatFile);
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

			//

			// position cube
			if (HOTreload == false) {
				ImGui::Spacing();

				ImGui::Spacing();
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
				ImGui::Spacing();
				// texture
				if (Interface->inputDemandingTexture1() == true) {
					*IndicatorDemandingTexture = *IndicatorDemandingTexture + 1;
				}
				if (*IndicatorDemandingTexture == 1) {
					if (Interface->inputDemandSelectFolderForTex1() == true) {
						indicatorFolderTexture1 = 1;
						filePathTex1 = unconstchar(static_cast<const char*>(Read.selectPath(window[0]).c_str()));
					}
					if (indicatorFolderTexture1 == 1) {
						Interface->inputFileTexture1(filePathTex1);
					}
					if (Interface->inputDemandSelectFolderForTex2() == true) {
						indicatorFolderTexture2 = 1;
						filePathTex2 = unconstchar(static_cast<const char*>(Read.selectPath(window[0]).c_str()));
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
		}

		if (HOTreload == true) {
			matrixAnimation->setRotateLeft(RotateValue, Interface->getValueRotateX(), Interface->getValueRotateY(), Interface->getValueRotateZ());
			RotateValue += 1;

		}
		if (HOTreload == false) {
			ImGui::Spacing();

			// menubar

			// settings 
			// colors
			ImGui::Spacing();
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
			ImGui::Spacing();
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
				matrixAnimation->frameMatrix(Cube->getshaderCube());
				rendering.drawElements(Cube);
			}
			matrixAnimation->setLookAtMatrixCamera(camera.getcamPos(), camera.getcamPos() - camera.getcamFront(), camera.getcamUp());
			ImGui::Columns(2);
			ImGui::SetColumnOffset(1, 2560 / 4 / 2);
			ImGui::Spacing();
			if (ImGui::CollapsingHeader("Color Object")) {
				ImGui::Spacing();
				Interface->setColorObjectR();
				ImGui::Spacing();
				Interface->setColorObjectG();
				ImGui::Spacing();
				Interface->setColorObjectB();
				ImGui::Spacing();
				matrixAnimation->setColorObject(Cube->getshaderCube(), Interface->getColorObjectR(), Interface->getColorObjectG(), Interface->getColorObjectB());
			}
			ImGui::NextColumn();
			ImGui::Spacing();
			float indicator2 = 0;
			if (ImGui::CollapsingHeader("Color Frame")) {
				float rr[3];
				ImGui::Spacing();
				Interface->setColorR();
				ImGui::Spacing();
				Interface->setColorG();
				ImGui::Spacing();
				Interface->setColorB();
				ImGui::Spacing();
				ImGui::ColorEdit3("color", rr);
			}

			ImGui::End();
			Interface->endFrame();
		}
		if (HOTreload == true) {
			matrixAnimation->frameMatrix(Cube->getshaderCube());
			rendering.drawElements(Cube);
		}
		glEnable(GL_DEPTH_TEST);
		glfwSwapBuffers(window[0]);
		glfwPollEvents();
	}
	if (HOTreload == false)
		Interface->~UserInterface();
Cube->~cube();
	delete Cube;
	delete IndicatorDemandingRotate; delete IndicatorDemandingRotateLeft;
	delete IndicatorDemandingRotateRight; delete IndicatorDemandingAnimation;
	delete IndicatorDemandingRotateAroundZ;
	delete IndicatorDemandingRotateAroundX; delete IndicatorDemandingRotateAroundY;
	delete IndicatorDemandingTexture;  delete IndicatorDemandingChangeFOV;

	delete IndicatorDemandCamera; delete IndicatorDemandChangeCameraSpeed;
}
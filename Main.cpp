#include <glad/glad.h>
#include <GLFW/glfw3.h>
// Initialize with gl3wInit()

#include <iostream>
#include <string>
#include "object.h"
#include "Render.h"
#include "Editor/imgui/imgui_node_editor.h"
#include "Time.h"
#include "Editor/imgui/imgui_bezier_math.h"
#include "stbi_image.h"
#include "file.h"
#include "Editor/imgui/imgui.h"
#include "Editor/imgui/imgui_impl_glfw.h"
#include "Editor/UserInterface.h"
#include "Editor/imgui/imgui_impl_opengl3.h"
#include "glmAnimation3D.h"
#include "Editor/icon/icons.h"
#include "Editor/icon/iconcpp.h"
#include "Editor/EditorStart.h"
#include "Editor/EditorPosition.h"
#include "Editor/EditorCamera.h"
#include "Editor/EditorSize.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <commdlg.h>
#include <shellapi.h>
#include <fileapi.h>
#include "Time.h" // this include import the time of work of animation .ect
#include <commdlg.h>
#include <filesystem> // C++17 standard header file name
#define COLOR_FRAME 1
#define COLOR_OBJECT 2

#define ADD_NODE_ROTATE_RIGHT 1
#define ADD_NODE_ROTATE_LEFT 2
#define ADD_NODE_MOVE_CAMERA_LEFT 3
#define ADD_NODE_MOVE_CAMERA_RIGHT 4
#define ADD_NODE_MOVE_CAMERA_UP 5
#define ADD_NODE_MOVE_CAMERA_DOWN 6
#define ADD_NODE_ROTATE_AROUD_X_MATRIX 7
#define ADD_NODE_ROTATE_AROUND_Y_MATRIX 8
#define ADD_NODE_ROTATE_AROUND_Z_MATRIX 9
#define ADD_NODE_CHANGE_CAMERA_SPEED 10
#define ADD_NODE_CHANGE_PERCENT_TEXTURE 11
#define ADD_NODE_CHANGE_POSITION_X 12
#define ADD_NODE_CHANGE_POSITION_Y 13
#define ADD_NODE_CHANGE_POSITION_Z 14
#define ADD_NODE_CHANGE_COLOR_FRAME 15
#define ADD_NODE_CHANGE_COLOR_OBJECT 16
#define ADD_NODE_CHANGE_FOV 17
#define ADD_NODE_CHANGE_SIZE_X 18 
#define ADD_NODE_CHANGE_SIZE_Y 19
#define ADD_NODE_CHANGE_SIZE_Z 20
#define ADD_NODE_CHANGE_DIRECTION_ROTATE_MATRIX 21
#define ADD_NODE_ALL_NODES 22


#define IN_FRAME_NOT static_cast<float>(1.0f)
#define IN_FRAME_TRUE static_cast<float>(2.0f)

#define SRC_HEIGHT glfwGetVideoMode(glfwGetPrimaryMonitor())->height
#define SRC_WIDTH glfwGetVideoMode(glfwGetPrimaryMonitor())->width


static bool HOTreload = false;
static bool IndicatorFinishLoading = false;
namespace ed = ax::NodeEditor;




void setCameraPitchYaw(GLFWwindow* window, Camera& camera, float &lastX, float &lastY) {
	lastX = (glfwGetVideoMode(glfwGetPrimaryMonitor())->width)/2;
	lastY = (glfwGetVideoMode(glfwGetPrimaryMonitor())->height) / 2;

}
void processInput(GLFWwindow* window) {

}
void ImGuiEx_BeginColumn()
{
	ImGui::BeginGroup();
}

void ImGuiEx_NextColumn()
{
	ImGui::EndGroup();
	ImGui::SameLine();
	ImGui::BeginGroup();
}

void ImGuiEx_EndColumn()
{
	ImGui::EndGroup();
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
void LoadingFonction() {
	while (!IndicatorFinishLoading) {
		std::cout << "loading..." << std::endl;
	}
}
int main() {
	std::thread threadLoad(LoadingFonction);

	// set parametters of OpenGL
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.6);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4.6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef _APPLE_
	glfwwindowhint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // _APPLE_
	const float lastX = (glfwGetVideoMode(glfwGetPrimaryMonitor())->width) / 2.0f;
	const float lastY = (glfwGetVideoMode(glfwGetPrimaryMonitor())->height) / 2.0f;
	//
	int* resY = new int; *resY = 1440; float resX2 = 2560;
	int* resX = new int; *resX = 2560; float resY2 = 1440;
	GLFWmonitor* MyMonitor = glfwGetPrimaryMonitor(); // The primary monitor.. Later Occulus?..

	const GLFWvidmode* mode = glfwGetVideoMode(MyMonitor);
	*resX = mode->width;
	*resY = mode->height;
#ifdef HOT_REALOAD
	std::vector<GLFWwindow*> window; window.push_back(glfwCreateWindow(glfwGetVideoMode(glfwGetPrimaryMonitor())->width,
		glfwGetVideoMode(glfwGetPrimaryMonitor())->height, "DevNinisEngineMotion",
		nullptr, nullptr));
#endif // HOT_REALOAD
#ifndef HOT_REALOAD
	GLFWwindow* window; window = glfwCreateWindow(glfwGetVideoMode(glfwGetPrimaryMonitor())->width,
		glfwGetVideoMode(glfwGetPrimaryMonitor())->height, "DevNinisEngineMotion",
		glfwGetPrimaryMonitor(), nullptr);
#endif

	if (window == NULL) {
		MessageBoxA(0, static_cast<const char*>("failed to initialise glad"), "ERROR", 0);
		exit(EXIT_FAILURE);
		return -1;
	}
	glfwMakeContextCurrent(window);
	// set glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		MessageBoxA(0, static_cast<const char*>("failed to initialise glad"), "ERROR", 0);
		exit(EXIT_FAILURE);
		return -1;
	}

	// 

	else {

		glViewport(*resX / 4.25, *resY / 4.25, *resX, *resY);

	}

#define SRC_WIDTH = glfwGetVideoMode(glfwGetPrimaryMonitor())->width / 2.0f;
#define SRC_HEIGHT = glfwGetVideoMode(glfwGetPrimaryMonitor())->height / 2.0f;

	float FOV = 55.0f; float RotateValue = -55.0f;
	bool drawingCube = true;
	char* filePathTex1; filePathTex1 = new char;
	char* filePathTex2; filePathTex2 = new char;
	int indicatorNumberTexVector = 0;
	int indicatorFolderTexture1 = 0; int indicatorFolderTexture2 = 0;
	const char* filePath;
	glmAnimation3D* matrixAnimation; matrixAnimation = new glmAnimation3D(window);
	// initialise imgui 
	UserInterface* Interface = nullptr; Interface = new UserInterface(window); // in the builder of this class they create a imgui context is because in argument they have GLFWwindow* ...
	if (HOTreload == false) {
		Interface->setStyleSettingFrame(window);

	}
	basicObject::cube* Cube; Cube = new basicObject::cube(window);
	std::string formatFile; formatFile = ".dev_ninis";
	writing::save Save; reading::read Read;
	Camera camera;
	Render rendering(window); objectUser::Mesh mesh(window);
	int* IndicatorFilepath = nullptr; IndicatorFilepath = new int; *IndicatorFilepath = Interface->getIndicatorTextureFilePath();
	mesh.setBufferMesh();
	mesh.CompileShaderMesh();
	mesh.setTexture1(unconstchar("img/containerBois.jpg"), 0);
	mesh.setTexture1(unconstchar("img/containerBois.jpg"), 1);

	float valueXColor = 0.2f; float ValueYcolor = 0.6f; float ValueZColor = 0.9f; float ValueWColor = 0.1f;
	float deltatime = 0, currentFrame = 0, lastedFrame = 0;
	TCHAR filepath = 100; char filePathBuffer[100]; filePathBuffer[100];
	TCHAR nBufferLength = 102; char lpFileName[2]; char* lpFilePart = nullptr; lpFilePart = &filePathBuffer[1];
	int numberMesh = 1;
	int uniqueId = 1;
	ed::Config config;
	static ed::EditorContext* g_Context = ed::CreateEditor(&config);
	float ab2 = 8.3f;
	VariablesSize SizeObject(window);
	SizeObject.setCHANGE_VALUE_ALL_SIZE(mesh.getShaderObject(), IN_FRAME_TRUE);
	AnimationProgramUser* UserProgram = nullptr;

	std::vector<Time::TimeValuesResultT<float>*> valuesTime = { nullptr };
	Editor::EditorStart* StandarEditor; StandarEditor = new Editor::EditorStart(window);
	IndicatorFinishLoading = true;
	threadLoad.join();
	while (!glfwWindowShouldClose(window)) // render
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltatime = currentFrame - lastedFrame;
		lastedFrame = currentFrame;

		mesh.setBufferMesh();




		if (HOTreload == false) {
			Interface->setSettingFrame();
			Interface->interfaceEditorWindow();

		}






		processInput(window);
		glClearColor(StandarEditor->lastedColorFrame[0], StandarEditor->lastedColorFrame[1], StandarEditor->lastedColorFrame[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		mesh.useShaderObject();
		camera.processInputCamera(window, deltatime, StandarEditor->getCmerraSpeed());
		if (HOTreload == false) {
			
			
		}
	


		

		// initialise matrix, ect...
		matrixAnimation->initialiseMatrix();
		matrixAnimation->setLookAtMatrixCamera(camera.getcamPos(), camera.getcamFront(), camera.getcamUp());
		matrixAnimation->setRotateLeft(RotateValue, StandarEditor->getValueRotateX(), StandarEditor->getValueRotateY(), StandarEditor->getValueRotateZ());
		matrixAnimation->setMatrixPerspectiveProjection(FOV, resX2, resY2, camera);
		matrixAnimation->setTransformValue();
		matrixAnimation->frameMatrix(mesh.getShaderObject());
		matrixAnimation->setPercentTexture(mesh.getShaderObject(), Interface->getpercentTexture());
		matrixAnimation->drawAnimation(mesh.getShaderObject(), rendering, mesh, camera.getcamPos(), camera.getcamFront(), camera.getcamUp());


		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			HOTreload = false;
			glViewport(*resX / 4.5, 0, *resX, *resY);
		}
		matrixAnimation->setPercentTexture(mesh.getShaderObject(), Interface->getpercentTexture());

		if (HOTreload == false) { 
			ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
			if (ImGui::BeginMainMenuBar()) {
				if (ImGui::BeginMenu("file")) {
					if (ImGui::MenuItem("Open")) {
						Read.setValueFile(Read.selectPath(window));
						Interface = nullptr;

						mesh.setTexture1(StandarEditor->filePathPointer[0], 0);
						mesh.setTexture1(StandarEditor->filePathPointer[0], 1);
						matrixAnimation->setPercentTexture(mesh.getShaderObject(), StandarEditor->getpercentTexture());
						SizeObject.setCHANGE_VALUE_ALL_SIZE(mesh.getShaderObject(), StandarEditor->LastedFloatFrame);
						matrixAnimation->setPositionObject(mesh.getShaderObject(), StandarEditor->getPositionObjectX(), StandarEditor->getPositionObjectY(), StandarEditor->getPositionObjectZ());
						matrixAnimation->setColorObject(mesh.getShaderObject(), StandarEditor->LastedColorObject[0], StandarEditor->LastedColorObject[1], StandarEditor->LastedColorObject[2]);
						matrixAnimation->setRotateLeft(RotateValue, StandarEditor->getValueRotateX(), StandarEditor->getValueRotateY(), StandarEditor->getValueRotateZ());
					}
					ImGui::Spacing();
					if (ImGui::MenuItem("Save")) {
						Save.setFileContent(Read.selectPath(window));
					}
					ImGui::Spacing();
					if (ImGui::MenuItem("Save as")) {
						Save.setFileContent(Read.selectPath(window));
					}
					if (ImGui::MenuItem("Wiew Source Code ")) {
						ShellExecuteA(NULL, "open", "https://github.com/DEV-NINIS/miniEngine", NULL, NULL, SW_SHOWDEFAULT);
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("import")) {
					if (ImGui::MenuItem("Mesh (.obj file)")) {

					}
					ImGui::EndMenu();

				}
				ImGui::EndMainMenuBar();
			}
			if (ImGui::Button(ICON_FA_PLAY "  PLAY", ImVec2(2560 / 4.35, 40.0f))) {
				HOTreload = true;
				glViewport(0, 0, *resX, *resY);

			}
			if (StandarEditor->setCollaspedHeaderSize()) {
				if (UserProgram == nullptr) {
					UserProgram = new VariablesSize(window);
				}
				ImGui::Separator();
				ImGui::Separator();
				SizeObject.setCHANGE_VALUE_ALL_SIZE(mesh.getShaderObject(), IN_FRAME_NOT);
				ImGui::Separator();

				UserProgram->setCHANGE_X(IN_FRAME_NOT);
				matrixAnimation->frameMatrix(mesh.getShaderObject());
				ImGui::Separator();
				UserProgram->setCHANGE_Y(IN_FRAME_NOT);
				matrixAnimation->frameMatrix(mesh.getShaderObject());
				ImGui::Separator();


				UserProgram->setCHANGE_Z(IN_FRAME_NOT);
				ImGui::Separator();
				SizeObject.InputSize();

				matrixAnimation->frameMatrix(mesh.getShaderObject());
				ImGui::Separator();
			}
			ImGui::Spacing();
			if (StandarEditor->setCollaspedHeaderPosition()) {
				ImGui::Spacing();
				StandarEditor->setPositionObjectX();
				ImGui::Separator();
				matrixAnimation->setPositionObject(mesh.getShaderObject(), StandarEditor->getPositionObjectX(), StandarEditor->getPositionObjectY(), StandarEditor->getPositionObjectZ());
				StandarEditor->setPositionObjectY();
				ImGui::Separator();
				matrixAnimation->setPositionObject(mesh.getShaderObject(), StandarEditor->getPositionObjectX(), StandarEditor->getPositionObjectY(), StandarEditor->getPositionObjectZ());
				StandarEditor->setPositionObjectZ();
				ImGui::Separator();
				matrixAnimation->setPositionObject(mesh.getShaderObject(), StandarEditor->getPositionObjectX(), StandarEditor->getPositionObjectY(), StandarEditor->getPositionObjectZ());
			}
		}



		if (HOTreload == true) {
			SizeObject.setCHANGE_VALUE_ALL_SIZE(mesh.getShaderObject(), StandarEditor->LastedFloatFrame);
		}





		//Left side

			
				// end menubar



				// echelle du cube

				//

				// position cube
				if (HOTreload == false) {

					// Animation

					ImGui::Spacing();
					// texture
					if (StandarEditor->setCollaspedHeaderTexture()) {
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
						StandarEditor->setPercentTexture();
						 // this fonction set the value in the shader
						if (Interface->confirmFilePath() == true) {
							mesh.setTexture1(filePathTex1, 0);
							mesh.setTexture1(filePathTex1, 1);
							mesh.setPercentTexture(StandarEditor->getpercentTexture());
						}
					}
				}

			if (HOTreload == true) {
				matrixAnimation->setRotateLeft(RotateValue, StandarEditor->getValueRotateX(), StandarEditor->getValueRotateY(), StandarEditor->getValueRotateZ());
				RotateValue += 1;

			}
			if (HOTreload == false) {
				ImGui::Spacing();

				// menubar

				// settings 
				// colors

				// camera
				if (StandarEditor->setCollaspedHeaderCamera() == true) {
					if (StandarEditor != nullptr) {
						ImGui::Spacing();
						StandarEditor->setCameraSpeed();
						ImGui::Spacing();
						StandarEditor->setChangeFOV();
						FOV = StandarEditor->getFOV_Value();
						ImGui::Text("press E to forward ");
						ImGui::Spacing();
						ImGui::Text("press D to move back ");
						ImGui::Spacing();
						ImGui::Text("press S to move right ");
						ImGui::Spacing();
						ImGui::Text("press F to move left ");
						ImGui::Spacing();
					}

				}
				if (HOTreload == false) {
					ImGui::Spacing();
					// FOV


					// render




					matrixAnimation->setLookAtMatrixCamera(camera.getcamPos(), camera.getcamFront(), camera.getcamUp());


					if (StandarEditor->setCollaspedHeaderColorObject()){
						ImGui::Spacing();
						StandarEditor->setColorObjectR();
						ImGui::Spacing();
					StandarEditor->setColorObjectG();
					ImGui::Spacing();
					StandarEditor->setColorObjectB();
					ImGui::Spacing();
					matrixAnimation->setColorObject(mesh.getShaderObject(), StandarEditor->LastedColorObject[0], StandarEditor->LastedColorObject[1], StandarEditor->LastedColorObject[2]);
					StandarEditor->setColorEditorObject(COLOR_OBJECT);
					}

					ImGui::Spacing();

					if (StandarEditor->setCollaspedHeaderColorFrame()) {
						StandarEditor->setColorR();
						ImGui::Spacing();
						StandarEditor->setColorG();
						ImGui::Spacing();
						StandarEditor->setColorB();
						ImGui::Spacing();
						StandarEditor->setColorEditorFrame(COLOR_FRAME);
						setCHANGE_DIRECTION_ROTATE_MATRIX<void>();
					}

					ImGui::End();
				}
				// node 



				Interface->setNodeWindow();
				Interface->setStyleNodeFrame();
				ImGui::Begin("Node", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);



				ed::SetCurrentEditor(g_Context);
				ed::Begin("My Editor", ImVec2(0.0, 0.0f));
				// Start drawing nodes.
				Interface->recevedNodeValueForSetNodeText();

				

				ed::End();
				ImGui::End();
				Interface->setNodeAddButtonWindow();
				ImGui::Begin("add Node +", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
				Interface->setNodeButtonFORadd();
















			}
			// Get the size of the child (i.e. the whole draw size of the windows).
			matrixAnimation->frameMatrix(mesh.getShaderObject());
			
			if (HOTreload == false) {
				ImGui::End();
				Interface->endFrame();
			}
			
			// ------ End of docking --------
			// node window

			glEnable(GL_DEPTH_TEST);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		if (HOTreload == false) {
			ed::DestroyEditor(g_Context);
		}

		Cube->~cube();
		mesh.~Mesh();
		delete Cube; Cube = NULL;
	}




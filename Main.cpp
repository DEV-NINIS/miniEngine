#include <glad/glad.h>
#include <GLFW/glfw3.h>
// Initialize with gl3wInit()

#include <iostream>
#include <string>
#include "object.h"
#include "Render.h"
#include "imgui/imgui_node_editor.h"
#include "imgui/imgui_bezier_math.h"
#include "stbi_image.h"
#include "file.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "UserInterface.h"
#include "imgui/imgui_impl_opengl3.h"
#include "glmAnimation3D.h"
#include "iconcpp.h"
#include "icons.h"
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
#define COLOR_FRAME 1
#define COLOR_OBJECT 2
IMGUI_API ImTextureID ImGui_CreateTexture32(const void* data, int width, int height);
IMGUI_API ImTextureID ImGui_CreateTextureFromDescriptor(...); // API dependent
IMGUI_API void        ImGui_DestroyTexture(ImTextureID texture);
IMGUI_API int         ImGui_GetTextureWidth(ImTextureID texture);
IMGUI_API int         ImGui_GetTextureHeight(ImTextureID texture);

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

static bool HOTreload = false;
namespace ed = ax::NodeEditor;

//												_____
//               /\         |\		|	 |	   |
//				/  \		| \		|	 |	   |
//			   /	\		|  \	|	 |	   |_____
//			  /------\		|	\	|	 |			 |
//			 /		  \		|	 \	|	 |			 |
//			/		   \	|	  \	|	 |		_____|
//
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
	mesh.setTexture1(unconstchar("img/containerBois.jpg"));
	mesh.setTexture2(unconstchar("img/containerBois.jpg"));
	Interface->LastedFloatFrame = 1;
	float valueXColor = 0.2f; float ValueYcolor = 0.6f; float ValueZColor = 0.9f; float ValueWColor = 0.1f;
	float deltatime = 0, currentFrame = 0, lastedFrame = 0;
	TCHAR filepath = 100; char filePathBuffer[100]; filePathBuffer[100];
	TCHAR nBufferLength = 102; char lpFileName[2]; char* lpFilePart = nullptr; lpFilePart = &filePathBuffer[1];
	int numberMesh = 1;
	int uniqueId = 1;
	ed::Config config;
	static ed::EditorContext* g_Context = ed::CreateEditor(&config);
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
		glClearColor(Interface->lastedColorFrame[0], Interface->lastedColorFrame[1], Interface->lastedColorFrame[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		mesh.useShaderObject();
		camera.processInputCamera(window, deltatime, Interface->getCmerraSpeed());

		// initialise matrix, ect...
		matrixAnimation->initialiseMatrix();
		matrixAnimation->setLookAtMatrixCamera(camera.getcamPos(), camera.getcamFront(), camera.getcamUp());
		matrixAnimation->setRotateLeft(RotateValue, Interface->getValueRotateX(), Interface->getValueRotateY(), Interface->getValueRotateZ());
		matrixAnimation->setMatrixPerspectiveProjection(FOV, resX2, resY2, camera);
		matrixAnimation->setTransformValue();
		matrixAnimation->frameMatrix(mesh.getShaderObject());
		matrixAnimation->setScaleValue(mesh.getShaderObject(), Interface->LastedFloatFrame);
		matrixAnimation->setPercentTexture(mesh.getShaderObject(), Interface->getpercentTexture());


		
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			HOTreload = false;
			glViewport(*resX / 4.5, 0, *resX, *resY);
		}
		matrixAnimation->setPercentTexture(mesh.getShaderObject(), Interface->getpercentTexture());

		if (HOTreload == false) {
			ImGui::Begin("Editor");
			if (ImGui::Button( ICON_FA_PLAY "  PLAY", ImVec2(2560 / 4.35, 40.0f))) {
				HOTreload = true;
				glViewport(0, 0, *resX, *resY);

			}
			if (ImGui::CollapsingHeader("size")) {
				ImGui::Separator();
				Interface->setScaleCube();
				matrixAnimation->setScaleValue(mesh.getShaderObject(), Interface->LastedFloatFrame);
				ImGui::Separator();
				Interface->setLastedmatrix();
				matrixAnimation->setScaleValue(mesh.getShaderObject(), Interface->LastedFloatFrame);
				matrixAnimation->setScaleValueX(mesh.getShaderObject());
				matrixAnimation->frameMatrix(mesh.getShaderObject());
				ImGui::Separator();
				Interface->setLastedmatrix();
				matrixAnimation->setScaleValue(mesh.getShaderObject(), Interface->LastedFloatFrame);
				matrixAnimation->setScaleValueY(mesh.getShaderObject());
				matrixAnimation->frameMatrix(mesh.getShaderObject());
				ImGui::Separator();


				Interface->setLastedmatrix();
				matrixAnimation->setScaleValue(mesh.getShaderObject(), Interface->LastedFloatFrame);
				matrixAnimation->setScaleValueZ(mesh.getShaderObject());
				matrixAnimation->frameMatrix(mesh.getShaderObject());
				ImGui::Separator();
			}
			ImGui::Spacing();
			if (ImGui::CollapsingHeader("positions")) {
				ImGui::Spacing();
				Interface->setPositionObjectX();
				ImGui::Separator();
				matrixAnimation->setPositionObject(mesh.getShaderObject(), Interface->getPositionObjectX(), Interface->getPositionObjectY(), Interface->getPositionObjectZ());
				Interface->setPositionObjectY();
				ImGui::Separator();
				matrixAnimation->setPositionObject(mesh.getShaderObject(), Interface->getPositionObjectX(), Interface->getPositionObjectY(), Interface->getPositionObjectZ());
				Interface->setPositionObjectZ();
				ImGui::Separator();
				matrixAnimation->setPositionObject(mesh.getShaderObject(), Interface->getPositionObjectX(), Interface->getPositionObjectY(), Interface->getPositionObjectZ());
			}
		}



		if (HOTreload == true) {
			matrixAnimation->setScaleValue(mesh.getShaderObject(), Interface->LastedFloatFrame);
		}





		//Left side
		if (HOTreload == false) {

			if (ImGui::BeginMainMenuBar()) {
				if (ImGui::BeginMenu("file")) {
					if (ImGui::MenuItem("Open")) {
						Read.setValueFile(Read.selectPath(window));
						Interface = nullptr;
						Interface = new UserInterface(window, Read.getValueColorFrameRFile(), Read.getValueColorFrameGFile(), Read.getValueColorFrameBFile(),
							Read.getLastedScaleXFile(), Read.getLastedScaleYFile(), Read.getLastedScaleZFile(), Read.getValueTransformXFile(),
							Read.getValueTransformYFile(), Read.getValueTransformZFile(), Read.getcolorObjectFileR(),
							Read.getcolorObjectFileG(), Read.getcolorObjectFileB(), Read.getValuePositionObjectFileX(), Read.getValuePositionObjectFileY(),
							Read.getValuePositionObjectFileZ(), Read.getValueCameraSpeedFile(), Read.getfiletextureFile());
						matrixAnimation->frameMatrix(mesh.getShaderObject());
						mesh.setTexture1(Interface->filePathPointer[0]);
						mesh.setTexture2(Interface->filePathPointer[0]);
						matrixAnimation->setPercentTexture(mesh.getShaderObject(), Interface->getpercentTexture());
						matrixAnimation->setScaleValue(mesh.getShaderObject(), Interface->LastedFloatFrame);
						matrixAnimation->setPositionObject(mesh.getShaderObject(), Interface->getPositionObjectX(), Interface->getPositionObjectY(), Interface->getPositionObjectZ());
						matrixAnimation->setColorObject(mesh.getShaderObject(), Interface->LastedColorObject[0], Interface->LastedColorObject[1], Interface->LastedColorObject[2]);
						matrixAnimation->setRotateLeft(RotateValue, Interface->getValueRotateX(), Interface->getValueRotateY(), Interface->getValueRotateZ());
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
			// end menubar



			// echelle du cube

			//

			// position cube
			if (HOTreload == false) {

				// Animation

				ImGui::Spacing();
				// texture
				if (ImGui::CollapsingHeader("texture")) {
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
					Interface->setPercentTexture<void>();
					if (Interface->confirmFilePath() == true) {
						mesh.setTexture1(filePathTex1);
						mesh.setTexture2(filePathTex2);
					}
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

			// camera
			if (ImGui::CollapsingHeader("Camera")) {
				ImGui::Spacing();
				Interface->setCameraSpeed();
				ImGui::Spacing();
				Interface->setChangeFOV();
				FOV = Interface->getFOV_Value();
				ImGui::Text("press E to forward ");
				ImGui::Spacing();
				ImGui::Text("press D to move back ");
				ImGui::Spacing();
				ImGui::Text("press S to move right ");
				ImGui::Spacing();
				ImGui::Text("press F to move left ");
				ImGui::Spacing();
				
			}

			ImGui::Spacing();
			// FOV

			
			// render
			



			matrixAnimation->setLookAtMatrixCamera(camera.getcamPos(), camera.getcamFront(), camera.getcamUp());
			ImGui::Columns(2);
			ImGui::SetColumnOffset(1, glfwGetVideoMode(glfwGetPrimaryMonitor())->width / 4 / 2);
			ImGui::Spacing();
			if (ImGui::CollapsingHeader("Color Object")) {
				ImGui::Spacing();
				Interface->setColorObjectR();
				ImGui::Spacing();
				Interface->setColorObjectG();
				ImGui::Spacing();
				Interface->setColorObjectB();
				ImGui::Spacing();
				matrixAnimation->setColorObject(mesh.getShaderObject(), Interface->LastedColorObject[0], Interface->LastedColorObject[1], Interface->LastedColorObject[2]);
				Interface->setColorEditorObject(COLOR_OBJECT);
			}
			ImGui::NextColumn();
			ImGui::Spacing();
			if (ImGui::CollapsingHeader("Color Frame")) {
				ImGui::Spacing();
				Interface->setColorR();
				ImGui::Spacing();
				Interface->setColorG();
				ImGui::Spacing();
				Interface->setColorB();
				ImGui::Spacing();
				Interface->setColorEditorFrame(COLOR_FRAME);
				setCHANGE_DIRECTION_ROTATE_MATRIX<void>();
			}
			
			ImGui::End();
			// node 



			Interface->setNodeWindow();
			Interface->setStyleNodeFrame();
			ImGui::Begin("Node");

			ImGui::Columns(2);
			ImGui::SetColumnOffset(1, (glfwGetVideoMode(glfwGetPrimaryMonitor())->width - glfwGetVideoMode(glfwGetPrimaryMonitor())->width/4.25)/4);
			ImGui::Button("rotate object in the x abscisses");
			ImGui::NextColumn();
			ImGui::Spacing();
			ed::SetCurrentEditor(g_Context);
			ed::Begin("My Editor", ImVec2(0.0, 0.0f));
			Interface->addNode(ADD_NODE_CHANGE_DIRECTION_ROTATE_MATRIX);
			Interface->setNodeRotateMeshWithRadius();
			Interface->setNodeRotateMeshWithRadius();
			ed::End();












		}
		// Get the size of the child (i.e. the whole draw size of the windows).
		matrixAnimation->frameMatrix(mesh.getShaderObject());
		rendering.drawElements(mesh, numberMesh);
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



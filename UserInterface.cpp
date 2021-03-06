#include "UserInterface.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_node_editor.h"
#include "imgui/imgui_node_editor_internal.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_opengl3_loader.h"
#include "imgui/imgui_internal.h"
#include "icons.h"
#include "iconcpp.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#define COLOR_FRAME 1
#define COLOR_OBJECT 2

// define of node
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

#define SRC_WIDTH glfwGetVideoMode(glfwGetPrimaryMonitor())->width
#define SRC_HEIGHT glfwGetVideoMode(glfwGetPrimaryMonitor())->height

#define EDITOR_WINDOW_POS ImVec2(viewport->WorkPos.x, viewport->WorkPos.y)
#define EDITOR_WINDOW_SIZE ImVec2(viewport->WorkSize.x - viewport->WorkSize.x * 0.75, viewport->WorkSize.y)
#define EDITOR_WINDOW_SIZE_X (viewport->WorkSize.x - viewport->WorkSize.x * 0.75)
#define NODE_WINDOW_POS ImVec2(viewport->WorkPos.x + (viewport->WorkSize.x/4.25) + (viewport->WorkSize.x - viewport->WorkSize.x / 4.25) / 4, viewport->WorkSize.y- viewport->WorkSize.y/4.275)
#define NODE_WINDOW_POS_X (viewport->WorkPos.x + (viewport->WorkSize.x/4.25) + (viewport->WorkSize.x - viewport->WorkSize.x / 4.25) / 4)
#define NODE_WINDOW_SIZE ImVec2(viewport->WorkSize.x - viewport->WorkSize.x/ 4.275 - (viewport->WorkSize.x - viewport->WorkSize.x / 4.275) / 4, viewport->WorkSize.y/4)
#define NODE_WINDOW_SIZE_X (viewport->WorkSize.x - viewport->WorkSize.x/ 4.25 - (viewport->WorkSize.x - viewport->WorkSize.x / 4.25) / 4)
#define NODE_ADD_BUTTON_WINDOW_POS ImVec2(viewport->WorkSize.x - viewport->WorkSize.x * 0.75, viewport->WorkSize.y - viewport->WorkSize.y/4.275)
#define NODE_ADD_BUTTON_WINDOW_SIZE ImVec2((viewport->WorkSize.x - NODE_WINDOW_SIZE_X - EDITOR_WINDOW_SIZE_X),  viewport->WorkSize.y/4)



namespace ed = ax::NodeEditor;

char UserInterface::filePath1[] = { 0 };
char UserInterface::filePath2[] = { 0 };
char UserInterface::filePath3[] = { 0 };
char UserInterface::filePath4[] = { 0 };
char UserInterface::filePath5[] = { 0 };
const char* UserInterface::filepath1ConstChar = 0;
const char* UserInterface::filepath2ConstChar = 0;
float UserInterface::LastedColorObject[] = { 0 };
float UserInterface::lastedColorFrame[] = { 0 };


static int uniqueId = 1;

UserInterface::UserInterface(GLFWwindow* window)  {
	
	lastedColorFrame[0] = 0.2; lastedColorFrame[1] = 0.6; lastedColorFrame[2] = 0.9;
	LastedFloatFrame = 1.0f; LastedFloatFrameX = 1.0f; LastedFloatFrameY = 1.0f; LastedFloatFrameZ = 1.0f;
	LastedRotateXValue = 0.1f; LastedRotateYValue = 0.0f; LastedRotateZValue = 0.0f;
	size1 = new float;
	FOV = 55.0f;
	lastedFilePath = -1;
	LastedColorObject[0] = 0.1;
		LastedColorObject[1] = 0.6;
		LastedColorObject[2] = 0.5;
	LastedPositionObjectX = 0.0f; LastedPositionObjectY = 0.0f; LastedPositionObjectZ = 0.0f;
	filePathPointer.push_back(new char); *filePathPointer[0] = '0';
	filePathPointer.push_back(new char); *filePathPointer[1] = '0';
	percentTexture = 0.5f;
	CameraSpeed = 10.0f;


	
}
UserInterface::UserInterface(GLFWwindow* window, int randomNumberJustForSurcharge) {

}
UserInterface::UserInterface(GLFWwindow* window, float LastedFrameColorRFile, float LastedFrameColorGFile,
float LastedFrameColorBFile, float LastedFloatFrameXFile, float LastedFloatFrameYFile, float LastedFloatFrameZFile,
float LastedRotateXValueFile, float LastedRotateYValueFile, float LastedRotateZValueFile, float LastedColorObjectRFile,
float LastedColorObjectGFile, float LastedColorObjectBFile, float LastedPositionObjectXFile, float LastedPositionObjectYFile,
float LastedPositionObjectZFile, float CameraSpeedFile, const char* filePathPointerFile)
{
	lastedColorFrame[0] = LastedFrameColorRFile; lastedColorFrame[1] = LastedFrameColorGFile; lastedColorFrame[2] = LastedFrameColorBFile;
	LastedFloatFrame = 1.0f; LastedFloatFrameX = LastedFloatFrameXFile; LastedFloatFrameY = LastedFloatFrameYFile; LastedFloatFrameZ = LastedFloatFrameZFile;
	LastedRotateXValue = LastedRotateXValueFile; LastedRotateYValue = LastedRotateYValueFile; LastedRotateZValue = LastedRotateZValueFile;
	LastedColorObject[0] = LastedColorObjectRFile;
	LastedColorObject[1] = (LastedColorObjectGFile);
	LastedColorObject[2] = (LastedColorObjectBFile);
	LastedPositionObjectX = LastedPositionObjectXFile; LastedPositionObjectY = LastedPositionObjectYFile; LastedPositionObjectZ = LastedPositionObjectZFile;
	percentTexture = 0.5f; CameraSpeed = CameraSpeedFile; FOV = 55.0f;
	lastedFilePath = -1;
	size1 = new float;
	filepath1ConstChar = filePathPointerFile;
	filepath2ConstChar = filePathPointerFile;
	filePathPointer.push_back(new char); *filePathPointer[0] = '0';
	filePathPointer.push_back(new char); *filePathPointer[1] = '0';
}
UserInterface::~UserInterface() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
void UserInterface::interfaceEditorWindow() {
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
		ImGuiWindowFlags_NoBackground;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(EDITOR_WINDOW_POS);
	ImGui::SetNextWindowSize(EDITOR_WINDOW_SIZE);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 10.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::PopStyleVar(3);
}
void UserInterface::setNodeWindow() {
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
		ImGuiWindowFlags_NoBackground;
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(NODE_WINDOW_POS);
	ImGui::SetNextWindowSize(NODE_WINDOW_SIZE);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 10.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::PopStyleVar(3);

}
void UserInterface::setStyleNodeFrame() {
	ed::Style style;
	style.SelectedNodeBorderWidth = 0;
	
}
void UserInterface::setNodeAddButtonWindow() {
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
		ImGuiWindowFlags_NoBackground;
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(NODE_ADD_BUTTON_WINDOW_POS);
	ImGui::SetNextWindowSize(NODE_ADD_BUTTON_WINDOW_SIZE);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 10.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::PopStyleVar(3);
}
void UserInterface::setNodeInformation() {
	auto& io = ImGui::GetIO();
	ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.0f / io.Framerate : 0.0f);
	ImGui::Separator();
	ed::Begin("My Editor", ImVec2(0.0, 0.0f));
}
void UserInterface::setStyleSettingFrame(GLFWwindow* window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.Fonts->AddFontFromFileTTF("resources/textFont/Merriweather-Regular.ttf", 17);
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
	ImVec4* color = ImGui::GetStyle().Colors;
	color[ImGuiCol_WindowBg] = ImColor(50, 56, 57, 255);
	ImGuiStyle* style = &ImGui::GetStyle();
	io.IniFilename = nullptr;

	static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
	ImFontConfig icons_config;

	ImFontConfig CustomFont;
	CustomFont.FontDataOwnedByAtlas = false;


	icons_config.MergeMode = true;
	icons_config.PixelSnapH = true;
	icons_config.OversampleH = 2.5;
	icons_config.OversampleV = 2.5;

	io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 19.0f, &icons_config, icons_ranges);
	io.Fonts->AddFontDefault();


	style->WindowBorderSize = 0;
	style->WindowTitleAlign = ImVec2(0.5, 0.5);
	style->ButtonTextAlign = ImVec2(0.5, 0.5);
	style->FramePadding = ImVec2(1, 1);
	style->WindowMenuButtonPosition = ImGuiDir();
	style->Colors[ImGuiCol_TitleBg] = ImColor(79, 86, 98, 255);
	style->Colors[ImGuiCol_TitleBgActive] = ImColor(79, 86, 98, 255);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(79, 86, 98, 130);

	style->Colors[ImGuiCol_Button] = ImColor(79, 86, 98, 255);
	style->Colors[ImGuiCol_ButtonActive] = ImColor(79, 86, 98, 255);
	style->Colors[ImGuiCol_ButtonHovered] = ImColor(187, 180, 150, 255);

	style->Colors[ImGuiCol_Separator] = ImColor(70, 70, 70, 255);
	style->Colors[ImGuiCol_SeparatorActive] = ImColor(76, 76, 76, 255);
	style->Colors[ImGuiCol_SeparatorHovered] = ImColor(76, 76, 76, 255);

	style->Colors[ImGuiCol_MenuBarBg] = ImColor(50, 56, 57, 255);

	style->Colors[ImGuiCol_FrameBg] = ImColor(60, 56, 47, 255);
	style->Colors[ImGuiCol_FrameBgActive] = ImColor(60, 56, 47, 255);
	style->Colors[ImGuiCol_FrameBgHovered] = ImColor(60, 56, 47, 255);
	style->SelectableTextAlign = ImVec2(0.1, 0.1);
	style->PopupBorderSize = 5;
	style->FrameBorderSize = 3.0;
	style->ChildBorderSize = 3.0;
	style->TabBorderSize = 3.0;
	style->WindowBorderSize = 3.0;
	style->PopupRounding = 5;
	style->ChildRounding = 5;
	style->FrameRounding = 5;
	style->GrabRounding = 5;
	style->WindowRounding = 0;
	style->TabRounding = 5;
	style->MouseCursorScale = 50;
	style->IndentSpacing = 5;
}
void UserInterface::setSettingFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}
bool UserInterface::inputDemandSelectFolderForTex1() const {
	if (ImGui::Button(ICON_FA_UPLOAD "  select folder for texture 1", ImVec2(SRC_WIDTH / 4.5, SRC_HEIGHT / 40.5))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandSelectFolderForTex2() const {
	if (ImGui::Button(ICON_FA_UPLOAD "  select folder for texture 2", ImVec2(SRC_WIDTH / 4.5, SRC_HEIGHT / 40.5))) {
		return true;
	}
	else { return false; }
}
float UserInterface::setScaleCubeX() {
	ImGui::SliderFloat("sizeX", &LastedFloatFrameX, 0.0f, 10.0f);
	if (LastedFloatFrameX > -401602080) {
		LastedFloatFrameX = 1.0f;
		return LastedFloatFrameX;
	}
	else { 
		return LastedFloatFrameX;
	}
}
float UserInterface::setRotateAroundXValue() {
	float* RotateXValue = nullptr; RotateXValue = new float;
	ImGui::SliderFloat("ValueX_MatrixX", &*RotateXValue, -1.0f, 1.0f);
	if (*RotateXValue > -401602080) {
		LastedRotateXValue = *RotateXValue;
		return *RotateXValue;
	}
	else { return 0.0f; }
}

float UserInterface::setRotateAroundYValue() {
	float* RotateYValue = nullptr; RotateYValue = new float;
	ImGui::SliderFloat("ValueX_MatrixY", &*RotateYValue, -1.0f, 1.0f);
	if (*RotateYValue > -401602080) {
		LastedRotateYValue = *RotateYValue;
		return *RotateYValue;
	}
	else { return 0.0f; }
}
float UserInterface::setRotateAroundZValue() {
	float* RotateZValue = nullptr; RotateZValue = new float;
	ImGui::SliderFloat("ValueX_MatrixZ", &*RotateZValue, -1.0f, 1.0f);
	if (*RotateZValue > -401602080) {
		LastedRotateZValue = *RotateZValue;
		return *RotateZValue;
	}
	else { return 0.0f; }
}
void UserInterface::setCameraSpeed() {
	ImGui::SliderFloat("valueCameraSpeed", &CameraSpeed, 0, 100);
}
float UserInterface::setScaleCubeZ() {
	ImGui::SliderFloat("sizeZ", &LastedFloatFrameZ, 0, 10);
	if (LastedFloatFrameZ > -401602080) {
		LastedFloatFrameZ = 1.0f;
		return LastedFloatFrameZ;
	}
	else {
		return LastedFloatFrameZ;
	}
}
bool UserInterface::changeColorFrame() {
	if (ImGui::Button("Color ", ImVec2(75, 50))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingChangeColorFrame() {
	if (ImGui::Button("Clear Color", ImVec2(200, 30))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::confirmFilePath() const {
	if (ImGui::Button("load", ImVec2(SRC_WIDTH / 60, SRC_HEIGHT/60))) {
		return true;
	}
	else { return false; }
}
void UserInterface::setColorR() {
	ImGui::SliderFloat("R (FRAME)", &lastedColorFrame[0], 0, 1);
	if (lastedColorFrame[0] < -401602080) {
		lastedColorFrame[0] = 0.4f;
	}
}
void UserInterface::setColorG() {
	ImGui::SliderFloat("G (FRAME)", &lastedColorFrame[1], 0, 1);
	if (lastedColorFrame[1] < -401602080) {
		lastedColorFrame[1] = 0.1f;
	}
}
void UserInterface::setColorB() {
	ImGui::SliderFloat("B (FRAME)", &lastedColorFrame[2], 0, 1);
	if (lastedColorFrame[2] < -401602080) {
		lastedColorFrame[2] = 0.9f;
	}
}
void UserInterface::setChangeFOV() {
	ImGui::SliderFloat("change FOV", &FOV, 10, 145);
	if (FOV < -401602080) {
		FOV = 45.0f;
	}
}
void UserInterface::inputFileTexture1(char* filePath) {
	ImGui::Text(filePath , ": is your filepath");
}
void UserInterface::inputFileTexture2(char* filePath) {
	ImGui::Text(filePath ,": is your filepath");
}

void UserInterface::setColorObjectR() {
	ImGui::SliderFloat("R (OBJECT)", &LastedColorObject[0], 0, 1);
	if (LastedColorObject[0] < -401602080) {
		LastedColorObject[0] = 0.5f;
	}
}
void UserInterface::setColorObjectG() {
	ImGui::SliderFloat("G (OBJECT)", &LastedColorObject[1], 0, 1);
	if (LastedColorObject[1] < -401602080) {
		LastedColorObject[1] = 0.5f;
	}
}
void UserInterface::setColorObjectB() {
	ImGui::SliderFloat("B (OBJECT)", &LastedColorObject[2], 0, 1);
	if (LastedColorObject[2] < -401602080) {
		LastedColorObject[2] = 0.5f;
	}
}
// set positions 
void UserInterface::setPositionObjectX() {
	ImGui::SliderFloat("PositionX", &LastedPositionObjectX, -100, 100);
	if (LastedPositionObjectX < -401602080) {
		LastedPositionObjectX = 0.0f;
	}
}
void UserInterface::setPositionObjectY() {
	ImGui::SliderFloat("PositionY", &LastedPositionObjectY, -100, 100);
	if (LastedPositionObjectY < -401602080) {
		LastedPositionObjectY = 0.0f;
	}
}
void UserInterface::setPositionObjectZ() {
	ImGui::SliderFloat("PositionZ", &LastedPositionObjectZ, -100, 100);
	if (LastedPositionObjectZ < -401602080) {
		LastedPositionObjectZ = 0.0f;
	}
}

// node

void UserInterface::recevedNodeValueForSetNodeText() {
	int uniqueID =  1;

	if (ADD_NODE_CHANGE_CAMERA_SPEED_variable == 1) {
		ed::SetNodePosition(uniqueID++, ImVec2(50, 150));
		ed::BeginNode(uniqueID++);
		ImGui::Text("CHANGE CAMERA SPEED");
		ed::BeginPin(uniqueID++, ed::PinKind::Input);
		ImGui::Text(ICON_FA_ARROW_RIGHT " In");
		ed::EndPin();
		ImGui::SameLine();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::EndNode();
	}
	if (ADD_NODE_CHANGE_COLOR_OBJECT_variable == 1) {
		ed::SetNodePosition(uniqueID++, ImVec2(50, 150));
		ed::BeginNode(uniqueID++);
		ImGui::Text("CHANGE COLOR OBJECT");
		ed::BeginPin(uniqueID++, ed::PinKind::Input);
		ImGui::Text(ICON_FA_ARROW_RIGHT " In");
		ed::EndPin();
		ImGui::SameLine();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::EndNode();
	}
	if (ADD_NODE_CHANGE_COLOR_FRAME_variable == 1) {
		ed::SetNodePosition(uniqueID++, ImVec2(50, 150));
		ed::BeginNode(uniqueID++);
		ImGui::Text("CHANGE COLOR FRAME");
		ed::BeginPin(uniqueID++, ed::PinKind::Input);
		ImGui::Text(ICON_FA_ARROW_RIGHT " In");
		ed::EndPin();
		ImGui::SameLine();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::EndNode();
	}
	if (ADD_NODE_CHANGE_DIRECTION_ROTATE_MATRIX_variable == 1) {
		ed::SetNodePosition(uniqueID++, ImVec2(50, 150));
		ed::BeginNode(uniqueID++);
		ImGui::Text("CHANGE DIRECTION ROTATE MATRIX VARIABLE");
		ed::BeginPin(uniqueID++, ed::PinKind::Input);
		ImGui::Text(ICON_FA_ARROW_RIGHT " In");
		ed::EndPin();
		ImGui::SameLine();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::EndNode();
	}
	if (ADD_NODE_CHANGE_FOV_variable == 1) {
		ed::SetNodePosition(uniqueID++, ImVec2(50, 150));
		ed::BeginNode(uniqueID++);
		ImGui::Text("CHANGE FOV");
		ed::BeginPin(uniqueID++, ed::PinKind::Input);
		ImGui::Text(ICON_FA_ARROW_RIGHT " In");
		ed::EndPin();
		ImGui::SameLine();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::EndNode();
	}
	if (ADD_NODE_CHANGE_PERCENT_TEXTURE_variable == 1) {
		ed::SetNodePosition(uniqueID++, ImVec2(50, 150));
		ed::BeginNode(uniqueID++);
		ImGui::Text("CHANGE PERCENT TEXTURE");
		ed::BeginPin(uniqueID++, ed::PinKind::Input);
		ImGui::Text(ICON_FA_ARROW_RIGHT " In");
		ed::EndPin();
		ImGui::SameLine();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::EndNode();
	}
	if (ADD_NODE_CHANGE_POSITION_X_variable == 1) {
		ed::SetNodePosition(uniqueID++, ImVec2(50, 150));
		ed::BeginNode(uniqueID++);
		ImGui::Text("CHANGE POSITION X");
		ed::BeginPin(uniqueID++, ed::PinKind::Input);
		ImGui::Text(ICON_FA_ARROW_RIGHT " In");
		ed::EndPin();
		ImGui::SameLine();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::EndNode();
	}
	if (ADD_NODE_CHANGE_POSITION_Y_variable == 1) {
		ed::SetNodePosition(uniqueID++, ImVec2(50, 150));
		ed::BeginNode(uniqueID++);
		ImGui::Text("CHANGE POSITION Y");
		ed::BeginPin(uniqueID++, ed::PinKind::Input);
		ImGui::Text(ICON_FA_ARROW_RIGHT " In");
		ed::EndPin();
		ImGui::SameLine();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::EndNode();
	}
	if (ADD_NODE_CHANGE_POSITION_Z_variable == 1) {
		ed::SetNodePosition(uniqueID++, ImVec2(50, 150));
		ed::BeginNode(uniqueID++);
		ImGui::Text("CHANGE POSITION Z");
		ed::BeginPin(uniqueID++, ed::PinKind::Input);
		ImGui::Text(ICON_FA_ARROW_RIGHT " In");
		ed::EndPin();
		ImGui::SameLine();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::EndNode();
	}
	if (ADD_NODE_CHANGE_SIZE_X_variable == 1) {
		ed::SetNodePosition(uniqueID++, ImVec2(50, 150));
		ed::BeginNode(uniqueID++);
		ImGui::Text("CHANGE SIZE X");
		ed::BeginPin(uniqueID++, ed::PinKind::Input);
		ImGui::Text(ICON_FA_ARROW_RIGHT " In");
		ed::EndPin();
		ImGui::SameLine();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::EndNode();
	}
	if (ADD_NODE_CHANGE_SIZE_Y_variable == 1) {
		ed::SetNodePosition(uniqueID++, ImVec2(50, 150));
		ed::BeginNode(uniqueID++);
		ImGui::Text("CHANGE SIZE Y");
		ed::BeginPin(uniqueID++, ed::PinKind::Input);
		ImGui::Text(ICON_FA_ARROW_RIGHT " In");
		ed::EndPin();
		ImGui::SameLine();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::EndNode();
	}
	if (ADD_NODE_CHANGE_SIZE_Z_variable == 1) {
		ed::SetNodePosition(uniqueID++, ImVec2(50, 150));
		ed::BeginNode(uniqueID++);
		ImGui::Text("CHANGE SIZE Z");
		ed::BeginPin(uniqueID++, ed::PinKind::Input);
		ImGui::Text(ICON_FA_ARROW_RIGHT " In");
		ed::EndPin();
		ImGui::SameLine();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::EndNode();
	}
	if (ADD_NODE_MOVE_CAMERA_DOWN_variable == 1) {
		ed::SetNodePosition(uniqueID++, ImVec2(50, 150));
		ed::BeginNode(uniqueID++);
		ImGui::Text("MOVE CAMERA DOWN");
		ed::BeginPin(uniqueID++, ed::PinKind::Input);
		ImGui::Text(ICON_FA_ARROW_RIGHT " In");
		ed::EndPin();
		ImGui::SameLine();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::EndNode();
	}
	if (ADD_NODE_MOVE_CAMERA_LEFT_variable == 1) {
		ed::SetNodePosition(uniqueID++, ImVec2(50, 150));
		ed::BeginNode(uniqueID++);
		ImGui::Text("MOVE CAMERA LEFT");
		ed::BeginPin(uniqueID++, ed::PinKind::Input);
		ImGui::Text(ICON_FA_ARROW_RIGHT " In");
		ed::EndPin();
		ImGui::SameLine();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::EndNode();
	}
	if (ADD_NODE_MOVE_CAMERA_RIGHT_variable == 1) {
		ed::SetNodePosition(uniqueID++, ImVec2(50, 150));
		ed::BeginNode(uniqueID++);
		ImGui::Text("MOVE CAMERA RIGHT");
		ed::BeginPin(uniqueID++, ed::PinKind::Input);
		ImGui::Text(ICON_FA_ARROW_RIGHT " In");
		ed::EndPin();
		ImGui::SameLine();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::EndNode();
	}
	if (ADD_NODE_MOVE_CAMERA_UP_variable == 1) {
		ed::SetNodePosition(uniqueID++, ImVec2(50, 150));
		ed::BeginNode(uniqueID++);
		ImGui::Text("MOVE CAMERA UP");
		ed::BeginPin(uniqueID++, ed::PinKind::Input);
		ImGui::Text(ICON_FA_ARROW_RIGHT " In");
		ed::EndPin();
		ImGui::SameLine();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::EndNode();
	}
	if (ADD_NODE_ROTATE_AROUD_X_MATRIX_variable == 1) {
		ed::SetNodePosition(uniqueID++, ImVec2(50, 150));
		ed::BeginNode(uniqueID++);
		ImGui::Text("ROTATE AROUND X AXES");
		ed::BeginPin(uniqueID++, ed::PinKind::Input);
		ImGui::Text(ICON_FA_ARROW_RIGHT " In");
		ed::EndPin();
		ImGui::SameLine();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::EndNode();
	}
	if (ADD_NODE_ROTATE_AROUND_Y_MATRIX_variable == 1)
	{
		ed::SetNodePosition(uniqueID++, ImVec2(50, 150));
		ed::BeginNode(uniqueID++);
		ImGui::Text("ROTATE AROUND Y AXES");
		ed::BeginPin(uniqueID++, ed::PinKind::Input);
		ImGui::Text(ICON_FA_ARROW_RIGHT " In");
		ed::EndPin();
		ImGui::SameLine();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::EndNode();
	}
	if (ADD_NODE_ROTATE_AROUND_Z_MATRIX_variable == 1) {
		ed::SetNodePosition(uniqueID++, ImVec2(50, 150));
		ed::BeginNode(uniqueID++);
		ImGui::Text("ROTATE AROUND Z AXES");
		ed::BeginPin(uniqueID++, ed::PinKind::Input);
		ImGui::Text(ICON_FA_ARROW_RIGHT " In");
		ed::EndPin();
		ImGui::SameLine();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::BeginPin(uniqueID++, ed::PinKind::Output);
		ImGui::Text("Out " ICON_FA_ARROW_RIGHT);
		ed::EndPin();
		ed::EndNode();
	}
}

void UserInterface::setNodeButtonFORadd() {
	
	if (ImGui::Button("ROTATE_LEFT", ImVec2(SRC_WIDTH / 6, SRC_HEIGHT / 50))) {
		this->addNode(ADD_NODE_ROTATE_LEFT);
	}
	ImGui::Separator();
	if (ImGui::Button("MOVE CAMERA LEFT", ImVec2(SRC_WIDTH / 6, SRC_HEIGHT / 50))) {
		this->addNode(ADD_NODE_MOVE_CAMERA_LEFT);
	}
	ImGui::Separator();
	if (ImGui::Button("MOVE CAMERA RIGHT", ImVec2(SRC_WIDTH / 6, SRC_HEIGHT / 50))) {
		this->addNode(ADD_NODE_MOVE_CAMERA_RIGHT);
	}
	ImGui::Separator();
	if (ImGui::Button("MOVE CAMERA UP", ImVec2(SRC_WIDTH / 6, SRC_HEIGHT / 50))) {
		this->addNode(ADD_NODE_MOVE_CAMERA_UP);
	}
	ImGui::Separator();
	if (ImGui::Button("MOVE CAMERA DOWN", ImVec2(SRC_WIDTH / 6, SRC_HEIGHT / 50))) {
		this->addNode(ADD_NODE_MOVE_CAMERA_DOWN);
	}
	ImGui::Separator();
	if (ImGui::Button("ROTATE AROUD X AXES", ImVec2(SRC_WIDTH / 6, SRC_HEIGHT / 50))) {
		this->addNode(ADD_NODE_ROTATE_AROUD_X_MATRIX);
	}
	ImGui::Separator();
	if (ImGui::Button("ROTATE AROUND Y AXES", ImVec2(SRC_WIDTH / 6, SRC_HEIGHT / 50))) {
		this->addNode(ADD_NODE_ROTATE_AROUND_Y_MATRIX);
	}
	ImGui::Separator();
	if (ImGui::Button("ROTATE AROUND Z AXES", ImVec2(SRC_WIDTH / 6, SRC_HEIGHT / 50))) {
		this->addNode(ADD_NODE_ROTATE_AROUND_Z_MATRIX);
	}
	ImGui::Separator();
	if (ImGui::Button("CHANGE CAMERA SPEED", ImVec2(SRC_WIDTH / 6, SRC_HEIGHT / 50))) {
		this->addNode(ADD_NODE_CHANGE_CAMERA_SPEED);
	}
	ImGui::Separator();
	if (ImGui::Button("CHANGE PERCENT TEXTURE", ImVec2(SRC_WIDTH / 6, SRC_HEIGHT / 50))) {
		this->addNode(ADD_NODE_CHANGE_PERCENT_TEXTURE);
	}
	ImGui::Separator();
	if (ImGui::Button("CHANGE POSITION X", ImVec2(SRC_WIDTH / 6, SRC_HEIGHT / 50))) {
		this->addNode(ADD_NODE_CHANGE_POSITION_X);
	}
	ImGui::Separator();
	if (ImGui::Button("CHANGE POSITION Y", ImVec2(SRC_WIDTH / 6, SRC_HEIGHT / 50))) {
		this->addNode(ADD_NODE_CHANGE_POSITION_Y);
	}
	ImGui::Separator();
	if (ImGui::Button("CHANGE POSITION Z", ImVec2(SRC_WIDTH / 6, SRC_HEIGHT / 50))) {
		this->addNode(ADD_NODE_CHANGE_POSITION_Z);
	}
	ImGui::Separator();
	if (ImGui::Button("CHANGE COLOR FRAME", ImVec2(SRC_WIDTH / 6, SRC_HEIGHT / 50))) {
		this->addNode(ADD_NODE_CHANGE_COLOR_FRAME);
	}
	ImGui::Separator();
	if (ImGui::Button("CHANGE COLOR OBJECT", ImVec2(SRC_WIDTH / 6, SRC_HEIGHT / 50))) {
		this->addNode(ADD_NODE_CHANGE_COLOR_OBJECT);
	}
	ImGui::Separator();
	if (ImGui::Button("CHANGE FOV", ImVec2(SRC_WIDTH / 6, SRC_HEIGHT / 50))) {
		this->addNode(ADD_NODE_CHANGE_FOV);
	}
	ImGui::Separator();
	if (ImGui::Button("CHANGE SIZE X", ImVec2(SRC_WIDTH / 6, SRC_HEIGHT / 50))) {
		this->addNode(ADD_NODE_CHANGE_SIZE_X);
	}
	ImGui::Separator();
	if (ImGui::Button("CHANGE SIZE Y", ImVec2(SRC_WIDTH / 6, SRC_HEIGHT / 50))) {
		this->addNode(ADD_NODE_CHANGE_SIZE_Y);
	}
	ImGui::Separator();
	if (ImGui::Button("CHANGE SIZE Z", ImVec2(SRC_WIDTH / 6, SRC_HEIGHT / 50))) {
		this->addNode(ADD_NODE_CHANGE_SIZE_Z);
	}
	ImGui::Separator();
	if (ImGui::Button("CHANGE DIRECTION ROTATE MATRIX", ImVec2(SRC_WIDTH / 6, SRC_HEIGHT / 50))) {
		this->addNode(ADD_NODE_CHANGE_DIRECTION_ROTATE_MATRIX);
	}
	ImGui::Separator();

}
void UserInterface::addNode(int typeOfNode) {
	switch (typeOfNode)
	{
	case ADD_NODE_ROTATE_RIGHT:
		ADD_NODE_ROTATE_RIGHT_variable = 1;
		break;
	case ADD_NODE_ROTATE_LEFT:
		ADD_NODE_ROTATE_LEFT_variable = 1;
		break;
	case ADD_NODE_MOVE_CAMERA_LEFT:
		ADD_NODE_MOVE_CAMERA_LEFT_variable = 1;
		break;
	case ADD_NODE_MOVE_CAMERA_RIGHT:
		ADD_NODE_MOVE_CAMERA_RIGHT_variable = 1;
		break;
	case ADD_NODE_MOVE_CAMERA_UP:
		ADD_NODE_MOVE_CAMERA_UP_variable = 1;
		break;
	case ADD_NODE_MOVE_CAMERA_DOWN:
		ADD_NODE_MOVE_CAMERA_DOWN_variable = 1;
		break;
	case ADD_NODE_ROTATE_AROUD_X_MATRIX:
		ADD_NODE_ROTATE_AROUD_X_MATRIX_variable = 1;
		break;
	case ADD_NODE_ROTATE_AROUND_Y_MATRIX:
		ADD_NODE_ROTATE_AROUND_Y_MATRIX_variable = 1;
		break;
	case ADD_NODE_ROTATE_AROUND_Z_MATRIX:
		ADD_NODE_ROTATE_AROUND_Z_MATRIX_variable = 1;
		break;
	case ADD_NODE_CHANGE_CAMERA_SPEED:
		ADD_NODE_CHANGE_CAMERA_SPEED_variable = 1;
		break;
	case ADD_NODE_CHANGE_PERCENT_TEXTURE:
		ADD_NODE_CHANGE_PERCENT_TEXTURE_variable = 1;
		break;
	case ADD_NODE_CHANGE_POSITION_X:
		ADD_NODE_CHANGE_POSITION_X_variable = 1;
		break;
	case ADD_NODE_CHANGE_POSITION_Y:
		ADD_NODE_CHANGE_POSITION_Y_variable = 1;
		break;
	case ADD_NODE_CHANGE_POSITION_Z:
		ADD_NODE_CHANGE_POSITION_Z_variable = 1;
		break;
	case ADD_NODE_CHANGE_COLOR_FRAME:
		ADD_NODE_CHANGE_COLOR_FRAME_variable = 1;
		break;
	case ADD_NODE_CHANGE_COLOR_OBJECT:
		ADD_NODE_CHANGE_COLOR_OBJECT_variable = 1;
		break;
	case ADD_NODE_CHANGE_FOV:
		ADD_NODE_CHANGE_FOV_variable = 1;
		break;
	case ADD_NODE_CHANGE_SIZE_X:
		ADD_NODE_CHANGE_SIZE_X_variable = 1;
		break;
	case ADD_NODE_CHANGE_SIZE_Y:
		ADD_NODE_CHANGE_SIZE_Y_variable = 1;
		break;
	case ADD_NODE_CHANGE_SIZE_Z:
		ADD_NODE_CHANGE_SIZE_Z_variable = 1;
		break;
	case ADD_NODE_CHANGE_DIRECTION_ROTATE_MATRIX:
		ADD_NODE_CHANGE_DIRECTION_ROTATE_MATRIX_variable = 1;
		break;
	default:
		break;
	}
}
void UserInterface::endFrame() {
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
// editor color
void UserInterface::setColorEditorFrame(int objectOrFrame) { ImGui::ColorEdit3("color(frame)", lastedColorFrame); }
void UserInterface::setColorEditorObject(int objectOrFrame) { ImGui::ColorEdit3("color(object)", LastedColorObject); }

void UserInterface::setLastedmatrix() {
	LastedFloatFrame = *size1;
}
// getting value
int UserInterface::getIndicatorTextureFilePath() { return lastedFilePath; }
float& UserInterface::getValueRotateX() { return LastedRotateXValue; }
float& UserInterface::getValueRotateY() { return LastedRotateYValue; }
float& UserInterface::getValueRotateZ() { return LastedRotateZValue; }
float UserInterface::getFOV_Value() const { return FOV; }
float UserInterface::getPositionObjectX() const { return LastedPositionObjectX; }
float UserInterface::getPositionObjectY() const { return LastedPositionObjectY; }
float UserInterface::getPositionObjectZ() const { return LastedPositionObjectZ; }
float UserInterface::getpercentTexture() const { return percentTexture; }
float UserInterface::getCmerraSpeed() const { return CameraSpeed; }
float UserInterface::getScaleCubeX() const { return LastedFloatFrameX; }
float UserInterface::getScaleCubeY() const { return LastedFloatFrameY; }
float UserInterface::getScaleCubeZ() const { return LastedFloatFrameZ; }

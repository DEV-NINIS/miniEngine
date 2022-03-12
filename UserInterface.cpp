#include "UserInterface.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_opengl3_loader.h"
#include "imgui/imgui_internal.h"
#include "icons.h"
#include "iconcpp.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

char UserInterface::filePath1[] = { 0 };
char UserInterface::filePath2[] = { 0 };
char UserInterface::filePath3[] = { 0 };
char UserInterface::filePath4[] = { 0 };
char UserInterface::filePath5[] = { 0 };
const char* UserInterface::filepath1ConstChar = 0;
const char* UserInterface::filepath2ConstChar = 0;
float UserInterface::LastedColorObject[] = { 0 };

UserInterface::UserInterface(GLFWwindow* window)  {
	
	LastedFrameColorR = 0.2f; LastedFrameColorG = 0.5f; LastedFrameColorB = 0.7f; 
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
	LastedFrameColorR = LastedFrameColorRFile; LastedFrameColorG = LastedFrameColorGFile; LastedFrameColorB = LastedFrameColorBFile;
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
void UserInterface::interfacebeginCanvas() {
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
		ImGuiWindowFlags_NoBackground;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(ImVec2(viewport->WorkSize.x - viewport->WorkSize.x * 0.9, viewport->WorkSize.y));

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 10.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::PopStyleVar(3);
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
	style->WindowMinSize = ImVec2(2560 / 4.5, 430);
	style->FramePadding = ImVec2(2, 2);
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
	if (ImGui::Button(ICON_FA_UPLOAD "  select folder for texture 1", ImVec2(220, 30))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandSelectFolderForTex2() const {
	if (ImGui::Button(ICON_FA_UPLOAD "  select folder for texture 2", ImVec2(220, 30))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingAnimation() const {
	if (ImGui::CollapsingHeader("Animation")) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingCamera() const {
	if (ImGui::Button( "Camera", ImVec2(200, 30)) == true) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandCameraSpeed() const {
	if (ImGui::Button("Camera Speed", ImVec2(150, 20)) == true) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingRotateLeft() const {
	if (ImGui::Button("save direction and Rotate", ImVec2(200, 20))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingRotateRight() const {
	if (ImGui::Button("change direction <- -> ", ImVec2(175, 20))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingRotate() const {
	if (ImGui::Button("Rotate", ImVec2(60, 40))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingTexture1() const {
	if (ImGui::Button("Texture", ImVec2(300, 40))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingRotateAroundX() const {
	if (ImGui::Button("Rotate X", ImVec2(65, 20))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingRotateAroundY() const {
	if (ImGui::Button("Rotate Y", ImVec2(65, 20))) {
		return true;
	}
	else { return false; }
}bool UserInterface::inputDemandingRotateAroundZ() const {
	if (ImGui::Button("Rotate Z", ImVec2(65, 20))) {
		return true;
	}
	else { return false; }
}
float UserInterface::setScaleCube() {
	ImGui::SliderFloat("size all", &LastedFloatFrame, 0.0, 10.0);
	return LastedFloatFrame;
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
bool UserInterface::ButtonForSetAnimation() {
	if (ImGui::Button("Animation", ImVec2(300, 40))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::confirmFilePath() const {
	if (ImGui::Button("load", ImVec2(50, 20))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingChangeFOV() const {
	if (ImGui::Button("FOV", ImVec2(200, 30))) {
		return true;
	}
	else { return false; }
}
void UserInterface::setColorR() {
	ImGui::SliderFloat("R", &LastedFrameColorR, 0, 1);
	if (LastedFrameColorR < -401602080) {
		LastedFrameColorR = 0.4f;
	}
}
void UserInterface::setColorG() {
	ImGui::SliderFloat("G", &LastedFrameColorG, 0, 1);
	if (LastedFrameColorG < -401602080) {
		LastedFrameColorG = 0.1f;
	}
}
void UserInterface::setColorB() {
	ImGui::SliderFloat("B", &LastedFrameColorB, 0, 1);
	if (LastedFrameColorB < -401602080) {
		LastedFrameColorB = 0.9f;
	}
}
void UserInterface::setChangeFOV() {
	ImGui::SliderFloat("change FOV", &FOV, 10, 145);
	if (FOV < -401602080) {
		FOV = 45.0f;
	}
}
void UserInterface::inputFileTexture1(char* filePath) {
	ImGui::Text(filePath, ": is your filepath");
}
void UserInterface::inputFileTexture2(char* filePath) {
	ImGui::Text(filePath, ": is your filepath");
}

void UserInterface::setColorObjectR() {
	ImGui::SliderFloat("R", &LastedColorObject[0], 0, 1);
	if (LastedColorObject[0] < -401602080) {
		LastedColorObject[0] = 0.5f;
	}
}
void UserInterface::setColorObjectG() {
	ImGui::SliderFloat("G", &LastedColorObject[1], 0, 1);
	if (LastedColorObject[1] < -401602080) {
		LastedColorObject[1] = 0.5f;
	}
}
void UserInterface::setColorObjectB() {
	ImGui::SliderFloat("B", &LastedColorObject[2], 0, 1);
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
void UserInterface::setPercentTexture() {
	ImGui::SliderFloat("percentTexture", &percentTexture, 0, 1);
}
void UserInterface::endFrame() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void UserInterface::setColorEditor() {
	ImGui::ColorEdit3("color", LastedColorObject);
}
void UserInterface::setLastedmatrix() {
	LastedFloatFrame = *size1;
}
// getting value
int UserInterface::getIndicatorTextureFilePath() { return lastedFilePath; }
float& UserInterface::getValueRotateX() { return LastedRotateXValue; }
float& UserInterface::getValueRotateY() { return LastedRotateYValue; }
float& UserInterface::getValueRotateZ() { return LastedRotateZValue; }
float UserInterface::getColorR() const { return LastedFrameColorR; }
float UserInterface::getColorG() const { return LastedFrameColorG; }
float UserInterface::getColorB() const { return LastedFrameColorB; }
float UserInterface::getFOV_Value() const { return FOV; }
float UserInterface::getColorObjectR() const { return LastedColorObject[0]; }
float UserInterface::getColorObjectG() const { return LastedColorObject[1]; }
float UserInterface::getColorObjectB() const { return LastedColorObject[2]; }
float UserInterface::getPositionObjectX() const { return LastedPositionObjectX; }
float UserInterface::getPositionObjectY() const { return LastedPositionObjectY; }
float UserInterface::getPositionObjectZ() const { return LastedPositionObjectZ; }
float UserInterface::getpercentTexture() const { return percentTexture; }
float UserInterface::getCmerraSpeed() const { return CameraSpeed; }
float UserInterface::getScaleCubeX() const { return LastedFloatFrameX; }
float UserInterface::getScaleCubeY() const { return LastedFloatFrameY; }
float UserInterface::getScaleCubeZ() const { return LastedFloatFrameZ; }

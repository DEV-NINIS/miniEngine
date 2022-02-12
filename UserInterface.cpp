#include "UserInterface.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_internal.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

char UserInterface::filePath1[] = { 0 };
char UserInterface::filePath2[] = { 0 };
char UserInterface::filePath3[] = { 0 };
char UserInterface::filePath4[] = { 0 };
char UserInterface::filePath5[] = { 0 };
UserInterface::UserInterface(GLFWwindow* window)  {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
	auto& style = ImGui::GetStyle();
	ImVec4* color = ImGui::GetStyle().Colors;
	color[ImGuiCol_WindowBg] = ImVec4(0.1, 0.3, 0.5, 0.9);
	LastedFrameColorR = 0.2f; LastedFrameColorG = 0.5f; LastedFrameColorB = 0.7f; 
	LastedFloatFrame = 1.0f; LastedFloatFrameX = 1.0f; LastedFloatFrameY = 1.0f; LastedFloatFrameZ = 1.0f; 
	LastedRotateXValue = 0.1f; LastedRotateYValue = 0.0f; LastedRotateZValue = 0.0f;
	size1 = new float;
	FOV = 55.0f;
	lastedFilePath = -1;
	LastedColorObjectR = 0.5f; LastedColorObjectG = 0.6f; LastedColorObjectB = 0.9f; 
	LastedPositionObjectX = 0.0f; LastedPositionObjectY = 0.0f; LastedPositionObjectZ = 0.0f;
	filePathPointer.push_back(new char); *filePathPointer[0] = '0';
	filePathPointer.push_back(new char); *filePathPointer[1] = '0';
	filePathPointer.push_back(new char); *filePathPointer[2] = '0';
	filePathPointer.push_back(new char); *filePathPointer[3] = '0';
	filePathPointer.push_back(new char); *filePathPointer[4] = '0';
}
UserInterface::~UserInterface() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void UserInterface::setSettingFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}
bool UserInterface::inputDemandingAnimation() const {
	if (ImGui::CollapsingHeader("Animation")) {
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
bool UserInterface::inputDemandingScaleCube() const {
	ImGui::Text("@Dev_ninis Frame : ", ImGui::GetFrameHeight());
	if (ImGui::Button("Size Object", ImVec2(300, 40))) {
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
bool UserInterface::inputDemandingScaleCubeX() const {
	if (ImGui::Button("size X", ImVec2(60, 40))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingScaleCubeY() const {
	if (ImGui::Button("size Y", ImVec2(60, 40))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingScaleCubeZ() const {
	if (ImGui::Button("size Z", ImVec2(60, 40))) {
		return true;
	}
	else { return false; }
}
float UserInterface::setScaleCube() {
	ImGui::SliderFloat("size", &*size1, -5.0f, 5.0f);
	LastedFloatFrame = *size1;
	return *size1;
	delete size1;
}
float UserInterface::setScaleCubeX() {
	float* size2 = nullptr; size2 = new float;
	ImGui::SliderFloat("sizeX", &*size2, -5.0f, 5.0f);
	if (*size2 > -401602080) {
		LastedFloatFrameX = *size2;
		return *size2;
	}
	else { 
		return LastedFloatFrameX;
	}
	delete size2;
}
float UserInterface::setScaleCubeY() {
	float* size3 = nullptr; size3 = new float;
	ImGui::SliderFloat("sizeY", &*size3, -5.0f, 5.0f);
	if (*size3 > -401602080) {
		LastedFloatFrameY = *size3;
		return *size3;
	}
	else {
		return LastedFloatFrameY;
	}
	delete size3;
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
float UserInterface::setScaleCubeZ() {
	float* size4 = nullptr; size4 = new float;
	ImGui::SliderFloat("sizeZ", &*size4, -5.0f, 5.0f);
	if (*size4 > -401602080) {
		LastedFloatFrameZ = *size4;
		return *size4;
	}
	else {
		return LastedFloatFrameZ;
	}
	delete size4;
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
bool UserInterface::inputColorR() const {
	if (ImGui::Button("R:", ImVec2(20, 20))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputColorG() const {
	if (ImGui::Button("G:", ImVec2(20, 20))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputColorB() const {
	if (ImGui::Button("B:", ImVec2(20, 20))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputColorA() const {
	if (ImGui::Button("A:", ImVec2(20, 20))) {
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
bool UserInterface::inputDemandingChangeColorObject() const {
	if (ImGui::Button("Color Object", ImVec2(300, 40))) {
		return true;
	}
	else { return false; }
}
// position object
bool UserInterface::inputDemandingPositionObject() const {
	if (ImGui::Button("Position Object", ImVec2(300, 40))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingPositionObjectX() const {
	if (ImGui::Button("position X Object", ImVec2(125, 20))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingPositionObjectY() const {
	if (ImGui::Button("position Y Object", ImVec2(125, 20))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingPositionObjectZ() const {
	if (ImGui::Button("position Z Object", ImVec2(125, 20))) {
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
void UserInterface::inputFileTexture1(std::vector<int*> successLoaderTexture) {
	ImGui::InputText("texture 1", this->filePath1, IM_ARRAYSIZE(this->filePath1));
	if (*successLoaderTexture[0] == 1) { ImGui::Text("failer to load texture"); }
}
void UserInterface::inputFileTexture2(std::vector<int*> successLoaderTexture) {
	ImGui::InputText("texture 1", this->filePath2, IM_ARRAYSIZE(this->filePath2));
	if (*successLoaderTexture[1] == 1) { ImGui::Text("failer to load texture"); }
}
void UserInterface::inputFileTexture3(std::vector<int*> successLoaderTexture) {
	ImGui::InputText("texture 1", this->filePath3, IM_ARRAYSIZE(this->filePath3));
	if (*successLoaderTexture[2] == 1) { ImGui::Text("failer to load texture"); }
}
void UserInterface::inputFileTexture4(std::vector<int*> successLoaderTexture) {
	ImGui::InputText("texture 1", this->filePath4, IM_ARRAYSIZE(this->filePath4));
	if (*successLoaderTexture[3] == 1) { ImGui::Text("failer to load texture"); }
}
void UserInterface::inputFileTexture5(std::vector<int*> successLoaderTexture) {
	ImGui::InputText("texture 1", this->filePath5, IM_ARRAYSIZE(this->filePath5));
	if (*successLoaderTexture[4] == 1) { ImGui::Text("failer to load texture"); }
}
void UserInterface::setColorObjectR() {
	ImGui::SliderFloat("R", &LastedColorObjectR, 0, 1);
	if (LastedColorObjectR < -401602080) {
		LastedColorObjectR = 0.5f;
	}
}
void UserInterface::setColorObjectG() {
	ImGui::SliderFloat("G", &LastedColorObjectG, 0, 1);
	if (LastedColorObjectG < -401602080) {
		LastedColorObjectG = 0.5f;
	}
}
void UserInterface::setColorObjectB() {
	ImGui::SliderFloat("B", &LastedColorObjectB, 0, 1);
	if (LastedColorObjectB < -401602080) {
		LastedColorObjectB = 0.5f;
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
void UserInterface::endFrame() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
float UserInterface::getColorObjectR() const { return LastedColorObjectR; }
float UserInterface::getColorObjectG() const { return LastedColorObjectG; }
float UserInterface::getColorObjectB() const { return LastedColorObjectB; }
float UserInterface::getPositionObjectX() const { return LastedPositionObjectX; }
float UserInterface::getPositionObjectY() const { return LastedPositionObjectY; }
float UserInterface::getPositionObjectZ() const { return LastedPositionObjectZ; }
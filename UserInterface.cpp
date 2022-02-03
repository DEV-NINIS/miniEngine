#include "UserInterface.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_internal.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

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
	LastedFloatFrame = 1.0f; LastedFloatFrameX = 1.0f; LastedFloatFrameY = 1.0f; LastedFloatFrameZ = 1.0f; 
	LastedRotateXValue = 0.0f; LastedRotateYValue = 0.0f; LastedRotateZValue = 0.0f;
	size1 = new float;
}
UserInterface::~UserInterface() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void UserInterface::setSettingFrame() {
	
}
bool UserInterface::inputDemandingAnimation() {
	if (ImGui::Button("Animation", ImVec2(150, 40))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingRotateLeft() {
	if (ImGui::Button("save direction and Rotate", ImVec2(200, 20))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingRotateRight() {
	if (ImGui::Button("change direction <- -> ", ImVec2(175, 20))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingRotate() {
	if (ImGui::Button("Rotate", ImVec2(60, 40))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingScaleCube() {
	ImGui::Text("@Dev_ninis Frame : ", ImGui::GetFrameHeight());
	if (ImGui::Button("Size Cube", ImVec2(150, 40))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingRotateAroundX() {
	if (ImGui::Button("Rotate X", ImVec2(65, 20))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingRotateAroundY() {
	if (ImGui::Button("Rotate Y", ImVec2(65, 20))) {
		return true;
	}
	else { return false; }
}bool UserInterface::inputDemandingRotateAroundZ() {
	if (ImGui::Button("Rotate Z", ImVec2(65, 20))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingScaleCubeX() {
	if (ImGui::Button("size X", ImVec2(60, 40))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingScaleCubeY() {
	if (ImGui::Button("size Y", ImVec2(60, 40))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingScaleCubeZ() {
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
bool UserInterface::setSettings() {
	if (ImGui::Button("settings ", ImVec2(75, 20))) {
		return true;
	}
	else { return false; }
}
bool UserInterface::ButtonForSetAnimation() {
	if (ImGui::Button("Animation ", ImVec2(75, 40))) {
		return true;
	}
	else { return false; }
}
char UserInterface::inputFileTexture() {
	char* FilePath; FilePath = new char; *FilePath = 'a';
	ImGui::InputText("path texture", FilePath, IM_ARRAYSIZE(FilePath));
	return *FilePath;
}
void UserInterface::endFrame() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void UserInterface::setLastedmatrix() {
	LastedFloatFrame = *size1;
}
// getting value
float& UserInterface::getValueRotateX() { return LastedRotateXValue; }
float& UserInterface::getValueRotateY() { return LastedRotateYValue; }
float& UserInterface::getValueRotateZ() { return LastedRotateZValue; }
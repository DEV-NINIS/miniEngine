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
	
	LastedFloatFrame = 1.0f; LastedFloatFrameX = 1.0f; LastedFloatFrameY = 1.0f; LastedFloatFrameZ = 1.0f; 
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
bool UserInterface::inputDemandingScaleCube() {
	ImGui::Text("@Dev_ninis Frame : ", ImGui::GetFrameHeight());
	if (ImGui::Button("Enter size Cube", ImVec2(150, 40))) {
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
	ImGui::SliderFloat("size", &*size1, -5, 5);
	LastedFloatFrame = *size1;
	return *size1;
	delete size1;
}
float UserInterface::setScaleCubeX() {
	float* size2 = nullptr; size2 = new float;
	ImGui::SliderFloat("sizeX", &*size2, -5, 5);
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
	ImGui::SliderFloat("sizeY", &*size3, -5, 5);
	if (*size3 > -401602080) {
		LastedFloatFrameY = *size3;
		return *size3;
	}
	else {
		return LastedFloatFrameY;
	}
	delete size3;
}
float UserInterface::setScaleCubeZ() {
	float* size4 = nullptr; size4 = new float;
	ImGui::SliderFloat("sizeZ", &*size4, -5, 5);
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

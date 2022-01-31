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
	LastedFloatFrame = 1.0f; LastedFloatFrameX = 1.0f; LastedFloatFrameY = 1.0f; LastedFloatFrameZ = 1.0f;
	// theme 
	auto& style = ImGui::GetStyle();
	ImVec4* color = ImGui::GetStyle().Colors;
	color[ImGuiCol_WindowBg] = ImVec4(0.1, 0.3, 0.5, 0.9); 
	size1 = new float;
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
bool UserInterface::inputDemandingScaleCube() {
	ImGui::Text("@Dev_ninis");
	if (ImGui::Button("Enter size Cube")) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingScaleCubeX() {
	if (ImGui::Button("size X")) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingScaleCubeY() {
	if (ImGui::Button("size Y")) {
		return true;
	}
	else { return false; }
}
bool UserInterface::inputDemandingScaleCubeZ() {
	if (ImGui::Button("size Z")) {
		return true;
	}
	else { return false; }
}
float UserInterface::setScaleCube() {
	ImGui::SliderFloat("size", &*size1, -2, 3);
	LastedFloatFrame = *size1;
	return *size1;
	delete size1;
}
float UserInterface::setScaleCubeX() {
	float* size2 = nullptr; size2 = new float;
	ImGui::SliderFloat("sizeX", &*size2, -2, 3);
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
char UserInterface::inputFileTexture() {
	char* FilePath = 0;
	ImGui::InputText("string", FilePath, IM_ARRAYSIZE(FilePath));
	return *FilePath;
}
void UserInterface::endFrame() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void UserInterface::setLastedmatrix() {
	LastedFloatFrame = *size1;
}

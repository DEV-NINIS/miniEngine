#include "UserInterface.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_internal.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

UserInterface::UserInterface(GLFWwindow* window) : glmAnimation3D() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
	LastedFloatFrame;
	// theme 
	auto& style = ImGui::GetStyle();
	ImVec4* color = ImGui::GetStyle().Colors;
	color[ImGuiCol_WindowBg] = ImVec4(0.4, 0.6, 0.5, 0.3); 
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
	ImGui::End();
}
float UserInterface::setScaleCube(GLuint shader) {
	float* size; size = new float;
	ImGui::SliderFloat("size", &*size, -2, 2);
	glmAnimation3D::setScaleValue(shader, *size);
	LastedFloatFrame = *size;
	std::cout << *size << std::endl;
	return *size;
	delete size;
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

#include "UserInterface.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_internal.h"
#include <iostream>
#include <vector>

UserInterface::UserInterface(GLFWwindow* window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
	// theme 
	auto& style = ImGui::GetStyle();
	ImVec4* color = ImGui::GetStyle().Colors;
	color[ImGuiCol_WindowBg] = ImVec4(0.8, 0.5, 0.2, 0.9);
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
void UserInterface::BasicFonction() {
	ImGui::Text("hello amigos");
	ImGui::Button("ok");
}
void UserInterface::endFrame() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

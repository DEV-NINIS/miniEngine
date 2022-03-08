#include "object.h"
#include "UserInterface.h"
#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stbi_image.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

using namespace objectUser;

float Mesh::verteciesObject[] = {
	0
};
unsigned int Mesh::indexObject[] {
	0
};

Mesh::Mesh(GLFWwindow* window) {
	objectVAO; objectVBO; objectEBO;
	// shaders
	shaderProgram; shaderFrag; shaderVertex;
	vertexShaderCODE = "#version 460 core\n"
		"";
	fragmentShaderCODE = "";
}
Mesh::~Mesh() {

}
void Mesh::CompileShaderObject() {

}
void Mesh::setBufferObject() {
	glGenVertexArrays(1, &objectVAO);
	glBindVertexArray(objectVAO);

	glGenBuffers(1, &objectVBO);
	glBindBuffer(GL_ARRAY_BUFFER, objectVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verteciesObject), verteciesObject, GL_STATIC_DRAW);
}
void Mesh::OpenShader(std::string filePathVertex, std::string filePathFragment) {
	std::string FileContent;
	std::ifstream fluxVertex(filePathVertex.c_str());
	while (std::getline(fluxVertex, FileContent)) {}
	vertexShaderCODE = static_cast<const char*>(FileContent.c_str());
	FileContent = "";
	std::ifstream fluxFragment(filePathFragment.c_str());
	while (std::getline(fluxFragment, FileContent)) {}
	fragmentShaderCODE = static_cast<const char*>(FileContent.c_str());
}


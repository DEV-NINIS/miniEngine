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
		"layout (location = 0) in vec3 position;\n"
		"layout (location = 1) in vec3 color;\n"
		"layout (location = 2) in vec2 Texcoords;\n"
		"out vec3 colorFrag;\n"
		"out vec2 TexcoordsFrag;\n"
		"uniform mat4 view;\n"
		"uniform mat4 model;\n"
		"uniform mat4 Scale;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 transform;\n"
		"uniform float PositionX;\n"
		"uniform float PositionY;\n"
		"uniform float PositionZ;\n"
		"void main () {\n"
		"if (PositionX == 0 && PositionY == 0 && PositionZ == 0) {\n"
		"gl_Position = projection * view * model * transform * Scale * vec4(aPos, 1.0f);\n"
		"}\n"
		"else {\n"
		"gl_Position = projection * view * model * transform * Scale * vec4(aPos.x + PositionX/20, aPos.y + PositionY/20, aPos.z + PositionZ/20, 1.0f);\n"
		"}\n"
		"colorFrag = color;\n"
		"TexcoordsFrag = Texcoords;\n"
		"}\n\0";

	fragmentShaderCODE = "#version 460 core\n"
		"in vec3 color;\n"
		"out vec4 frag_Color;\n"
		"void main() {\n"
		"frag_Color = vec4(color, 1.0);"
		"}\n\0";
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

	glGenBuffers(1, &objectEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objectEBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(indexObject), indexObject, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
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


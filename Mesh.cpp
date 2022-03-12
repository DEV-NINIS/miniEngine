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
#define LOADER_TEXTURE_SUCCESS 0
#define LOADER_TEXTURE_NOT_SUCCESS 1
using namespace objectUser;

float Mesh::verteciesObject[] = {
	-0.5f, -0.5f, -0.5f,  0.8f, 0.6f, 0.9f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.9f, 0.6f, 0.2f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.5f, 0.6f, 0.9f,1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.7f, 0.6f, 0.8f,1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.1f, 0.6f, 0.9f,0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.3f, 0.6f, 0.1f,0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.2f, 0.1f, 0.9f,0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.9f, 0.6f, 0.9f,1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.2f, 0.2f, 0.9f,1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.3f, 0.6f, 0.1f,1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.2f, 0.3f, 0.9f,0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.2f, 0.6f, 0.9f,0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  0.9f, 0.1f, 0.2f,1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.4f, 0.6f, 0.8f,1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.9f, 0.5f, 0.4f,0.0f, 0.4f,
		-0.5f, -0.5f, -0.5f,  0.2f, 0.2f, 0.8f,0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.6f, 0.6f, 0.9f,0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.6f, 0.5f, 0.3f,1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f, 0.3f, 0.9f, 0.9f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.9f, 0.4f, 0.3f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 0.1f, 0.6f, 0.9f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 0.7f, 0.1f, 0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 0.2f, 0.4f, 0.1f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.7f, 0.9f, 0.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.7f, 0.6f, 0.8f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 0.5f, 0.4f, 0.1f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 0.6f, 0.6f, 0.5f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 0.9f, 0.3f, 0.2f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.1f, 0.9f, 0.7f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.2f, 0.1f, 0.9f, 0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f, 0.8f, 0.8f, 0.8f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 0.4f, 0.7f, 0.5f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 0.2f, 0.4f, 0.6f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.3f, 0.3f, 0.6f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.9f, 0.9f, 0.1f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.1f, 0.1f, 0.4f, 0.0f, 1.0f
};
unsigned int Mesh::indexObject[] {
	0
};

Mesh::Mesh(GLFWwindow* window) {
	// textures
	LoaderTextureSUCCESS.push_back(0);
	LoaderTextureSUCCESS.push_back(0);
	texture1; texture2;
	pathTexture.push_back(new char);
	pathTexture.push_back(new char);
	// buffers
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
		"in vec2 Texcoords;\n"
		"out vec4 frag_Color;\n"
		"uniform float PercentTexture;\n"
		"uniform sampler2D texture1;\n"
		"uniform sampler2D Texture2;\n"
		"uniform float PercentTexture;\n"
		"void main() {\n"
		"frag_Color = mix(texture(texture1, Texcoords), texture(texture2, Texcoords), PercentTexture) * vec4(color, 1.0);"
		"}\n\0";
}
Mesh::~Mesh() {
	glDeleteVertexArrays(1, &objectVAO);
	glDeleteBuffers(1, &objectVBO);
	glDeleteBuffers(1, &objectEBO);
}
float Mesh::variableSize1(float variable) {
	float a = sizeof(variable) / sizeof(float);
	return a;
}
unsigned int Mesh::variableSize(unsigned int variable) {
	unsigned int a = variable / sizeof(unsigned int);
	return a;
}
void Mesh::activeTexture() {
	if (texture1 != 0) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
	}
	if (texture2 != 0) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
	}
}
void Mesh::drawMesh() {
	this->activeTexture();
	glBindVertexArray(objectVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}
void Mesh::CompileShaderMesh() {
	int succesCompileShaders;
	shaderVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shaderVertex, 1, (const GLchar**)vertexShaderCODE, NULL);
	glCompileShader(shaderVertex);
	glGetShaderiv(shaderVertex, GL_COMPILE_STATUS, &succesCompileShaders);
	if (succesCompileShaders == NULL) {
		exit(EXIT_FAILURE);
	}

	shaderFrag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shaderFrag, 1, (const GLchar**)fragmentShaderCODE, NULL);
	glCompileShader(shaderFrag);
	glGetShaderiv(shaderFrag, GL_COMPILE_STATUS, &succesCompileShaders);
	if (succesCompileShaders == NULL) {
		exit(EXIT_FAILURE);
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, shaderVertex);
	glAttachShader(shaderProgram, shaderFrag);
	glLinkProgram(shaderProgram);
}
void Mesh::setTexture1(char* filePath) {
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChanels;
	unsigned char* data = 0;
	pathTexture[0] = static_cast<const char*>(filePath);
	data = stbi_load(pathTexture[0], &width, &height, &nrChanels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
		glUseProgram(shaderProgram);
		glUniform1f(glGetAttribLocation(shaderProgram, "texture1"), 0);
		LoaderTextureSUCCESS[0] = LOADER_TEXTURE_SUCCESS;
	}
	else {
		LoaderTextureSUCCESS[0] = LOADER_TEXTURE_NOT_SUCCESS;
	}
}
void Mesh::setTexture2(char* filePath) {
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChanels;
	unsigned char* data2 = 0;
	pathTexture[0] = static_cast<const char*>(filePath);
	data2 = stbi_load(pathTexture[0], &width, &height, &nrChanels, 0);
	if (data2) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data2);
		glUseProgram(shaderProgram);
		glUniform1f(glGetAttribLocation(shaderProgram, "texture2"), 1);
		LoaderTextureSUCCESS[1] = LOADER_TEXTURE_SUCCESS;
	}
	else {
		LoaderTextureSUCCESS[1] = LOADER_TEXTURE_NOT_SUCCESS;
	}
}
void Mesh::setBufferMesh() {
	glGenVertexArrays(1, &objectVAO);
	glBindVertexArray(objectVAO);

	glGenBuffers(1, &objectVBO);
	glBindBuffer(GL_ARRAY_BUFFER, objectVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verteciesObject), verteciesObject, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &objectEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objectEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexObject), indexObject, GL_DYNAMIC_DRAW);

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

void Mesh::useShaderObject() { glUseProgram(shaderProgram); }
// getting
std::vector<const char*> Mesh::getPathTexture() { return pathTexture; }
GLuint& Mesh::getShaderObject() { return shaderProgram; }
GLuint Mesh::getVertexArray() const { return shaderVertex; }


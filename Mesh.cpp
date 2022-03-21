#pragma warning(disable : 4996)
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
#include <Windows.h>
#include <commdlg.h>
#include <shellapi.h>
#include <fileapi.h>
#include <commdlg.h>
#include <filesystem> // C++17 standard header file name


#define LOADER_TEXTURE_SUCCESS 0
#define LOADER_TEXTURE_NOT_SUCCESS 1
using namespace objectUser;


std::vector<unsigned int> Mesh::indexObject = { 0 };
std::vector<float> Mesh::verteciesObject = { 0 };
std::vector<unsigned int> Mesh::normalIndices = { 0 };

Mesh::Mesh(GLFWwindow* window) {
	// textures
	LoaderTextureSUCCESS.push_back(0);
	LoaderTextureSUCCESS.push_back(0);
	texture1; texture2;
	pathTexture.push_back(new char);
	pathTexture.push_back(new char);

	temp_vertices; temp_uvs; temp_normals;
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
		"uniform mat4 projection;\n"
		"uniform mat4 transform;\n"
		"uniform mat4 Scale;\n"
		"uniform float PositionX;\n"
		"uniform float PositionY;\n"
		"uniform float PositionZ;\n"

		"void main() {\n"
		"if (PositionX == 0 && PositionY == 0 && PositionZ == 0) {\n"
		"gl_Position = projection * view * model * transform * Scale * vec4(position, 1.0f);\n"
		"}\n"
		"else {\n"
		"gl_Position = projection * view * model * transform * Scale * vec4(position.x + PositionX/20, position.y + PositionY/20, position.z + PositionZ/20, 1.0f);\n"
		"}\n"
		"colorFrag = color;\n"
		"TexcoordsFrag = Texcoords;\n"
		"}\n\0";

	fragmentShaderCODE = "#version 460 core\n"

		"in vec3 colorFrag;\n"
		"in vec2 TexcoordsFrag;\n"
		"out vec4 Frag_color;\n"
		"uniform sampler2D Texture1;\n"
		"uniform sampler2D Texture2;\n"
		"uniform float PercentTexture;\n"
		"uniform float ColorR;\n"
		"uniform float ColorG;\n"
		"uniform float ColorB;\n"

		"void main() {\n"
		"if (ColorR == 0 && ColorG == 0 && ColorB == 0) {\n"
		"Frag_color = mix(texture(Texture1, TexcoordsFrag), texture(Texture2, TexcoordsFrag), PercentTexture) * vec4(colorFrag, 1.0);\n"
		"}\n"
		"else {\n"
		"Frag_color = mix(texture(Texture1, TexcoordsFrag), texture(Texture2, TexcoordsFrag), PercentTexture) * vec4(ColorR, ColorG, ColorB, 1.0f);\n"
		"}\n"
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
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
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
	glShaderSource(shaderVertex, 1, (const GLchar**)&vertexShaderCODE, NULL);
	glCompileShader(shaderVertex);
	glGetShaderiv(shaderVertex, GL_COMPILE_STATUS, &succesCompileShaders);
	if (succesCompileShaders == NULL) {
		MessageBoxA(0, static_cast<const char*>("error compilation shaders"), "ERROR", 0);
		exit(EXIT_FAILURE);
		// l'erreur vient des shader !!!!!!!!
	}

	shaderFrag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shaderFrag, 1, (const GLchar**)&fragmentShaderCODE, NULL);
	glCompileShader(shaderFrag);
	glGetShaderiv(shaderFrag, GL_COMPILE_STATUS, &succesCompileShaders);
	if (succesCompileShaders == NULL) {
		MessageBoxA(0, static_cast<const char*>("error compilation shaders"), "ERROR", 0);
		exit(EXIT_FAILURE);
		// l'erreur vient des shader !!!!!!!!
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
		LoaderTextureSUCCESS[0] = LOADER_TEXTURE_SUCCESS;
	}
	else {
		LoaderTextureSUCCESS[0] = LOADER_TEXTURE_NOT_SUCCESS;
	}
	glUseProgram(shaderProgram);
	glUniform1i(glGetAttribLocation(shaderProgram, "texture1"), 0);
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
	pathTexture[1] = static_cast<const char*>(filePath);
	data2 = stbi_load(pathTexture[1], &width, &height, &nrChanels, 0);
	if (data2) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data2);
		LoaderTextureSUCCESS[1] = LOADER_TEXTURE_SUCCESS;
	}
	else {
		LoaderTextureSUCCESS[1] = LOADER_TEXTURE_NOT_SUCCESS;
	}
	glUseProgram(shaderProgram);
	glUniform1i(glGetAttribLocation(shaderProgram, "texture2"), 1);
}
void Mesh::setBufferMesh() {
	glGenVertexArrays(1, &objectVAO);
	glBindVertexArray(objectVAO);

	glGenBuffers(1, &objectVBO);
	glBindBuffer(GL_ARRAY_BUFFER, objectVBO);
	glBufferData(GL_ARRAY_BUFFER, verteciesObject.size() * sizeof(glm::vec3), &verteciesObject[0], GL_STATIC_DRAW);

	glGenBuffers(1, &objectEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objectEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW);

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
	fluxVertex.close();
	FileContent = "";
	std::ifstream fluxFragment(filePathFragment.c_str());
	while (std::getline(fluxFragment, FileContent)) {}
	fragmentShaderCODE = static_cast<const char*>(FileContent.c_str());
	fluxFragment.close();
}
bool Mesh::OpenMeshObjFile(std::string filePath) {
	std::vector<glm::vec3> out_vertices;
	FILE* file = fopen(filePath.c_str(), "r");
		if (file == NULL) {
			MessageBoxA(0, static_cast<const char*>("FAILED TO LOADING MESH"), "ERROR", 0);
			return false;
		}
		while (1) {

			char lineHeader[128];
			// read the first word of the line
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
				break;
			if (strcmp(lineHeader, "v") == 0) {
				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0) {
				glm::vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				temp_uvs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) {
				glm::vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) {
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9) {
					printf("File can't be read by our simple parser : ( Try exporting with other options\n");
					return false;
				}
				verteciesObject.push_back(vertexIndex[0]);
				verteciesObject.push_back(vertexIndex[1]);
				verteciesObject.push_back(vertexIndex[2]);
				indexObject.push_back(uvIndex[0]);
				indexObject.push_back(uvIndex[1]);
				indexObject.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}
		for (unsigned int i = 0; i < verteciesObject.size(); i++) {
			unsigned int vertexIndex = verteciesObject[i];
			glm::vec3 vertex = temp_vertices[vertexIndex - 1];
			out_vertices.push_back(vertex);
		}
}

void Mesh::useShaderObject() { glUseProgram(shaderProgram); }
// getting
std::vector<const char*> Mesh::getPathTexture() { return pathTexture; }
GLuint& Mesh::getShaderObject() { return shaderProgram; }
GLuint Mesh::getVertexArray() const { return shaderVertex; }


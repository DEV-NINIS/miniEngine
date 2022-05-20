#pragma warning(disable : 4996)
#include "object.h"
#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stbi_image.h"
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

GLuint Mesh::index[] = { 0 };
std::vector<GLfloat> Mesh::Vertecies { -0.5f, -0.5f, -0.5f,   0.2f, 0.6f, 0.9f, 0.0f, 0.0f,
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
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.5f, 0.4f,0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.1f, 0.2f, 0.8f,0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  0.6f, 0.6f, 0.9f,0.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  1.0f, 0.5f, 0.3f,1.0f, 0.0f,

		0.5f,  0.5f,  0.5f, 0.3f, 0.9f, 0.9f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f, 0.9f, 0.4f, 0.3f, 1.0f, 1.0f,
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

Mesh::Mesh(GLFWwindow* window) {
	// textures
	LoaderTextureSUCCESS.push_back(0);
	LoaderTextureSUCCESS.push_back(0);
	TextureCube.push_back(new GLuint);
	TextureCube.push_back(new GLuint);
	pathTexture.push_back(new char);
	pathTexture.push_back(new char);

	temp_vertices; temp_uvs; temp_normals;  out_vertices; index;

	// buffers
	objectVAO = new GLuint; 
	objectVBO = new GLuint; 
	objectEBO = new GLuint;
	// shaders
	shaderProgram = new GLuint; 
	shaderFrag = new GLuint; 
	shaderVertex = new GLuint;


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
	glDeleteVertexArrays(1, &*objectVAO);
	glDeleteBuffers(1, &*objectVBO);
	glDeleteBuffers(1, &*objectEBO);
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
	glUseProgram(*shaderProgram);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, *TextureCube[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, *TextureCube[1]);
}
void Mesh::drawMesh() {
	this->activeTexture();
	glBindVertexArray(*objectVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}
void Mesh::CompileShaderMesh() {
	int succesCompileShaders;
	*shaderVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(*shaderVertex, 1, (const GLchar**)&vertexShaderCODE, NULL);
	glCompileShader(*shaderVertex);
	glGetShaderiv(*shaderVertex, GL_COMPILE_STATUS, &succesCompileShaders);
	if (succesCompileShaders == NULL) {
		MessageBoxA(0, static_cast<const char*>("error compilation shaders"), "ERROR", 0);
		exit(EXIT_FAILURE);
		// l'erreur vient des shader !!!!!!!!
	}

	*shaderFrag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(*shaderFrag, 1, (const GLchar**)&fragmentShaderCODE, NULL);
	glCompileShader(*shaderFrag);
	glGetShaderiv(*shaderFrag, GL_COMPILE_STATUS, &succesCompileShaders);
	if (succesCompileShaders == NULL) {
		MessageBoxA(0, static_cast<const char*>("error compilation shaders"), "ERROR", 0);
		exit(EXIT_FAILURE);
		// l'erreur vient des shader !!!!!!!!
	}

	*shaderProgram = glCreateProgram();
	glAttachShader(*shaderProgram, *shaderVertex);
	glAttachShader(*shaderProgram, *shaderFrag);
	glLinkProgram(*shaderProgram);
}
void Mesh::setTexture1(char* filePath, int NumberTexture) {
	glGenTextures(1, &*TextureCube[NumberTexture]);
	glBindTexture(GL_TEXTURE_2D, *TextureCube[NumberTexture]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChanels;
	stbi_set_flip_vertically_on_load(true);
	
	pathTexture[NumberTexture] = static_cast<const char*>(filePath);
	unsigned char* data = stbi_load(pathTexture[NumberTexture], &width, &height, &nrChanels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		LoaderTextureSUCCESS[NumberTexture] = LOADER_TEXTURE_SUCCESS;
	}
	else {
		LoaderTextureSUCCESS[NumberTexture] = LOADER_TEXTURE_NOT_SUCCESS;
	}
	stbi_image_free(data);
	glUseProgram(*shaderProgram);
	if (NumberTexture == 0) { glUniform1i(glGetAttribLocation(*shaderProgram, "Texture1"), NumberTexture); }
	if (NumberTexture == 1) { glUniform1i(glGetAttribLocation(*shaderProgram, "Texture2"), NumberTexture); }
}
void Mesh::setPercentTexture(float PercentTexture) {
	glUseProgram(*shaderProgram);
	glUniform1f(glGetAttribLocation(*shaderProgram, "PercentTexture"), PercentTexture);
}
void Mesh::setTexture2(char* filePath) {
	glGenTextures(1, &*TextureCube[1]);
	glBindTexture(GL_TEXTURE_2D, *TextureCube[1]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChanels;
	stbi_set_flip_vertically_on_load(true);

	pathTexture[1] = static_cast<const char*>(filePath);
	unsigned char* data = stbi_load(pathTexture[1], &width, &height, &nrChanels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		LoaderTextureSUCCESS[1] = LOADER_TEXTURE_SUCCESS;
	}
	else {
		LoaderTextureSUCCESS[1] = LOADER_TEXTURE_NOT_SUCCESS;
	}
	stbi_image_free(data);
	glUseProgram(*shaderProgram);
	glUniform1i(glGetAttribLocation(*shaderProgram, "Texture2"), 1);
}
void Mesh::setBufferMesh() {
	MotionNinis::VertexArrayObject VAO;
	MotionNinis::VertexBufferObject buffer(Vertecies);
	MotionNinis::ElementArrayBuffer EBO(std::vector<GLfloat>(0));

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
	std::ifstream file(filePath.c_str());
		if (!file) {
			MessageBoxA(0, static_cast<const char*>("FAILED TO LOADING MESH"), "ERROR", 0);
			return false;
		}
		while (1) {

			char lineHeader[128];
			// read the first word of the line
			if (file.tellg() == EOF) {
				break;
			}
			if (strcmp(lineHeader, "v") == 0) {
				glm::vec3 vertex;
				temp_vertices.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0) {
				glm::vec2 uv;
				file >> uv.x;
				file >> uv.y;
				temp_uvs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) {
				glm::vec3 normal;
				file >> normal.x;
				file >> normal.y;
				file >> normal.z;
				temp_normals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) {
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				for (int i(0); i < 3; i++) {
					file >> vertexIndex[i];
					file >> uvIndex[i];
					file >> normalIndex[i];
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

void Mesh::useShaderObject() { glUseProgram(*shaderProgram); }
// getting
std::vector<const char*> Mesh::getPathTexture() { return pathTexture; }
GLuint& Mesh::getShaderObject() { return *shaderProgram; }
GLuint Mesh::getVertexArray() const { return *shaderVertex; }


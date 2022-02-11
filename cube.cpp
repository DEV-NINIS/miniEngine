#include "cube.h"
#include "UserInterface.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stbi_image.h"

float cube::vertecies[] ={

		-0.5f, -0.5f, -0.5f,  0.2f, 0.6f, 0.9f, 0.0f, 0.0f,
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
unsigned int cube::index[] = {
	0, 1, 2
};
cube::cube(GLFWwindow* window)  {

	fragmentShader; vertexShader; programShader;
	// shaders
		// frag
	vertexShaderCODE = "#version 460 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"layout (location = 2) in vec2 texCoords;\n"
		"out vec3 colorForFragmentShader;\n"
		"out vec2 texCoordsForFrag;\n"
		"uniform mat4 view;\n"
		"uniform mat4 model;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 transform;\n"
		"uniform float LastedFrame;\n"
		"uniform mat4 Scale;\n"
		"uniform float PositionX;\n"
		"uniform float PositionY;\n"
		"uniform float PositionZ;\n"

		"void main() {\n"
		"if (PositionX == 0 && PositionY == 0 && PositionZ == 0) {\n"
		"gl_Position = projection * view * model * transform * Scale * vec4(aPos, 1.0f);\n"
		"}\n"
		"else {\n"
		"gl_Position = projection * view * model * transform * Scale * vec4(aPos.x + PositionX/20, aPos.y + PositionY/20, aPos.z + PositionZ/20, 1.0f);\n"
		"}\n"
		"colorForFragmentShader = aColor;\n"
		"texCoordsForFrag = texCoords;\n"
		"}\n\0";

	// vertex
	fragmentShaderCODE = "#version 460 core\n"

		"in vec3 colorForFragmentShader;\n"
		"in vec2 texCoordsForFrag;\n"
		"out vec4 Frag_color;\n"
		"uniform sampler2D Texture1;\n"
		"uniform sampler2D Texture2;\n"
		"uniform sampler2D Texture3;\n"
		"uniform sampler2D Texture4;\n"
		"uniform sampler2D Texture5;\n"
		"uniform float ColorR;\n"
		"uniform float ColorG;\n"
		"uniform float ColorB;\n"

		"void main() {\n"
		"if (ColorR == 0 && ColorG == 0 && ColorB == 0) {"
		"Frag_color = texture(Texture1, texCoordsForFrag) * vec4(colorForFragmentShader, 1.0);\n"
		"}\n"
		"else {\n"
		"Frag_color = mix(texture(Texture2, texCoordsForFrag), texture(Texture1, texCoordsForFrag), 0.5) * vec4(ColorR, ColorG, ColorB, 1.0f);\n"
		"}\n"
		"}\n\0";

	VAOcube; VBOcube; EBOcube;
	TextureCube.push_back(new GLuint);
	LoaderTexture.push_back(new int);
	LoaderTexture.push_back(new int);
	LoaderTexture.push_back(new int);
	LoaderTexture.push_back(new int);
	LoaderTexture.push_back(new int);
	nuberValueTexShader.push_back("Texture1");
	nuberValueTexShader.push_back("Texture2");
	nuberValueTexShader.push_back("Texture3");
	nuberValueTexShader.push_back("Texture4");
	nuberValueTexShader.push_back("Texture5");
	finalPathTexture.push_back(new char);
	finalPathTexture.push_back(new char);
	finalPathTexture.push_back(new char);
	finalPathTexture.push_back(new char);
	finalPathTexture.push_back(new char);
	tex[4];
}
cube::~cube() {
	glDeleteVertexArrays(1, &VAOcube);
	glDeleteBuffers(1, &VBOcube);
	glDeleteBuffers(1, &EBOcube);
}

void cube::setBuffer() {
	// vao
	glGenVertexArrays(1, &VAOcube);
	glBindVertexArray(VAOcube);
	//vbo
	glGenBuffers(1, &VBOcube);
	glBindBuffer(GL_ARRAY_BUFFER, VBOcube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), vertecies, GL_DYNAMIC_DRAW);
	// ebo
	glGenBuffers(1, &EBOcube);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOcube);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_DYNAMIC_DRAW);
	//pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // pointer position 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // pointer colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // pointer TexCoords
	glEnableVertexAttribArray(2);
}
void cube::setShader() {
	int succesCompileShaders;
	// fragment shader
	std::cout << fragmentShaderCODE << std::endl;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentShaderCODE, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &succesCompileShaders);
	if (succesCompileShaders == NULL) {
		std::cout << " error: fragment Shader" << std::endl;
	}
	// vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexShaderCODE, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &succesCompileShaders);
	if (succesCompileShaders == NULL) {
		std::cout << "error: vertex shader " << std::endl;
	}
	// program shader 
	programShader = glCreateProgram();
	glAttachShader(programShader, vertexShader);
	glAttachShader(programShader, fragmentShader);
	glLinkProgram(programShader);
	// deleted pointer of GL_COMPILE_STATUS
}
void cube::setParametterTexture(int numberValueVectorPathTexture) {
	if (numberValueVectorPathTexture == 0) { glActiveTexture(GL_TEXTURE0); }
	else if (numberValueVectorPathTexture == 1) { glActiveTexture(GL_TEXTURE1); }
	else if (numberValueVectorPathTexture == 2) { glActiveTexture(GL_TEXTURE2); }
	else if (numberValueVectorPathTexture == 3) { glActiveTexture(GL_TEXTURE3); }
	else if (numberValueVectorPathTexture == 4) { glActiveTexture(GL_TEXTURE4); }
	glBindTexture(GL_TEXTURE_2D, tex[numberValueVectorPathTexture]);
}
void cube::drawElements() {
	glBindVertexArray(VAOcube);
	glDrawArrays(GL_TRIANGLES, 0, 180);
	glBindVertexArray(0);
}
void cube::setTexture(std::vector<char*> filePath, int filepathIndicator, int numberValueVectorPathTexture) {
	glGenTextures(1, &tex[numberValueVectorPathTexture]);
	glBindTexture(GL_TEXTURE_2D, tex[numberValueVectorPathTexture]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChanels;
	unsigned char* data = 0;
	indicatorLoaderValue = 0;
	*LoaderTexture[numberValueVectorPathTexture] = -1;
	finalPathTexture[numberValueVectorPathTexture] = static_cast<const char*>(filePath[numberValueVectorPathTexture]);
	if (*filePath[numberValueVectorPathTexture] == '0') {
		finalPathTexture[numberValueVectorPathTexture] = static_cast<const char*>("img/basicTex.jpg");
	}
	if (filePath[numberValueVectorPathTexture] != nullptr) {
		*LoaderTexture[numberValueVectorPathTexture] = 0;
		data = stbi_load(finalPathTexture[numberValueVectorPathTexture], &width, &height, &nrChanels, 0);
	}
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
	else {
		*LoaderTexture[0] = 1;
		std::cout << " failed to load texture " << std::endl;
	}
		glUseProgram(programShader);
		glUniform1i(glGetUniformLocation(programShader, nuberValueTexShader[0]), 0);
}
void cube::useShaderCube() { glUseProgram(programShader); }
GLuint& cube::getshaderCube() { return programShader; }
std::vector<int*> cube::getLoaderTexture() { return LoaderTexture; }
int cube::getLoaderValueIndicator() { return indicatorLoaderValue; }
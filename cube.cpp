#include "cube.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stbi_image.h"

float cube::vertecies[] ={

		-0.5f, -0.5f, -0.5f,   0.2f, 0.6f, 0.9f, 0.0f, 0.0f,
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
unsigned int cube::index[] = {
	0, 1, 2
};
cube::cube() {

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
		"uniform mat4 Scale2;\n"
		"uniform float scaleX;\n"
		"uniform float scaleY;\n"
		"uniform float scaleZ;\n"

		"void main() {\n"
		"gl_Position = projection * view * model * transform * Scale * vec4(aPos, 1.0f);\n"
		"colorForFragmentShader = aColor;\n"
		"texCoordsForFrag = texCoords;\n"
		"}\n\0";

	// vertex
	fragmentShaderCODE = "#version 460 core\n"

		"in vec3 colorForFragmentShader;\n"
		"in vec2 texCoordsForFrag;\n"
		"out vec4 Frag_color;\n"
		"uniform sampler2D Texture;\n"

		"void main() {\n"
		"Frag_color = texture(Texture, texCoordsForFrag) * vec4(colorForFragmentShader, 1.0);\n"
		"}\n\0";

	VAOcube; VBOcube; EBOcube;
	TextureCube.push_back(new GLuint);
	LoaderTexture = new int;

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), vertecies, GL_STATIC_DRAW);
	// ebo
	glGenBuffers(1, &EBOcube);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOcube);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
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
void cube::drawElements() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glBindVertexArray(VAOcube);
	glDrawArrays(GL_TRIANGLES, 0, 180);
	glBindVertexArray(0);
}
void cube::setTexture(char* filePath, int filepathIndicator) {
	*LoaderTexture = -1;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChanels;
	unsigned char* data;
	if (filepathIndicator > -1) {
		*LoaderTexture = 0;
		data = stbi_load(static_cast<const char*>(filePath), &width, &height, &nrChanels, 0);
	}
	else {
		data = stbi_load("img/basicTex.jpg", &width, &height, &nrChanels, 0);
	}
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
	else { 
		*LoaderTexture = 1;
		std::cout << " failed to load texture " << std::endl; 
	}
	glUseProgram(programShader);
	glUniform1i(glGetUniformLocation(programShader, "Texture"), 0);
}
void cube::useShaderCube() { glUseProgram(programShader); }
GLuint& cube::getshaderCube() { return programShader; }
int cube::getLoaderTexture() { return *LoaderTexture; }
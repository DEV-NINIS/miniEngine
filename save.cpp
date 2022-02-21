#include "file.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <commdlg.h>
#include <fileapi.h>

using namespace writing;

save::save() {
	  fileContent; 
}
save::~save() {}

std::string save::setFilePath(GLFWwindow* window) {
	return std::string();
}
void save::setFileContent(const char* filetexture, float colorObjectR, float ColorObjectG, 
	float ColorObjectB, float ValuePositionObjectX,float ValuePositionObjectY, float ValuePositionObjectZ,
	float ValueTransformX, float ValueTransformY, float ValueTransformZ,float ValueColorFrameR, 
	float ValueColorFrameG, float ValueColorFrameB, float ValueCameraSpeed, float ValueFOV, std::string filepath) 
{
	std::ofstream flux(filepath.c_str()); // set filepath in std::string to char
	// fonction
	flux << filetexture << "  " << colorObjectR << " " << ColorObjectG << " " << ColorObjectB << "  " << ValuePositionObjectX 
	<< " " << ValuePositionObjectY << " " << ValuePositionObjectZ << "  " << ValueTransformX << " " <<
	ValueTransformY << " " << ValueTransformZ << "  " << ValueColorFrameR << " " << ValueColorFrameG <<
	" " << ValueColorFrameB << "  " << ValueCameraSpeed << "  " << ValueFOV << std::endl;
}

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
using namespace reading;

save::save() : read() {
	fileContent; lastedFile;
}
save::~save() {}

std::string save::setFilePath(GLFWwindow* window){
	OPENFILENAMEA ofn;
	CHAR szFile[260] = { 0 };
	CHAR currentDir[256] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)window);
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

	// Sets the default extension by extracting it from the filter
	if (GetSaveFileNameA(&ofn) == TRUE)
		lastedFile = ofn.lpstrFile;
		return ofn.lpstrFile;

	return std::string();
}
void save::setFileContent(const char* filetexture, float colorObjectR, float ColorObjectG, 
	float ColorObjectB, float ValuePositionObjectX,float ValuePositionObjectY, float ValuePositionObjectZ,
	float ValueTransformX, float ValueTransformY, float ValueTransformZ,float ValueColorFrameR, 
	float ValueColorFrameG, float ValueColorFrameB, float ValueCameraSpeed, float ValueFOV, float LastedScaleXFile, 
	float LastedScaleYFile, float LastedScaleZFile, std::string filepath)
{
	std::ofstream flux(filepath.c_str()); // set filepath in std::string to char
	// fonction
	flux << filetexture << " " << colorObjectR << " " << ColorObjectG << " " << ColorObjectB << " " << ValuePositionObjectX 
	<< " " << ValuePositionObjectY << " " << ValuePositionObjectZ << " " << ValueTransformX << " " <<
	ValueTransformY << " " << ValueTransformZ << " " << ValueColorFrameR << " " << ValueColorFrameG <<
	" " << ValueColorFrameB << " " << ValueCameraSpeed << " " << ValueFOV <<  " " << LastedScaleXFile << " "
	 << LastedScaleYFile << " " << LastedScaleZFile << std::endl;
}
std::string save::getLastedFile() { return lastedFile; }
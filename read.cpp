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

using namespace reading;

read::read() {
	 colorObjectFileR = 0;
	 ColorObjectFileG = 0;
	 ColorObjectFileB = 0;
	 ValuePositionObjectFileX = 0;
	 ValuePositionObjectFileY = 0;
	 ValuePositionObjectFileZ = 0;
	 ValueTransformXFile = 0;
	 ValueTransformYFile = 0;
	 ValueTransformZFile = 0;
	 ValueColorFrameRFile = 0;
	 ValueColorFrameGFile = 0;
	 ValueColorFrameBFile = 0;
	 ValueCameraSpeedFile = 0;
	 ValueFOVFile = 0;
	 filetextureFile = 0;
}
read::~read() {}

std::string read::selectPath(GLFWwindow* window) {
	OPENFILENAMEA ofn;
	CHAR File[200] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)window);
	ofn.lpstrFile = File;
	ofn.nMaxFile = sizeof(File);
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	if (GetOpenFileNameA(&ofn) == true) {
		return ofn.lpstrFile;
	}
	return std::string();
}
void read::setValueFile(std::string filepath) {
	std::ifstream flux(filepath.c_str());

}
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
	 filetextureFile;
	 fileContent; NumberMove = 0;
	 LastedScaleXFile = 0; LastedScaleYFile = 0; LastedScaleZFile = 0;
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
void read::MoveInFile(std::ifstream flux) {

}
void read::setValueFile(std::string filepath) {
	std::string* fileTexTemp = nullptr; fileTexTemp = new std::string;
	std::string* colorObjectFileRTemp = nullptr; colorObjectFileRTemp = new std::string;
	std::string* colorObjectFileGTemp = nullptr; colorObjectFileGTemp = new std::string;
	std::string* colorObjectFileBTemp = nullptr; colorObjectFileBTemp = new std::string;
	std::string* ValuePositionObjectFileXTemp = nullptr; ValuePositionObjectFileXTemp = new std::string;
	std::string* ValuePositionObjectFileYTemp = nullptr; ValuePositionObjectFileYTemp = new std::string;
	std::string* ValuePositionObjectFileZTemp = nullptr; ValuePositionObjectFileZTemp = new std::string;
	std::string* ValueTransformObjectTempX = nullptr; ValueTransformObjectTempX = new std::string;
	std::string* ValueTransformObjectTempY = nullptr; ValueTransformObjectTempY = new std::string;
	std::string* ValueTransformObjectTempZ = nullptr; ValueTransformObjectTempZ = new std::string;
	std::string* ValueColorFrameRFileTemp = nullptr; ValueColorFrameRFileTemp = new std::string;
	std::string* ValueColorFrameGFileTemp = nullptr; ValueColorFrameGFileTemp = new std::string;
	std::string* ValueColorFrameBFileTemp = nullptr; ValueColorFrameBFileTemp = new std::string;
	std::string* ValueCameraSpeedFileTemp = nullptr; ValueCameraSpeedFileTemp = new std::string;
	std::string* ValueFOVfileTemp = nullptr; ValueFOVfileTemp = new std::string;
	std::string* LastedScaleXFileTemp = nullptr; LastedScaleXFileTemp = new std::string;
	std::string* LastedScaleYFileTemp = nullptr; LastedScaleYFileTemp = new std::string;
	std::string* LastedScaleZFileTemp = nullptr; LastedScaleZFileTemp = new std::string;


	std::ifstream flux(filepath.c_str()); 
	flux.seekg(0, std::ios::beg);	
	// on se deplace au debut du fichier 

	flux >> *fileTexTemp; filetextureFile = static_cast<const char*>(fileTexTemp->c_str()); // cin in string and convert to const char for file texture
	NumberMove += fileTexTemp->size() + 1;
	flux.seekg(NumberMove, std::ios::beg);

	flux >> *colorObjectFileRTemp; colorObjectFileR = std::stof(*colorObjectFileRTemp);
	NumberMove += colorObjectFileRTemp->size() + 1;
	flux.seekg(NumberMove, std::ios::beg);

	flux >> *colorObjectFileGTemp; ColorObjectFileG = std::stof(*colorObjectFileGTemp);
	NumberMove += colorObjectFileGTemp->size() + 1;
	flux.seekg(NumberMove, std::ios::beg);

	flux >> *colorObjectFileBTemp; ColorObjectFileB = std::stof(*colorObjectFileBTemp);
	NumberMove += colorObjectFileBTemp->size() + 1;
	flux.seekg(NumberMove, std::ios::beg);

	flux >> *ValuePositionObjectFileXTemp; ValuePositionObjectFileX = std::stof(*ValuePositionObjectFileXTemp);
	NumberMove += ValuePositionObjectFileXTemp->size() + 1;
	flux.seekg(NumberMove, std::ios::beg);

	flux >> *ValuePositionObjectFileYTemp; ValuePositionObjectFileY = std::stof(*ValuePositionObjectFileYTemp);
	NumberMove += ValuePositionObjectFileYTemp->size() + 1;
	flux.seekg(NumberMove, std::ios::beg);

	flux >> *ValuePositionObjectFileZTemp; ValuePositionObjectFileZ = std::stof(*ValuePositionObjectFileZTemp);
	NumberMove += ValuePositionObjectFileZTemp->size() + 1;
	flux.seekg(NumberMove, std::ios::beg);

	flux >> *ValueTransformObjectTempX; ValueTransformXFile = std::stof(*ValueTransformObjectTempX);
	NumberMove += ValueTransformObjectTempX->size() + 1;
	flux.seekg(NumberMove, std::ios::beg);

	flux >> *ValueTransformObjectTempY; ValueTransformYFile = std::stof(*ValueTransformObjectTempY);
	NumberMove += ValueTransformObjectTempY->size() + 1;
	flux.seekg(NumberMove, std::ios::beg);

	flux >> *ValueTransformObjectTempZ; ValueTransformZFile = std::stof(*ValueTransformObjectTempZ);
	NumberMove += ValueTransformObjectTempZ->size() + 1;
	flux.seekg(NumberMove, std::ios::beg);

	flux >> *ValueColorFrameRFileTemp; ValueColorFrameRFile = std::stof(*ValueColorFrameRFileTemp);
	NumberMove += ValueColorFrameRFileTemp->size() + 1;
	flux.seekg(NumberMove, std::ios::beg);

	flux >> *ValueColorFrameGFileTemp; ValueColorFrameGFile = std::stof(*ValueColorFrameGFileTemp);
	NumberMove += ValueColorFrameGFileTemp->size() + 1;
	flux.seekg(NumberMove, std::ios::beg);

	flux >> *ValueColorFrameBFileTemp; ValueColorFrameBFile = std::stof(*ValueColorFrameBFileTemp);
	NumberMove += ValueColorFrameBFileTemp->size() + 1;
	flux.seekg(NumberMove, std::ios::beg);

	flux >> *ValueCameraSpeedFileTemp; ValueCameraSpeedFile = std::stof(*ValueCameraSpeedFileTemp);
	NumberMove += ValueCameraSpeedFileTemp->size() + 1;
	flux.seekg(NumberMove, std::ios::beg);

	flux >> *ValueFOVfileTemp; ValueFOVFile = std::stof(*ValueFOVfileTemp);
	NumberMove += ValueFOVfileTemp->size() + 1;
	flux.seekg(NumberMove, std::ios::beg);

	flux >> *LastedScaleXFileTemp; LastedScaleXFile = std::stof(*LastedScaleXFileTemp);
	NumberMove += LastedScaleXFileTemp->size() + 1;
	flux.seekg(NumberMove, std::ios::beg);

	flux >> *LastedScaleYFileTemp; LastedScaleYFile = std::stof(*LastedScaleYFileTemp);
	NumberMove += LastedScaleYFileTemp->size() + 1;
	flux.seekg(NumberMove, std::ios::beg);

	flux >> *LastedScaleZFileTemp; LastedScaleZFile = std::stof(*LastedScaleZFileTemp);
	NumberMove += LastedScaleZFileTemp->size() + 1;
	flux.seekg(NumberMove, std::ios::beg);

	std::cout << filetextureFile << std::endl;
	std::cout << colorObjectFileR << std::endl;
	std::cout << ColorObjectFileG << std::endl;
	std::cout << ColorObjectFileB << std::endl;
	std::cout << ValuePositionObjectFileX << std::endl;
	std::cout << ValuePositionObjectFileY << std::endl;
	std::cout << ValuePositionObjectFileZ << std::endl;
	std::cout << ValueTransformXFile << std::endl;
	std::cout << ValueTransformYFile << std::endl;
	std::cout << ValueTransformZFile << std::endl;
	std::cout << ValueColorFrameRFile << std::endl;
	std::cout << ValueColorFrameGFile << std::endl;
	std::cout << ValueColorFrameBFile << std::endl;
	std::cout << ValueCameraSpeedFile << std::endl;
	std::cout << ValueFOVFile << std::endl;

	delete fileTexTemp; delete colorObjectFileRTemp;
	delete colorObjectFileGTemp; delete colorObjectFileBTemp;
	delete ValuePositionObjectFileXTemp; delete ValuePositionObjectFileYTemp;
	delete ValuePositionObjectFileZTemp; delete ValueColorFrameRFileTemp;
	delete ValueColorFrameGFileTemp; delete ValueColorFrameBFileTemp;
	delete ValueCameraSpeedFileTemp; delete ValueFOVfileTemp;
	delete LastedScaleXFileTemp; delete LastedScaleYFileTemp;
	delete LastedScaleZFileTemp;
	
}
// getting values 
const char* read::getfiletextureFile() const { return filetextureFile; }
float read::getcolorObjectFileR() const { return colorObjectFileR; }
float read::getcolorObjectFileG() const { return ColorObjectFileG; }
float read::getcolorObjectFileB() const { return ColorObjectFileB; }
float read::getValuePositionObjectFileX() const { return ValuePositionObjectFileX; }
float read::getValuePositionObjectFileY() const { return ValuePositionObjectFileY; }
float read::getValuePositionObjectFileZ() const { return ValuePositionObjectFileZ; }
float read::getValueTransformXFile() const { return ValueTransformXFile; }
float read::getValueTransformYFile() const { return ValueTransformYFile; }
float read::getValueTransformZFile() const { return ValueTransformZFile; }
float read::getValueColorFrameRFile() const { return ValueColorFrameRFile; }
float read::getValueColorFrameGFile() const { return ValueColorFrameGFile; }
float read::getValueColorFrameBFile() const { return ValueColorFrameBFile; }
float read::getValueCameraSpeedFile() const { return ValueCameraSpeedFile; }
float read::getValueFOVFile() const { return ValueFOVFile; }
float read::getLastedScaleXFile() const { return LastedScaleXFile; }
float read::getLastedScaleYFile() const { return LastedScaleYFile; }
float read::getLastedScaleZFile() const { return LastedScaleZFile; }
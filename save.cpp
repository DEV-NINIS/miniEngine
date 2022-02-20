#include "file.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace writing;

save::save(char* filePath) : flux(filePath) {
	filePath;  fileContent;
}
save::~save() {}

void save::setFilePath() {
	flux << fileContent << std::endl;
}
void save::setFileContent(const char* filetexture, float colorObjectR, float ColorObjectG, 
	float ColorObjectB, float ValuePositionObjectX,float ValuePositionObjectY, float ValuePositionObjectZ,
	float ValueTransformX, float ValueTransformY, float ValueTransformZ,float ValueColorFrameR, 
	float ValueColorFrameG, float ValueColorFrameB, float ValueCameraSpeed, float ValueFOV) {
	// fonction
}

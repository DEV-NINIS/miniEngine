
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace writing
{
	#ifndef DEF_SAVE
	#define DEF_SAVE

	class save
	{
	public:
		save();
		virtual ~save();
		std::string setFilePath(GLFWwindow* window);
		void setFileContent(const char* filetexture, float colorObjectR, float ColorObjectG, float ColorObjectB, float ValuePositionObjectX,
			float ValuePositionObjectY, float ValuePositionObjectZ, float ValueTransformX, float ValueTransformY, float ValueTransformZ,
			float ValueColorFrameR, float ValueColorFrameG, float ValueColorFrameB, float ValueCameraSpeed, float ValueFOV, std::string filepath);
	protected:
		const char* fileContent;
	};
	#endif 
}
namespace reading
{
	#ifndef DEF_READING
	#define DEF_READING


	class read
	{
	public:
		read();
		~read();
		std::string selectPath(GLFWwindow* window);
		void setValueFile(std::string filePath);
		void MoveInFile(std::ifstream flux);
		const char* getfiletextureFile() const;
		float getcolorObjectFileR() const;
		float getcolorObjectFileG() const;
		float getcolorObjectFileB() const;
		float get
	protected:
		float colorObjectFileR;
		float ColorObjectFileG;
		float ColorObjectFileB;
		float ValuePositionObjectFileX;
		float ValuePositionObjectFileY;
		float ValuePositionObjectFileZ;
		float ValueTransformXFile;
		float ValueTransformYFile;
		float ValueTransformZFile;
		float ValueColorFrameRFile;
		float ValueColorFrameGFile;
		float ValueColorFrameBFile;
		float ValueCameraSpeedFile;
		float ValueFOVFile;
		const char* filetextureFile;
		std::string fileContent;
		float NumberMove;
	};
	#endif 

}




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
		void setFileContent(const char* filetexture, float colorObjectR, float ColorObjectG,
			float ColorObjectB, float ValuePositionObjectX,
			float ValuePositionObjectY, float ValuePositionObjectZ, float ValueTransformX, 
			float ValueTransformY, float ValueTransformZ,
			float ValueColorFrameR, float ValueColorFrameG, float ValueColorFrameB, 
			float ValueCameraSpeed, float ValueFOV, float LastedScaleXFile,
			float LastedScaleYFile, float LastedScaleZFile, std::string filepath);
		std::string getLastedFile();
	protected:
		const char* fileContent;
		std::string lastedFile;
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
		char* unconstchar2(const char* s);
		// getting values
		const char* getfiletextureFile();
		float getcolorObjectFileR() const;
		float getcolorObjectFileG() const;
		float getcolorObjectFileB() const;
		float getLastedScaleXFile() const;
		float getLastedScaleYFile() const;
		float getLastedScaleZFile() const;
		float getValuePositionObjectFileX() const;
		float getValuePositionObjectFileY() const;
		float getValuePositionObjectFileZ() const;
		float getValueTransformXFile() const;
		float getValueTransformYFile() const;
		float getValueTransformZFile() const;
		float getValueColorFrameRFile() const;
		float getValueColorFrameGFile() const;
		float getValueColorFrameBFile() const;
		float getValueCameraSpeedFile() const;
		float getValueFOVFile() const;
		std::string getLastedFilepath();
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
		float LastedScaleXFile;
		float LastedScaleYFile;
		float LastedScaleZFile;
		const char* filetextureFile;
		std::string fileContent;
		float NumberMove;
		std::string fileTexTemp; std::string colorObjectFileRTemp;
		std::string colorObjectFileGTemp; std::string colorObjectFileBTemp;
		std::string ValuePositionObjectFileXTemp; std::string ValuePositionObjectFileYTemp;
		std::string ValuePositionObjectFileZTemp; std::string ValueTransformObjectTempX;
		std::string ValueTransformObjectTempY; std::string ValueTransformObjectTempZ;
		std::string ValueColorFrameRFileTemp; std::string ValueColorFrameGFileTemp;
		std::string ValueColorFrameBFileTemp; std::string ValueCameraSpeedFileTemp;
		std::string ValueFOVfileTemp; std::string LastedScaleXFileTemp;
		std::string LastedScaleYFileTemp; std::string LastedScaleZFileTemp;

		std::string LastedFilepath;
	};
#endif 
}



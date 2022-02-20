
#include <iostream>
#include <fstream>
#include <filesystem>
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
		save(char* filePath);
		virtual ~save();
		void setFilePath();
		void setFileContent(const char* filetexture, float colorObjectR, float ColorObjectG, float ColorObjectB, float ValuePositionObjectX,
			float ValuePositionObjectY, float ValuePositionObjectZ, float ValueTransformX, float ValueTransformY, float ValueTransformZ,
			float ValueColorFrameR, float ValueColorFrameG, float ValueColorFrameB, float ValueCameraSpeed, float ValueFOV);
	protected:
		std::ofstream flux;
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

	protected:

	};
	#endif 

}



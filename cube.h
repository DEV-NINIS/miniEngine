
#ifndef DEF_CUBE
#define DEF_CUBE

#include <iostream>
#include <vector>
#include "UserInterface.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// cube object
class cube
{
public:
	cube(GLFWwindow* window);
	virtual ~cube();
	void setBuffer();
	void setShader();
	void setParametterTexture(int numberValueVectorPathTexture);
	void setTexture(char* filePath, int numberValueVectorPathTexture); // the variable numberValueVectorPathTexture correspponding to vector value : filePath[numberValueVectorPathTexture]
	void useShaderCube();
	void drawElements();
	GLuint& getshaderCube();
	std::vector<int*> getLoaderTexture();
	int getLoaderValueIndicator();
protected:
	static float vertecies[];
	static unsigned int index[];
	std::vector<const char*> nuberValueTexShader;
	const char* fragmentShaderCODE;
	const char* vertexShaderCODE;
	GLuint VAOcube;
	GLuint VBOcube;
	GLuint EBOcube;
	std::vector<GLuint*> TextureCube;
	GLuint fragmentShader;
	GLuint vertexShader;
	GLuint programShader;
	int indicatorLoaderValue;
	unsigned int tex[4];
	std::vector<int*> LoaderTexture;
	std::vector<const char*> finalPathTexture;
};

#endif // !1


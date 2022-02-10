
#ifndef DEF_CUBE
#define DEF_CUBE

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// cube object
class cube
{
public:
	cube();
	virtual ~cube();
	void setBuffer();
	void setShader();
	void setParametterTexture();
	void setTexture(std::vector<char*> filePath, int filepathIndicator);
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
	unsigned int tex;
	std::vector<int*> LoaderTexture;
	std::vector<const char*> finalPathTexture;
};

#endif // !1


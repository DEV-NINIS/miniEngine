
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
	int getLoaderTexture();
	void setBuffer();
	void setShader();
	void setTexture(char* filePath, int filepathIndicator);
	void useShaderCube();
	void drawElements();
	GLuint& getshaderCube();
protected:
	static float vertecies[];
	static unsigned int index[];
	const char* fragmentShaderCODE;
	const char* vertexShaderCODE;
	GLuint VAOcube;
	GLuint VBOcube;
	GLuint EBOcube;
	std::vector<GLuint*> TextureCube;
	GLuint fragmentShader;
	GLuint vertexShader;
	GLuint programShader;
	unsigned int tex;
	int* LoaderTexture = nullptr;
	const char* finalPathTexture;
};

#endif // !1


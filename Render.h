
#include "object.h"
#include <iostream>
#include "object.h"
#include <vector>

#ifndef DEF_RENDER
#define DEF_RENDER
class Render
{

public:
	Render(GLFWwindow* window);
	virtual ~Render();
	virtual void drawElements(objectUser::Mesh mesh , int& numberAssets);
private:
	basicObject::cube* Cube;
};
#endif 



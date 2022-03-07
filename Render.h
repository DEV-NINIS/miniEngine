
#include "object.h"
#include <iostream>
#include <vector>

#ifndef DEF_RENDER
#define DEF_RENDER
class Render: public objectUser::Mesh
{

public:
	Render(GLFWwindow* window);
	virtual ~Render();
	void drawElements();
private:

};
#endif 



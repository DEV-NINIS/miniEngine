


#include <iostream>
#include <vector>
#include "UserInterface.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// cube object

namespace basicObject {
#ifndef DEF_CUBE
#define DEF_CUBE
	class cube {
	public:
		cube(GLFWwindow* window);
		virtual ~cube();
		void setBuffer();
		void setShader();
		void setParametterTexture();
		void setTexture1(char* filePath); // the variable numberValueVectorPathTexture correspponding to vector value : filePath[numberValueVectorPathTexture]
		void setTexture2(char* filePath); // the variable numberValueVectorPathTexture correspponding to vector value : filePath[numberValueVectorPathTexture]
		void useShaderCube();
		GLuint getVertexArray() const;
		GLuint& getshaderCube();
		std::vector<int*> getLoaderTexture();
		int getLoaderValueIndicator();

		// get Value for save
		std::vector<const char*> getfinalPathTexture();

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
}
namespace objectUser {
#ifndef DEF_MESH
#define DEF_MESH
	class Mesh: public basicObject::cube{
		public:
			Mesh(GLFWwindow* window);
			virtual ~Mesh();
	    private:

	};
#endif
}



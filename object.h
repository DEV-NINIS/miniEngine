


#include <iostream>
#include <vector>
#include <string>
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
		void drawThisObject();
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
	class Mesh {
		public:
			Mesh(GLFWwindow* window);
			void CompileShaderMesh();
			void setBufferMesh();
			float variableSize1(float variable);
			void setTexture1(char* filePath);
			void setTexture2(char* filePath);
			void drawMesh();
			unsigned int variableSize(unsigned int variable);

			void OpenShader(std::string filePathVertex, std::string filePathFragment);
			virtual ~Mesh();
	    private:
			const char* fragmentShaderCODE;
			const char* vertexShaderCODE;
			static float verteciesObject[];
			static unsigned int indexObject[];
			GLuint objectVAO;
			GLuint objectVBO;
			GLuint objectEBO;
			GLuint shaderProgram;
			GLuint shaderFrag;
			GLuint shaderVertex;
			GLuint texture1;
			GLuint texture2;
			std::vector<int> LoaderTextureSUCCESS;
	};
#endif
}



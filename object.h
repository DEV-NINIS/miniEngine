


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
			virtual ~Mesh();
			void CompileShaderMesh();
			void setBufferMesh();
			float variableSize1(float variable);
			void setTexture1(char* filePath);
			void setTexture2(char* filePath);
			void drawMesh();
			void activeTexture();
			unsigned int variableSize(unsigned int variable);
			void useShaderObject();
			GLuint& getShaderObject();
			GLuint getVertexArray() const;
			std::vector<const char*> getPathTexture();
			void OpenShader(std::string filePathVertex, std::string filePathFragment);
			bool OpenMeshObjFile(std::string filePath);
	    protected:
			const char* fragmentShaderCODE;
			const char* vertexShaderCODE;
			static std::vector<unsigned int> indexObject;
			static std::vector<float> verteciesObject;
			static std::vector<unsigned int> normalIndices;
			std::vector<glm::vec3> temp_vertices;
			std::vector<glm::vec2> temp_uvs;
			std::vector<glm::vec3> temp_normals;
			std::vector<glm::vec3> out_vertices;
			GLuint objectVAO;
			GLuint objectVBO;
			GLuint objectEBO;
			GLuint shaderProgram;
			GLuint shaderFrag;
			GLuint shaderVertex;
			GLuint texture1 = 0;
			GLuint texture2 = 0;
			std::vector<int> LoaderTextureSUCCESS;
			std::vector<const char*> pathTexture;
	};
#endif
}



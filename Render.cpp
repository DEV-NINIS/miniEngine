#include "Render.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Render::Render(GLFWwindow* window)  : Mesh(window) {
	std::cout << fragmentShaderCODE << std::endl;
}
Render::~Render() {

}
void Render::drawElements() {
	glBindVertexArray(VAOcube);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

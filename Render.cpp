#include "Render.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "object.h"

Render::Render(GLFWwindow* window)   {

}
Render::~Render() {

}
void Render::drawElements(objectUser::Mesh mesh, int& numberAssets) {
		mesh.activeTexture();
		mesh.drawMesh(); // in this fonction they are the actives textures
}

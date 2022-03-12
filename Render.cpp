#include "Render.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "object.h"
#include "imgui/imgui_impl_opengl3.h"

Render::Render(GLFWwindow* window)   {

}
Render::~Render() {

}
void Render::drawElements(objectUser::Mesh mesh, int& numberAssets) {
	mesh.drawMesh();
}

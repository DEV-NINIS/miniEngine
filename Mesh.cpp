#include "object.h"
#include "UserInterface.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stbi_image.h"

using namespace objectUser;

Mesh::Mesh(GLFWwindow* window) : cube(window) {

}
Mesh::~Mesh() {

}


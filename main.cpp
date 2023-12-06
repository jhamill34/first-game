#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include <iostream>

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		std::cout << "Escape key pressed" << std::endl;
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL((GLADloadfunc) glfwGetProcAddress);

	glClearColor(0.4f, 0.3f, 0.4f, 0.0f);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

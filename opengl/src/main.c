#include <stdio.h>
#include <GLFW/glfw3.h>

void window_size_calllback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(void)
{
	glfwInit();

	// OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "Hello, world!", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open a window!\n");
		goto _failure;
	}

	glfwMakeContextCurrent(window);
	glViewport(0, 0, 800, 600); // tell OpenGL the size of the window
	glfwSetFramebufferSizeCallback(window, window_size_calllback);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.1f, 1.0f);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

_failure:
	glfwTerminate();
	return 1;
}

#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

void window_size_calllback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

char *read_file(const char *path)
{
	FILE *fp = fopen(path, "r");
	if (fp == NULL)
		return NULL;

	fseek(fp, 0l, SEEK_END);
	long len = ftell(fp);
	char *buffer = calloc(len + 1, sizeof(char));
	rewind(fp);
	fread(buffer, sizeof(char), len, fp);
	buffer[len] = '\0';

	printf("%s\n", buffer);
	return buffer;
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

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	};
	
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	char *vert_src = read_file("shaders/vertex.glsl");
	if (vert_src == NULL)
		goto _failure;
	unsigned int vert_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert_shader, 1, &vert_src, NULL);
	glCompileShader(vert_shader);

	char *frag_src = read_file("shaders/fragment.glsl");
	if (frag_src == NULL) {
		free(vert_src);
		goto _failure;
	}

	unsigned int frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag_shader, 1, &frag_src, NULL);
	glCompileShader(frag_shader);

	unsigned int shader_prog = glCreateProgram();
	glAttachShader(shader_prog, vert_shader);
	glAttachShader(shader_prog, frag_shader);
	glLinkProgram(shader_prog);
	glUseProgram(shader_prog);

	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader_prog);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate();
	return 0;

_failure:
	glfwTerminate();
	return 1;
}

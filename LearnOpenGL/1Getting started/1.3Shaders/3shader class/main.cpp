// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include "shader.h"

const GLuint WIDTH = 800, HEIGHT = 600;

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);      // opengl���汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);      // opengl���汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);     // ����Ϊ����ģʽ
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);           // ���ܵ������ڴ�С

	GLFWwindow * window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	glewExperimental = GL_TRUE;          // ����ΪGL_TRUE��Ϊ�˸��õ�ʹ�ú���ģʽ
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);   // ��Ⱦ���ڴ�С
	glViewport(0, 0, width, height);

	Shader ourShader("C://Users/lenovo/Desktop/LearnOpenGL/default_vs.txt", "C://Users/lenovo/Desktop/LearnOpenGL/default_frag.txt");

	GLfloat vertices[] = {
		// λ��              // ��ɫ
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
	};

	GLuint VBO, VAO;
	glGenBuffers(1, &VBO);       // ����һ��VBO����
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);     // ��VBO�󶨵�GL_ARRAY_BUFFER
	glBindVertexArray(VAO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // �Ѷ������ݸ��Ƶ�������ڴ���

	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid *)0);   // ������������
	glEnableVertexAttribArray(0);           // ���ö�������
	// ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid *)(3 * sizeof(GLfloat)));   // ������������
	glEnableVertexAttribArray(1);           // ������ɫ����

	glBindBuffer(GL_ARRAY_BUFFER, 0);  // ���԰�ȫ��󣬶���glVertexAttribPointer�󶨵�VBO����

	glBindVertexArray(0);  // ���VAO

	while (!glfwWindowShouldClose(window)) {   // ���GLFW�Ƿ�Ҫ���˳�
		glfwPollEvents();                      // ����Ƿ񴥷��¼��������ûص�����

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.Use();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		
		glfwSwapBuffers(window);               // ��ɫ˫����
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_TRUE) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}
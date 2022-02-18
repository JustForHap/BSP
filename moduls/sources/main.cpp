// Подключение библиотек
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Подключение заголовков
#include "shaders/shaders.h"
#include "buffer_objects/buffer_objects.h"

// Параметры графического окна
#define WINDOW_WIDTH 450
#define WINDOW_HEIGHT 450

// Прототипы функций обратного вызова для GLFW
void sizeCallback(GLFWwindow* window, int width, int height);

// Общий обработчик событий клавиатуры
void processKeyboardEvents(GLFWwindow* window);

// Используемые имена
using namespace std;

// Главная функция
int main()
{
	// Установка русской локализации
	setlocale(LC_ALL, "Ru");

	// Инициализация GLFW
	if (!glfwInit())
		return -1;

	// Установка стандарта OpenGL 3.3 Core Profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Создание объекта окна
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "GRAPHICS WINDOW", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Установка контекста окна основным для OpenGL
	glfwMakeContextCurrent(window);

	// Инициализация GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		return -1;
	}

	// Ограничения видимой области
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(window, sizeCallback);

	// Загрузка шейдеров для цветных вершин
	vertex_shader colorVertexShader;
	string path = COLOR_SHADER_PATH + (string)"vertex_shader.glsl";
	loadShader(path.c_str(), &colorVertexShader);
	fragment_shader colorFragmentShader;
	path = COLOR_SHADER_PATH + (string)"fragment_shader.glsl";
	loadShader(path.c_str(), &colorFragmentShader);

	// Создание шейдерной программы для цветных вершин
	shader_program shaderProgram(colorVertexShader, colorFragmentShader);

	//Используемая шейдерная программа
	shaderProgram.use();

	/////////////////////////////////////////////////////////////////////////////////////////////////

	GLfloat coords[9] = {
		-0.5f, -0.3f, 0.0f,
		0.5f, -0.3f, 0.0f,
		0.0f, 0.7f, 0.0f
	};

	GLfloat colors[9] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	GLuint indexes[3] = { 0, 1, 2 };

	vbo coordsVBO(coords, 9, 3);
	vbo colorsVBO(colors, 9, 3);
	vao VAO;
	VAO.addVBO(coordsVBO);
	VAO.addVBO(colorsVBO);
	ebo EBO(VAO, indexes, 3);

	/////////////////////////////////////////////////////////////////////////////////////////////////

	// Цикл рендеринга
	while (!glfwWindowShouldClose(window))
	{
		processKeyboardEvents(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		EBO.draw(GL_TRIANGLES);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Очистка ресурсов GLFW
	glfwTerminate();
	return 0;
}

// Обработчик событий клавиатуры
void processKeyboardEvents(GLFWwindow* window)
{
	// Закрытие графического окна по нажатию ESCAPE
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// Функции обратного вызова
void sizeCallback(GLFWwindow* window, int width, int height)
{
	// Изменение размеров видиомй области
	// при изменении параметров окна пользователем
	glViewport(0, 0, width, height);
}
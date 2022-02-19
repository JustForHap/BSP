// Подключение библиотек
#include <glad/glad.h>
#include <iostream>
#include "buffer_objects.h"

// Конструктор вершинного буфера
vbo::vbo(GLfloat* buffer, unsigned int size, unsigned int step)
{
	this->step = step;
	this->amount = size / step;

	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), buffer, GL_STATIC_DRAW);
}

// Определение текущим вершинный буфер
void vbo::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Получение ID вершинного буфера
GLuint vbo::getID()
{
	return ID;
}

// Получение шага вершинного буфера
int vbo::getStep()
{
	return step;
}

// Получение размера вершинного буфера
int vbo::account()
{
	return amount;
}

// Деструктор вершинного буфера
vbo::~vbo()
{
	glDeleteBuffers(1, &ID);
}

// Конструктор вершинного массива
vao::vao()
{
	countVBO = 0;
	amount = 0;
	glGenVertexArrays(1, &ID);
}

// Определение текущим вершинного массива
void vao::bind()
{
	glBindVertexArray(ID);
}

// Добавление вершинного буфера
void vao::addVBO(vbo& buffer)
{
	if (amount == buffer.account() || amount == 0)
	{
		unsigned int step = buffer.getStep();
		amount = buffer.account();

		glBindVertexArray(ID);
		glEnableVertexAttribArray(countVBO);
		buffer.bind();
		glVertexAttribPointer(countVBO, amount, GL_FLOAT, GL_FALSE, step * sizeof(float), (void*)0);

		countVBO++;
	}
}

// Отрисовка вершинного массива
void vao::draw(GLenum mode)
{
	glBindVertexArray(ID);
	glDrawArrays(mode, 0, amount);
}

// Получение ID вершинного массива
GLuint vao::getID()
{
	return ID;
}

// Деструктор вершинного массива
vao::~vao()
{
	glDeleteVertexArrays(1, &ID);
}

// Конструктор элементного буфера
ebo::ebo(vao& arr, GLuint* indexes, unsigned int size)
{
	this->arr = arr;
	this->size = size;

	arr.bind();
	
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(int), indexes, GL_STATIC_DRAW);
}

// Определение текущим элементного буфера
void ebo::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Отрисовка элементного буфера
void ebo::draw(GLenum mode)
{
	arr.bind();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glDrawElements(mode, size, GL_UNSIGNED_INT, 0);
}

// Получение ID элементного буфера
GLuint ebo::getID()
{
	return ID;
}

// Деструктор элементного буфера
ebo::~ebo()
{
	glDeleteBuffers(1, &ID);
}

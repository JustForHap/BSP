// ����������� ���������
#include <glad/glad.h>
#include <iostream>
#include "buffer_objects.h"

// ����������� ���������� ������
vbo::vbo(GLfloat* buffer, unsigned int size, unsigned int step)
{
	this->step = step;
	this->amount = size / step;

	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), buffer, GL_STATIC_DRAW);
}

// ����������� ������� ��������� �����
void vbo::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// ��������� ID ���������� ������
GLuint vbo::getID()
{
	return ID;
}

// ��������� ���� ���������� ������
int vbo::getStep()
{
	return step;
}

// ��������� ������� ���������� ������
int vbo::account()
{
	return amount;
}

// ���������� ���������� ������
vbo::~vbo()
{
	glDeleteBuffers(1, &ID);
}

// ����������� ���������� �������
vao::vao()
{
	countVBO = 0;
	amount = 0;
	glGenVertexArrays(1, &ID);
}

// ����������� ������� ���������� �������
void vao::bind()
{
	glBindVertexArray(ID);
}

// ���������� ���������� ������
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

// ��������� ���������� �������
void vao::draw(GLenum mode)
{
	glBindVertexArray(ID);
	glDrawArrays(mode, 0, amount);
}

// ��������� ID ���������� �������
GLuint vao::getID()
{
	return ID;
}

// ���������� ���������� �������
vao::~vao()
{
	glDeleteVertexArrays(1, &ID);
}

// ����������� ����������� ������
ebo::ebo(vao& arr, GLuint* indexes, unsigned int size)
{
	this->arr = arr;
	this->size = size;

	arr.bind();
	
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(int), indexes, GL_STATIC_DRAW);
}

// ����������� ������� ����������� ������
void ebo::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// ��������� ����������� ������
void ebo::draw(GLenum mode)
{
	arr.bind();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glDrawElements(mode, size, GL_UNSIGNED_INT, 0);
}

// ��������� ID ����������� ������
GLuint ebo::getID()
{
	return ID;
}

// ���������� ����������� ������
ebo::~ebo()
{
	glDeleteBuffers(1, &ID);
}

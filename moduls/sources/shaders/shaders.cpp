// Подключение библиотек
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <string>

// Используемые имена
using namespace std;

// Подключение заголовочных файлов
#include "shaders.h"

// Загрузка шейдеров
void loadShader(const char* path, shader* sh)
{
	ifstream file;
	string current;

	cout << path;

	const char* source;

	try
	{
		file.open(path);
		if (!file.is_open())
			throw - 1;

		current = "";
		while (!file.eof())
		{
			current += file.get();
		}
		source = current.c_str();

		sh->changeShader(source);
	}
	catch (int e)
	{
		if (e == -1)
		{
			cout << "ERROR. FILE NOT OPEN" << endl;
		}
	}
}

// Конструктор шейдера по умолчанию
shader::shader()
{
	ID = 0;
	compileState = false;
	source = "";
}

// Конструктор шейдера
shader::shader(const char* source)
{
	ID = 0;
	compileState = false;
	this->source = source;
}

// Проверка компиляции шейдера
bool shader::checkCompile()
{
	return compileState;
}

// Получение ID шейдера
GLuint shader::getID()
{
	return ID;
}

// Изменение шейдера
void shader::changeShader(const char* source)
{
	this->source = source;
	compile();
}

// Компиляция вершинного шейдера
void vertex_shader::compile()
{
	GLint succes;
	char infoLog[512];

	ID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(ID, 1, &source, NULL);
	glCompileShader(ID);

	glGetShaderiv(ID, GL_COMPILE_STATUS, &succes);
	if (!succes)
	{
		glGetShaderInfoLog(ID, 512, NULL, infoLog);
		cout << "ERROR VERTEX SHADER COMPILE\n" << infoLog << endl;
		compileState = false;
	}
	else 
	{
		compileState = true;
	}
}

// Деструктор вершинного шейдера
vertex_shader::~vertex_shader()
{
	glDeleteShader(ID);
}

// Компиляция фрагментного шейдера
void fragment_shader::compile()
{
	GLint succes;
	char infoLog[512];

	ID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(ID, 1, &source, NULL);
	glCompileShader(ID);

	glGetShaderiv(ID, GL_COMPILE_STATUS, &succes);
	if (!succes)
	{
		glGetShaderInfoLog(ID, 512, NULL, infoLog);
		cout << "ERROR FRAGMENT SHADER COMPILE\n" << infoLog << endl;
		compileState = false;
	}
	else
	{
		compileState = true;
	}
}

// Деструктор фрагментного шейдера
fragment_shader::~fragment_shader()
{
	glDeleteShader(ID);
}

// Конструктор шейдерной программы
shader_program::shader_program(vertex_shader& vs, fragment_shader& fs)
{
	GLuint vsID = vs.getID();
	GLuint fsID = fs.getID();

	ID = glCreateProgram();

	glAttachShader(ID, vsID);
	glAttachShader(ID, fsID);
	glLinkProgram(ID);

	GLint succes;
	char infoLog[512];

	glGetProgramiv(ID, GL_LINK_STATUS, &succes);
	if (!succes) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		cout << "ERROR SHADER PROGRAM LINK\n" << infoLog << endl;
		compileState = false;
	}
	else
	{
		compileState = true;
	}
}

// Проверка компиляции шейдерной программы
bool shader_program::checkCompile()
{
	return compileState;
}

// Включение шейдерной программы
void shader_program::use()
{
	glUseProgram(ID);
}

// Получение ID шейдерной программы
GLuint shader_program::getID()
{
	return ID;
}

// Деструктор шейдерной программы
shader_program::~shader_program()
{
	glDeleteProgram(ID);
}

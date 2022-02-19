// Защита от повторного включения
#pragma once

// Шейдеры
#define COLOR_SHADER_PATH "shaders/color_shaders/"

// Объявление абстрактного шейдера
class shader
{
protected:
	const char* source;
	GLuint ID;
	bool compileState;
public:
	shader();
	shader(const char* source);
	virtual void compile() = 0;
	bool checkCompile();
	GLuint getID();
	void changeShader(const char* source);
};

// Загрузка шейдеров
void loadShader(const char* path, shader* shader);

// Объявление вершинного шейдера
class vertex_shader : public shader
{
public:
	void compile();
	~vertex_shader();
};

// Объявление фрагментного шейдера
class fragment_shader : public shader
{
public:
	void compile();
	~fragment_shader();
};

// Объявление шейдерной программы
class shader_program
{
private:
	GLuint ID;
	bool compileState;
public:
	shader_program(vertex_shader& vs, fragment_shader& fs);
	bool checkCompile();
	void use();
	GLuint getID();
	~shader_program();
};
// ������ �� ���������� ���������
#pragma once

// �������
#define COLOR_SHADER_PATH "shaders/color_shaders/"

// ���������� ������������ �������
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

// �������� ��������
void loadShader(const char* path, shader* shader);

// ���������� ���������� �������
class vertex_shader : public shader
{
public:
	void compile();
	~vertex_shader();
};

// ���������� ������������ �������
class fragment_shader : public shader
{
public:
	void compile();
	~fragment_shader();
};

// ���������� ��������� ���������
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
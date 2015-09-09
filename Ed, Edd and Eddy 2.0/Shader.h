#pragma once


class CShader
{
public:
	CShader();
	~CShader();
	
	GLuint GetShadingProgram(void);
	void CreateShadingProgram(char[], char[]);

private:
	GLuint shadingProgramId;
	GLuint CreateShader(GLenum, char[]);
};


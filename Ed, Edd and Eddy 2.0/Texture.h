#pragma once

class CTexture
{
public:
	bool IsLoaded;

	CTexture(char *);
	CTexture(char *, int, int);
	~CTexture(void);
	bool Load(void);
	GLuint GetID(void);
	int GetWidth(void);
	int GetHeight(void);
protected:
	int _magFilter;
	int _minFilter;
	char * _file;
	GLuint _id;
	int width, height;
};


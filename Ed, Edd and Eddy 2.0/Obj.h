#pragma once
// Loader for .obj files

class CObj
{
public:	
	CObj();
	CObj(char *);
	~CObj();
	bool Load(void);
	GLuint GetDisplayListId(void);

private:
	char * _file;
	bool IsLoaded;
	GLuint _displayListId;
};


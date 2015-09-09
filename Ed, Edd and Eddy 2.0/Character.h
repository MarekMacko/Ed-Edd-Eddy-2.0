#pragma once

class CCharacter : public CSceneObject, public CObj
{
public:
	CCharacter(void);
	~CCharacter(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void LoadFiles(char *, char *);

private:
	GLuint _displayListId;
	CObj * obj;
	CTexture * _characterTexture;
	char * _fileTexture;
	char * _fileObj;
};


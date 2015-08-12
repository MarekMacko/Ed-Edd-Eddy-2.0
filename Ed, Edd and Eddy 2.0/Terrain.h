#pragma once

class CTerrain : public CSceneObject
{
public:
	CTerrain();
	~CTerrain();
	void Initialize(void);
	void Update(void);
	void Render(void);
	
protected:
	GLuint _displayListId;
	CTexture * _grassTexture;
};



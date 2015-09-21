#pragma once
#include "MD2Struct.h"

class CMD2Model
{
public:
	CMD2Model();
	~CMD2Model();

	int Load(char *modelFile, char *skinFile);	// ³aduje model i jego teksturê
	int LoadModel(char *modelFile); // ³aduje tylko model
	int LoadSkin(char *skinFile); // ³aduje tylko teksturê
	int SetTexture(texture_t *texture); // okreœla teksturê modelu
	int Animate(int startFrame, int endFrame, float percent); // animuje model metoda interpoacji klatek kluczowych
	int RenderFrame(int keyFrame); // wyœwietla wybran¹ klatkê modelu
	int Unload(); // zwalnia pamiêæ wykorzystywan¹ przez model
	void SetState(modelState_t state);
	modelState_t GetState(void);

private:
	void SetupSkin(texture_t *thisTexture);
	void CalculateNormal(vec3 *p1, vec3 *p2, vec3 *p3);

	int numFrames;			// liczba klatek animacji
	int numVertices;		// liczba wierzcho³ków modelu
	int numTriangles;		// liczba trójk¹tów modelu
	int numST;				// liczba tekstur modelu
	int frameSize;			// rozmiar klatki w bajtach
	int currentFrame;		// bie¿¹ca klatka animacji
	int nextFrame;			// kolenka klatka animacji
	float interpol;			// wspó³czynnik interpolacji
	mesh_t *triIndex;		// lista trójk¹tów
	texCoord_t *st;			// lista wspó³rzêdnych tekstury
	vec3 *vertexList;		// lista wierzcho³ków
	texture_t *modelTex;	// dane tekstury
	CTexture * tex;
	modelState_t modelState;
	static anim_t animlist[21];	// lista animacji
};



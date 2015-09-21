#pragma once
#include "MD2Struct.h"

class CMD2Model
{
public:
	CMD2Model();
	~CMD2Model();

	int Load(char *modelFile, char *skinFile);	// �aduje model i jego tekstur�
	int LoadModel(char *modelFile); // �aduje tylko model
	int LoadSkin(char *skinFile); // �aduje tylko tekstur�
	int SetTexture(texture_t *texture); // okre�la tekstur� modelu
	int Animate(int startFrame, int endFrame, float percent); // animuje model metoda interpoacji klatek kluczowych
	int RenderFrame(int keyFrame); // wy�wietla wybran� klatk� modelu
	int Unload(); // zwalnia pami�� wykorzystywan� przez model
	void SetState(modelState_t state);
	modelState_t GetState(void);

private:
	void SetupSkin(texture_t *thisTexture);
	void CalculateNormal(vec3 *p1, vec3 *p2, vec3 *p3);

	int numFrames;			// liczba klatek animacji
	int numVertices;		// liczba wierzcho�k�w modelu
	int numTriangles;		// liczba tr�jk�t�w modelu
	int numST;				// liczba tekstur modelu
	int frameSize;			// rozmiar klatki w bajtach
	int currentFrame;		// bie��ca klatka animacji
	int nextFrame;			// kolenka klatka animacji
	float interpol;			// wsp�czynnik interpolacji
	mesh_t *triIndex;		// lista tr�jk�t�w
	texCoord_t *st;			// lista wsp�rz�dnych tekstury
	vec3 *vertexList;		// lista wierzcho�k�w
	texture_t *modelTex;	// dane tekstury
	CTexture * tex;
	modelState_t modelState;
	static anim_t animlist[21];	// lista animacji
};



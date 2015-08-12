#include "stdafx.h"

CScene::CScene(void)
{

}

CScene::~CScene(void)
{

}

void CScene::Initialize(void) {

#pragma region Ustawienia
		
	glEnable(GL_LIGHT0);

#pragma endregion

#pragma region Zawartoœæ sceny

	Terrain = new CTerrain();
	Terrain->Initialize();

#pragma endregion
}

void CScene::Update(void) {

}

void CScene::Render(void) {

#pragma region Kamera

	gluLookAt(
		Player.pos.x + Player.cam.x, Player.pos.y + Player.cam.y, Player.pos.z + Player.cam.z,
		Player.pos.x + Player.cam.x + Player.dir.x, Player.pos.y + Player.cam.y + Player.dir.y, Player.pos.z + Player.cam.z + Player.dir.z,
		0.0f, 1.0f, 0.0f
	);

#pragma endregion

#pragma region Œwiat³o

	float l0_amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float l0_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float l0_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float l0_pos[] = {-1.0f, 0.2f, 0.5f, 0.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
	glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);

#pragma endregion

#pragma region Obiekty

	static double frame = 0;

	// Rysowanie obiektow na scenie.
	frame += 0.5;
	// Porostopad³oœcian
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 2.5f, -6.0f);
	glScalef(4.0f, 0.5f, 0.5f);
	glRotatef((GLfloat)frame, 0.0f, 1.0f, 0.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	Terrain->Render();

#pragma endregion

}
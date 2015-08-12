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

#pragma region Ruch kamery

	// Zmiana predkosci gracza jesli wcisniete W/S/A/D
	if (keystate['w']) {
		Player.velM = Player.speed;
	}
	if (keystate['s']) {
		Player.velM = -Player.speed;
	}
	if (keystate['a']) {
		Player.velS = -Player.speed;
	}
	if (keystate['d']) {
		Player.velS = Player.speed;
	}

	// Obrot kamery
	float phi = atan2(Player.dir.z, Player.dir.x);
	if (keystate['q']) {
		phi -= 0.02f * Player.speed;
	}
	if (keystate['e']) {
		phi += 0.02f * Player.speed;
	}

	Player.dir.x = cos(phi);
	Player.dir.z = sin(phi);

	// Znalezienie kierunku prostopad³ego
	vec3 per;
	per.x = -Player.dir.z;
	per.y = 0;
	per.z = Player.dir.x;

	// Chodzenie przód/ty³
	Player.pos.x += Player.dir.x * Player.velM * .1f;
	Player.pos.y += Player.dir.y * Player.velM * .1f;
	Player.pos.z += Player.dir.z * Player.velM * .1f;

	// Chodzenie na boki
	Player.pos.x += per.x * Player.velS * .1f;
	Player.pos.z += per.z * Player.velS * .1f;

	// Bezw³adnoœæ - w ka¿dym cyklu maleje prêdkoœæ gracza
	Player.velM /= 1.2;
	Player.velS /= 1.2;

#pragma endregion
	//system("cls");
	cout << Player.pos.x << endl <<
			Player.pos.y << endl <<
			Player.pos.z << endl;
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
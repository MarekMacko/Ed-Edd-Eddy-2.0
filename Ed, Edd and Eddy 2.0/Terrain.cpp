#include "stdafx.h"

CTerrain::CTerrain(void) : CSceneObject()
{
}

CTerrain::~CTerrain(void)
{
}

void CTerrain::Initialize(void)
{
	_grassTexture = new CTexture("Resources\\grass.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	_grassTexture->Load();
	
	_displayListId = glGenLists(1);

	float size = 100.0f;

	glNewList(_displayListId, GL_COMPILE);
		glBegin(GL_QUADS);
			
			glTexCoord2f(size, 0.0f);
			glVertex3f(size, 0.0f, -size);

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-size, 0.0f, -size);

			glTexCoord2f(0.0f, size);
			glVertex3f(-size, 0.0f, size);

			glTexCoord2f(size, size);
			glVertex3f(size, 0.0f, size);

		glEnd();
	glEndList();
}

void CTerrain::Update(void)
{
}

void CTerrain::Render(void)
{
	if (!_grassTexture->IsLoaded)
		return;

	glPushMatrix();

	glTranslatef(Position.x, Position.y, Position.z);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _grassTexture->GetId());
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glCallList(_displayListId);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

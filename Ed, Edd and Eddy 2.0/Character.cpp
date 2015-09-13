#include "stdafx.h"

CCharacter::CCharacter(void) : CSceneObject()
{
	//_displayListId = NULL;
}

CCharacter::~CCharacter(void)
{
}

void CCharacter::Initialize(void)
{
	Scale.Set(0.01f);
	Position.z = -1.0f;
	if (_fileObj) {
		obj = new CObj(_fileObj);
		if (obj->Load()) {
			_displayListId = obj->GetDisplayListId();
		}		
	}
	if (_fileTexture) {
		_characterTexture = new CTexture(_fileTexture, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
		if (!_characterTexture->Load()) {
			_characterTexture = NULL;
		}
	}
}

void CCharacter::Update(void)
{
}

void CCharacter::Render(void)
{	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _characterTexture->GetId());
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	glTranslatef(Position.x, Position.y, Position.z);
	glScalef(Scale.x, Scale.z, Scale.z);
	glCallList(_displayListId);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void CCharacter::LoadFiles(char * fileObj, char * fileTexture)
{
	_fileObj = fileObj;
	_fileTexture = fileTexture;
}



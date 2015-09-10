#include "stdafx.h"

CSceneObject::CSceneObject(void)
{
	Position.Set(0.0f, 0.0f, 0.0f);
	Scale.Set(1.0f, 1.0f, 1.0f);
	Name = new char[32];
	strcpy_s(Name, 32, "(unnamed object)");
}

CSceneObject::~CSceneObject(void)
{
	delete[] Name;
}


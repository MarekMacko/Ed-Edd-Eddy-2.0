// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

using namespace std;

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <GL\glut.h>


#include "Vec3.h"
#include "Bitmap.h"
#include "Texture.h"
#include "Shader.h"
#include "Obj.h"
#include "MD2Model.h"

#include "Ed, Edd and Eddy 2.0.h"

#include "SceneObject.h"
#include "Terrain.h"
#include "Character.h"
#include "Player.h"
#include "Scene.h"

#pragma region Zmienne globalne

	extern bool keystate[256];
	extern bool keystate_special[256];

#pragma endregion
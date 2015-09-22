#include "stdafx.h"

CTimer * CTimer::singleton = 0;

CTimer * CTimer::GetInstance(void) {
	if (singleton == 0) {
		singleton = new CTimer;
	}
	return singleton;
}

unsigned long CTimer::GetTimeMSec(void) {
	return glutGet(GLUT_ELAPSED_TIME);
}

unsigned long CTimer::GetTime(void) { 
	return currentTime; 
}

float CTimer::GetFps(void) { 
	return (float)1000.0 / ((float)(currentTime - lastTime)); 
}

void CTimer::Initialize(void) { 
	currentTime = GetTimeMSec(); lastTime = 0; 
}

void CTimer::Update(void) { 
	lastTime = currentTime; currentTime = GetTimeMSec(); 
}

CTimer::CTimer(void) {
	Initialize(); 
}

CTimer::~CTimer(void) {
}
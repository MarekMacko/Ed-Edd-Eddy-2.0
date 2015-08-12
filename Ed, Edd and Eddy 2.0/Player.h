#pragma once

class CPlayer
{
public:
	vec3 pos;
	vec3 dir;
	vec3 cam; // Przesunięcie punktu zaczepienia kamery względem pozycji gracza.
	float speed;
	CPlayer() {
		pos.Set(0.0f, 0.0f, 0.0f);
		dir.Set(0.0f, 0.0f, -1.0f);
		cam.Set(0.0f, 0.25f, 0.0f);
		speed = 0.0f;
	}
	
};


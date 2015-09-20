#pragma once

// Wektor 3-elementowy z przydatnymi metodami.
struct vec3 {

	float x, y, z;

	vec3() {
		x = y = z = 0.0f;
	}

	vec3(float nx, float ny, float nz) {
		x = nx;
		y = ny;
		z = nz;
	}

	vec3(float nxyz) {
		x = y = z = nxyz;
	}

	void Set(float nx, float ny, float nz) {
		x = nx;
		y = ny;
		z = nz;
	}

	void Set(float nxyz) {
		x = y = z = nxyz;
	}

	void Set(vec3 v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	vec3 operator=(const vec3 v) {
		Set(v.x, v.y, v.z);
		return *this;
	}

	vec3 operator-(const vec3 v) {
		return vec3(x - v.x, y - v.y, z - v.z);
	}

	vec3 operator+(const vec3 v) {
		return vec3(x + v.x, y + v.y, z + v.z);
	}

	vec3 operator*(const float f) {
		return vec3(x * f, y * f, z * f);
	}

	bool operator>(vec3 v) {
		return(x > v.x && y > v.y && z > v.z);
	}

	bool operator>=(vec3 v) {
		return(x >= v.x && y >= v.y && z >= v.z);
	}

	bool operator<(vec3 v) {
		return(x < v.x && y < v.y && z < v.z);
	}

	bool operator<=(vec3 v) {
		return(x <= v.x && y <= v.y && z <= v.z);
	}

	bool operator==(vec3 v) {
		return(x == v.x && y == v.y && z == v.z);
	}

	float Length() {	
		return sqrt(x * x + y * y + z * z);
	}

	float Length2() {
		return x * x + y * y + z * z;
	}

	void Normalize() {
		float d = Length();
		x /= d;
		y /= d;
		z /= d;
	}

	void SetLength(float l) {
		Normalize();
		x *= l;
		y *= l;
		z *= l;
	}

	void Scale(float s) {
		x *= s;
		y *= s;
		z *= s;
	}

	void Scale(float sx, float sy, float sz) {
		x *= sx;
		y *= sy;
		z *= sz;
	}

	void Scale(vec3 s) {
		x *= s.x;
		y *= s.y;
		z *= s.z;
	}

	float Dot(vec3 b) {
		return x * b.x + y * b.y + z * b.z;
	}

	static void Cross(vec3 a, vec3 b, vec3 &c) {
		c.x = a.y * b.z - a.z * b.y;
		c.y = a.z * b.x - a.x * b.z;
		c.z = a.x * b.y - a.y * b.x;
	}
};

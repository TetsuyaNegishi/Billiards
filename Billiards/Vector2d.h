#pragma once

class Vector2d{
public:
	Vector2d();
	Vector2d(float _x, float _y);
	Vector2d& Vector2d::operator=(const Vector2d& v);
	Vector2d& operator+=(const Vector2d& v);
	Vector2d& operator-=(const Vector2d& v);
	Vector2d& operator*=(float k);
	Vector2d& operator/=(float k);
	Vector2d operator+();
	Vector2d operator-();
	float norm();
	float norm2();
	void normalize();
	Vector2d getNormalizeVector();

	float x;
	float y;
};

Vector2d operator+(const Vector2d& u, const Vector2d& v);

Vector2d operator-(const Vector2d& u, const Vector2d& v);

float operator*(const Vector2d& u, const Vector2d& v);

Vector2d operator*(const Vector2d& v, float k);
Vector2d operator*(float k, const Vector2d& v);
Vector2d operator/(const Vector2d& v, float k);

float Cross(Vector2d v1, Vector2d v2);
Vector2d NormalVectorLeft(Vector2d v);
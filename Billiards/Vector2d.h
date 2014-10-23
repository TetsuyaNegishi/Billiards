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

	float x;
	float y;
};

Vector2d operator+(const Vector2d& u, const Vector2d& v);

Vector2d operator-(const Vector2d& u, const Vector2d& v);

float operator*(const Vector2d& u, const Vector2d& v);

Vector2d operator*(const Vector2d& v, float k);
Vector2d operator*(float k, const Vector2d& v);
Vector2d operator/(const Vector2d& v, float k);
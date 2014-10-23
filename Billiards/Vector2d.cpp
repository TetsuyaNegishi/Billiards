#include "Vector2D.h"

Vector2d::Vector2d() :x(0), y(0)
{
}

Vector2d::Vector2d(float _x, float _y) : x(_x), y(_y)
{
}
//������Z�q�̒�`
Vector2d& Vector2d::operator=(const Vector2d& v){
	this->x = v.x;	this->y = v.y;
	return *this;
}
// +=�̒�`
Vector2d& Vector2d::operator+=(const Vector2d& v){
	this->x += v.x;	this->y += v.y;	return *this;
}
// -=�̒�`
Vector2d& Vector2d::operator-=(const Vector2d& v){
	this->x -= v.x;	this->y -= v.y;	return *this;
}
// *=�̒�`
Vector2d& Vector2d::operator*=(float k){
	this->x *= k;	this->y *= k;	return *this;
}
// /=�̒�`
Vector2d& Vector2d::operator/=(float k){
	this->x /= k;	this->y /= k;	return *this;
}

//+�̒�`:	+v
Vector2d Vector2d::operator+(){
	return *this;
}
//-�̒�`:	-v
Vector2d Vector2d::operator-(){
	return Vector2d(-x, -y);
}


//�񍀉��Z�q
Vector2d operator+(const Vector2d& u, const Vector2d& v){	//vector+vector
	Vector2d w;
	w.x = u.x + v.x;
	w.y = u.y + v.y;
	return w;
}

Vector2d operator-(const Vector2d& u, const Vector2d& v){	//vector-vector
	Vector2d w;
	w.x = u.x - v.x;
	w.y = u.y - v.y;
	return w;
}

float operator*(const Vector2d& u, const Vector2d& v){	//���� vector*vector
	return u.x * v.x + u.y * v.y;
}

Vector2d operator*(const Vector2d& v, float k){	//vector*scalar
	Vector2d w;
	w.x = v.x * k;
	w.y = v.y * k;
	return w;
}
Vector2d operator*(float k, const Vector2d& v){	//scalar*vector
	Vector2d w;
	w.x = v.x * k;
	w.y = v.y * k;
	return w;
}
Vector2d operator/(const Vector2d& v, float k){	//vector/scalar
	Vector2d w;
	w.x = v.x / k;
	w.y = v.y / k;
	return w;
}
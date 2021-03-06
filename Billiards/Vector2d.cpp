#include "Vector2D.h"
#include <math.h>

Vector2d::Vector2d() :x(0), y(0)
{
}

Vector2d::Vector2d(float _x, float _y) : x(_x), y(_y)
{
}
//代入演算子の定義
Vector2d& Vector2d::operator=(const Vector2d& v){
	this->x = v.x;	this->y = v.y;
	return *this;
}
// +=の定義
Vector2d& Vector2d::operator+=(const Vector2d& v){
	this->x += v.x;	this->y += v.y;	return *this;
}
// -=の定義
Vector2d& Vector2d::operator-=(const Vector2d& v){
	this->x -= v.x;	this->y -= v.y;	return *this;
}
// *=の定義
Vector2d& Vector2d::operator*=(float k){
	this->x *= k;	this->y *= k;	return *this;
}
// /=の定義
Vector2d& Vector2d::operator/=(float k){
	this->x /= k;	this->y /= k;	return *this;
}

//+の定義:	+v
Vector2d Vector2d::operator+(){
	return *this;
}
//-の定義:	-v
Vector2d Vector2d::operator-(){
	return Vector2d(-x, -y);
}

//ノルム
float Vector2d::norm(){
	return sqrt(x*x + y*y);
}

//ノルムの２乗
float Vector2d::norm2(){
	return x*x + y*y;
}

//正規化
void Vector2d::normalize(){
	*this = *this / norm();
}

Vector2d Vector2d::getNormalizeVector(){
	return *this / norm();
}

//二項演算子
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

float operator*(const Vector2d& u, const Vector2d& v){	//内積 vector*vector
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

float Cross(Vector2d v1, Vector2d v2){
	return v1.x*v2.y - v1.y*v2.x;
}

Vector2d NormalVectorLeft(Vector2d v){
	return Vector2d(-v.y, v.x);
}
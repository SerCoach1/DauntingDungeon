#include "Vector2.h"
#include <cmath>

Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Vector2::normalise()
{
	if (x == 0 && y == 0)
		return;

	float length = std::sqrt((x*x) + (y*y));
	x /= length;
	y /= length;
}

float Vector2::magnitude()
{
	return std::sqrt((x*x) + (y*y));
}

float Vector2::DotProduct(Vector2 v) const
{
	return (this->x*v.x + this->y*v.y);
}

void Vector2::ToZero()
{
	x = 0.0f;
	y = 0.0f;
}

//Vector2 Vector2::operator-(const Vector2 & v) const
//{
//	return Vector2(x - v.x, y - v.y);
//}

Vector2 Vector2::operator+(const Vector2 & v) const
{
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator/(const Vector2 & v) const
{
	return Vector2(x / v.x, y / v.y);
}

Vector2 Vector2::operator*(float f) const
{
	return Vector2(x * f, y * f);
}

Vector2 Vector2::operator/(float f) const
{
	return Vector2(x / f, y / f);
}

void Vector2::operator+=(const Vector2 & v)
{
	x += v.x;
	y += v.y;
}

void Vector2::operator*=(float f)
{
	x *= f;
	y *= f;
}

void Vector2::operator-=(const Vector2 & a)
{
	x -= a.x;
	y -= a.y;
}

Vector2 operator-(const Vector2&vec1, const Vector2&vec2)
{
	float x = vec1.x - vec2.x;
	float y = vec1.y - vec2.y;
	return Vector2(x,y);
}

std::ostream & operator<<(std::ostream & o, const Vector2 & v)
{
	o << "Vector2(" << v.x << "," << v.y << ")";
	return o;
}

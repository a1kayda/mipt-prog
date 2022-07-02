//
//  classes.cpp
//  firstproject(akaVS)
//
//  Created by mac on 15/02/2019.
//  Copyright © 2019 mac. All rights reserved.
//

#include "header.h"

float Vector2::Len() const
{
    return sqrt(x*x+y*y);
}
float Vector2::sqrtLen() const
{
	return x*x+y*y;
}
Vector2::Vector2(float a, float b)
{
    x = a;
    y = b;
}

ostream& operator<<(ostream& stream, const Vector2& v)
{
	stream << v.x << " " << v.y << endl;
	return stream;
}

istream& operator>>(istream& stream, Vector2& v)
{
	stream >> v.x >> v.y;
	return stream;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	Vector2 res(0, 0);
	res.x = other.x + x;
	res.y = other.y + y;
	return res;
}
Vector2 Vector2::operator-(const Vector2& other) const
{
	Vector2 res(0, 0);
	res.x = - other.x + x;
	res.y = - other.y + y;
	return res;
}
Vector2& Vector2::operator+=(const Vector2& right)
{
	x += right.x;
	y += right.y;
	return *this;
}
Vector2& Vector2::operator-=(const Vector2& right)
{
	x -= right.x;
	y -= right.y;
	return *this;
}
float Vector2::operator*(const Vector2& right) const
{
	return (x*right.x + y*right.y);
}
float Vector2::operator^(const Vector2& right) const
{
	float res;
	res = x*right.y - right.x*y;
	if(res< 0)
		res = -res;
	return res;
}
Vector2& Vector2::operator*(const float c)//умножение на скаляр справа
{
	x *= c;
	y *= c;
	return *this;
}

Vector2& operator*(const float c, Vector2& v)
{
	v = v*c;
	return v;
}

Vector2& Vector2::operator/(const float c)
{
	x /= c;
	y /= c;
	return *this;
}
Vector2 Vector2::norm()
{
	Vector2 normv(0,0);
	float mod = Len();
	normv.x = x / mod;
	normv.y = y / mod;
	return normv;
}
Vector2 Vector2::perp()
{
	return Vector2(y, -x);
}
Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}
Vector2& Vector2::rotate(float angle)
{
	float x1 = x, y1 = y;
	x = x1*cos(angle*M_PI/180) - y1*sin(angle*M_PI/180);
	y = y1*cos(angle*M_PI/180) + x1*sin(angle*M_PI/180);
	return *this;
}
Vector2 Vector2::Getrotated(float angle) const
{
	Vector2 res(0,0);
	res.x = x*cos(angle*M_PI/180) - y*sin(angle*M_PI/180);
	res.y = y*cos(angle*M_PI/180) + x*sin(angle*M_PI/180);
	return res;
}

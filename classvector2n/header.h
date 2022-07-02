//
//  Header.h
//  firstproject(akaVS)
//
//  Created by mac on 15/02/2019.
//  Copyright © 2019 mac. All rights reserved.
//

#pragma once
#include <iostream>
#include <cmath>
using namespace std;

class Vector2
{
public:
    Vector2(float a, float b);
    float Len() const;
	float sqrtLen() const;
	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	float operator^(const Vector2& right) const;
	float operator*(const Vector2& right) const;
	Vector2& operator*(const float c);
	friend Vector2& operator*(const float c, Vector2& v);
	Vector2& operator/(const float c);
	Vector2 norm();
	Vector2 perp();
	Vector2 operator-() const;
	Vector2& rotate(float angle);
	Vector2 Getrotated(float angle) const;
	friend istream& operator>>(istream& stream, Vector2& v);
	friend ostream& operator<<(ostream& stream, const Vector2& v);
private:
    float x, y;
};

 /* Header_h */

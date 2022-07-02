//
//  methods.cpp
//  classvectortrack
//
//  Created by mac on 25/02/2019.
//  Copyright © 2019 mac. All rights reserved.
//

#include "methods.hpp"

Vector::Vector() :
data_(nullptr),
capacity_(0),//макс размер
size_(0)//реальный размер
{}



Vector::Vector(int cap):
data_(new int[cap]{}),
capacity_(cap),
size_(0)
{}


Vector::~Vector()
{
	delete[]data_;
	data_= nullptr;
	
}

int& Vector::at(int index)
{
	assert ( 0 <= index && index < size_ );
	return data_[index];
}
int& Vector::operator[](int index)
{
	return at(index);
}


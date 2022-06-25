#pragma once
#include<iostream>


class Visitor
{
public:
	Visitor();

	~Visitor();

	void InfoBook();

private:
	char firstName[25];
	char lastName[25];
	int* bookID;
};



#pragma once
#include"Moderator.h"

class Administrator :
	public Moderator
{
public:
	Administrator();
	Administrator(const char* nickname, int age);
	Administrator& operator=(const Administrator& rhs);
	~Administrator();
};


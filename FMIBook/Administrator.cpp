#include "Administrator.h"

Administrator::Administrator() : Moderator()
{
}

Administrator::Administrator(const char* nickname, int age)
{
	this->SetNickname(nickname);
	this->SetAge(age);
}

Administrator& Administrator::operator=(const Administrator& rhs)
{
	if (this != &rhs)
	{
		Moderator::operator=(rhs);
	}
	return *this;
}


Administrator::~Administrator()
{
}

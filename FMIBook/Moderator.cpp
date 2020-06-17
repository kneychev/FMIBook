#include "Moderator.h"

Moderator::Moderator() : User()
{
}

Moderator::Moderator(const char* newName, int newAge) : User()
{
	SetNickname(newName);
	SetAge(newAge);
}

Moderator& Moderator::operator=(const Moderator& rhs)
{
	if (this != &rhs)
	{
		User::operator=(rhs);
	}
	return *this;
}

Moderator::~Moderator()
{

}

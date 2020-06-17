#pragma once
#include "User.h"

class Moderator :
	public User
{
public:
	Moderator();
	Moderator(const char* newName, int newAge);
	Moderator& operator=(const Moderator& rhs);
	~Moderator();
};


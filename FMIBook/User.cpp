#include "User.h"

User::User() :nickname(nullptr), age(5), ids(nullptr), sizeOfIdsArr(0), capacityOfIdsArr(0)
{
}

User::User(const char* newName, int newAge) 
	:nickname(nullptr), age(newAge), ids(nullptr), sizeOfIdsArr(0), capacityOfIdsArr(0)
{
	SetNickname(newName);
}

User::User(const User& other)
{
	copyFrom(other);
}

User& User::operator=(const User& rhs)
{
	if (this != &rhs)
	{
		free();
		copyFrom(rhs);
	}
	return *this;
}

User::~User()
{
	free();
}

const char* User::GetNickname() const
{
	return this->nickname;
}

const int User::GetAge() const
{
	return this->age;
}

const int User::GetSizeOfIdsArr() const
{
	return sizeOfIdsArr;
}

const int* User::GetID() const
{
	return ids;
}

void User::SetNickname(const char* newNickname)
{
	if (nickname)
		delete[] nickname;

	nickname = new(std::nothrow) char[strlen(newNickname) + 1];
	if (!nickname)
	{
		std::cerr << "Could not allocate memory for the nickname";
		return;
	}
	strncpy(nickname, newNickname, strlen(newNickname) + 1);
}

void User::SetAge(int newAge)
{
	if (newAge <= 4 || newAge > 122) // the world record for oldest person :)
	{
		std::cerr << "Invalid age!\n";
		return;
	}

	age = newAge;
}

void User::AddId(int id)
{
	if (sizeOfIdsArr == capacityOfIdsArr)
		resize();

	ids[sizeOfIdsArr++] = id;
}

void User::RemoveId(int id)
{
	int idx = -1;
	for (int i = 0; i < sizeOfIdsArr; ++i)
	{
		if (ids[i] == id)
		{
			idx = i;
			break;
		}
	}

	if (idx == -1)
	{
		std::cerr << "The ID doesn't exist!\n";
		return;
	}

	for (int i = idx; i < sizeOfIdsArr; ++i)
	{
		ids[i] = ids[i + 1];
	}
	sizeOfIdsArr--;
}

void User::copyFrom(const User& other)
{
	nickname = new(std::nothrow) char[strlen(other.nickname) + 1];
	if (!nickname)
	{
		std::cerr << "Could not allocate memory for the nickname!\n";
		exit(1);
	}
	strncpy(nickname, other.nickname, strlen(other.nickname) + 1);
	age = other.age;

	capacityOfIdsArr = other.capacityOfIdsArr;
	sizeOfIdsArr = other.sizeOfIdsArr;

	ids = new(std::nothrow) int[sizeOfIdsArr];
	if (!ids)
	{
		std::cerr << "Could not allocate memory for ids!\n";
		exit(1);
	}
	for (int i = 0; i < sizeOfIdsArr; ++i)
	{
		ids[i] = other.ids[i];
	}
}

void User::free()
{
	delete[] nickname;
	age = 0;
	delete[] ids;
	sizeOfIdsArr = 0;
	capacityOfIdsArr = 0;
}

void User::resize()
{
	if (capacityOfIdsArr == 0)
		capacityOfIdsArr = 1;

	capacityOfIdsArr *= 2;
	int* newIds = new(std::nothrow) int[capacityOfIdsArr];
	if(!newIds)
	{
		std::cerr << "Not enough memory!\n";
		exit(1);
	}

	for (int i = 0; i < sizeOfIdsArr; ++i)
	{
		newIds[i] = ids[i];
	}

	delete[] ids;
	ids = newIds;
}

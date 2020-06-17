#pragma once
#include <iostream>

class User
{
public:
	User();
	User(const char* name, int age);
	User(const User& other);
	User& operator=(const User& rhs);
	~User();

	const char* GetNickname() const;
	const int GetAge() const;
	const int GetSizeOfIdsArr() const;
	const int* GetID() const;

	void SetNickname(const char* newNickname);
	void SetAge(int newAge);

	void AddId(int id);
	void RemoveId(int id);

private:
	void copyFrom(const User& other);
	void free();
	void resize();

private:
	int* ids;
	int sizeOfIdsArr;
	int capacityOfIdsArr;

	char* nickname;
	int age;
};


#pragma once
#include <iostream>
#include <fstream>

class Publication // virtual class
{
public:
	Publication(int newId = -1, char* newContend = nullptr);
	Publication(const Publication& other);
	Publication& operator=(const Publication& rhs);
	virtual ~Publication();

	void SetId(int newId);
	void SetContend(const char* newContend);
	
	const int GetID() const;
	const char* GetContend() const;

	virtual void SaveToFile(std::ofstream& out, const char* actor, int ID) = 0;
	virtual void SaveManyToFile(std::ofstream& out) = 0;
	virtual Publication* clone() const = 0;

private:
	int id;
	char* contend;
	
};


#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Publication // virtual class
{
public:
	Publication(int newId = -1, char* newContent = nullptr);
	Publication(const Publication& other);
	Publication& operator=(const Publication& rhs);
	virtual ~Publication();

	void SetId(int newId);
	void SetContent(const char* newContent);
	
	const int GetID() const;
	const char* GetContent() const;

	virtual void SaveToFile(std::ofstream& out, const char* actor, int ID) = 0;
	virtual void SaveManyToFile(std::ofstream& out) = 0;
	virtual Publication* clone() const = 0;

private:
	int id;
	char* content;
};


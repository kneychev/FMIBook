#pragma once
#include "Publication.h"
class Text :
	public Publication
{
public:
	Text();
	Text(int ID, const char* newContend);
	Text(const Text& other);
	Text& operator=(const Text& rhs);
	virtual ~Text();

	virtual void SaveToFile(std::ofstream& out, const char* actor, int ID);
	virtual void SaveManyToFile(std::ofstream& out);
	virtual Publication* clone() const;
};


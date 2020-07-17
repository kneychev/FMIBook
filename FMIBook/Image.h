#pragma once
#include "Publication.h"

class Image :
	public Publication
{
public:
	Image();
	Image(int id, const char* content);
	Image(const Image& other);
	Image& operator=(const Image& rhs);
	virtual ~Image();

	virtual void SaveToFile(std::ofstream& out, const char* actor, int ID);
	virtual void SaveManyToFile(std::ofstream& out);
	virtual Publication* clone() const;
};


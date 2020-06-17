#pragma once
#include "Publication.h"

class Image :
	public Publication
{
public:
	Image();
	Image(int id, const char* contend);
	Image(const Image& other);
	Image& operator=(const Image& rhs);
	virtual ~Image();

	virtual void SaveToFile(std::ofstream& out);
	virtual void SaveManyToFile(std::ofstream& out);
	virtual Publication* clone() const;
};


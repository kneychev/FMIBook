#include "Publication.h"

Publication::Publication(int newId, char* newContend)
	: id(newId), contend(newContend)
{
}

Publication::Publication(const Publication& other)
{
	contend = new(std::nothrow) char[strlen(other.contend) + 1];
	if (!contend)
	{
		std::cerr << "Could not allocate memory for the contend of publication!\n";
		exit(1);
	}
	strncpy(contend, other.contend, strlen(other.contend) + 1);
	id = other.id;
}

Publication& Publication::operator=(const Publication& rhs)
{
	if (this != &rhs)
	{
		delete[] contend;

		contend = new(std::nothrow) char[strlen(rhs.contend) + 1];
		if (!contend)
		{
			std::cerr << "Could not allocate memory for the contend of publication!\n";
			exit(1);
		}
		strncpy(contend, rhs.contend, strlen(rhs.contend) + 1);
		id = rhs.id;
	}
	return *this;
}

Publication::~Publication()
{
	delete[] contend;
	id = -1;
}

void Publication::SetId(int newId)
{
	id = newId;
}

void Publication::SetContend(const char* newContend)
{
	if (contend)
	{
		delete[] contend;
		contend = nullptr;
	}

	contend = new(std::nothrow) char[strlen(newContend) + 1];
	if (!contend)
	{
		std::cerr << "Could not allocate memory for the contend of publication!\n";
		exit(1);
	}
	strncpy(contend, newContend, strlen(newContend) + 1);
}

const int Publication::GetID() const
{
	return id;
}

const char* Publication::GetContend() const
{
	return contend;
}



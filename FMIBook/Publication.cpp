#include "Publication.h"

Publication::Publication(int newId, char* newContent)
	: id(newId), content(newContent)
{
}

Publication::Publication(const Publication& other)
{
	content = new(std::nothrow) char[strlen(other.content) + 1];
	if (!content)
	{
		std::cerr << "Could not allocate memory for the content of publication!\n";
		exit(1);
	}
	strncpy(content, other.content, strlen(other.content) + 1);
	id = other.id;
}

Publication& Publication::operator=(const Publication& rhs)
{
	if (this != &rhs)
	{
		delete[] content;

		content = new(std::nothrow) char[strlen(rhs.content) + 1];
		if (!content)
		{
			std::cerr << "Could not allocate memory for the content of publication!\n";
			exit(1);
		}
		strncpy(content, rhs.content, strlen(rhs.content) + 1);
		id = rhs.id;
	}
	return *this;
}

Publication::~Publication()
{
	delete[] content;
	id = -1;
}

void Publication::SetId(int newId)
{
	id = newId;
}

void Publication::SetContent(const char* newContent)
{
	if (content)
	{
		delete[] content;
		content = nullptr;
	}

	content = new(std::nothrow) char[strlen(newContent) + 1];
	if (!content)
	{
		std::cerr << "Could not allocate memory for the content of publication!\n";
		exit(1);
	}
	strncpy(content, newContent, strlen(newContent) + 1);
}

const int Publication::GetID() const
{
	return id;
}

const char* Publication::GetContent() const
{
	return content;
}



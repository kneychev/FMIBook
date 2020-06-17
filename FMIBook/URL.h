#pragma once
#include "Publication.h"

class URL :
	public Publication
{
public:
	URL();
	URL(int ID, const char* url, const char* desc);
	URL(const URL&other);
	URL& operator=(const URL& rhs);
	virtual ~URL();

	void SetDescription(const char* descr);

	const char* GetDescription() const;

	virtual void SaveToFile(std::ofstream& out);
	virtual void SaveManyToFile(std::ofstream& out);
	virtual Publication* clone() const;

private:
	char* description;
};


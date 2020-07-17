#include "URL.h"

const int MAX_URL_LEN = 512;

URL::URL() : Publication(), description(nullptr)
{
}

URL::URL(int ID, const char* url, const char* desc) : description(nullptr)
{
	SetContent(url);
	SetId(ID);
	SetDescription(desc);
}

URL::URL(const URL& other) : Publication(other), description(nullptr)
{
	description = new(std::nothrow) char[strlen(other.description) + 1];
	if (!description)
	{
		std::cerr << "Could not allocate memory for description!\n";
		exit(1);
	}
	strncpy(description, other.description, strlen(other.description) + 1);
}

URL& URL::operator=(const URL& rhs)
{
	if (this != &rhs)
	{
		delete[] description;

		Publication::operator=(rhs);
		
		description = new(std::nothrow) char[strlen(rhs.description) + 1];
		if (!description)
		{
			std::cerr << "Could not allocate memory for description!\n";
			exit(1);
		}
		strncpy(description, rhs.description, strlen(rhs.description) + 1);
	}
	return *this;
}

URL::~URL()
{
	delete[] description;
}

void URL::SetDescription(const char* descr)
{
	if (description)
	{ 
		delete[] description;
		description = nullptr;
	}

	description = new(std::nothrow) char[strlen(descr) + 1];
	if (!description)
	{
		std::cerr << "Could not allocate memory!\n";
		exit(1);
	}
	strncpy(description, descr, strlen(descr) + 1);
}

const char* URL::GetDescription() const
{
	return description;
}

void URL::SaveToFile(std::ofstream& out, const char* actor, int ID)
{
	out.open("Publication-URL.html");
	if (!out)
	{
		std::cerr << "Could not create the html file!\n";
		return;
	}
	out << actor << " viewed post with id=" << ID << '\n';
	out << "<a href=\"" << GetContent()
		<< "\">" << GetDescription() << "</a>";
	out.close();
}

void URL::SaveManyToFile(std::ofstream& out)
{
	out << "<a href=\"" << GetContent()
		<< "\">" << GetDescription() << "</a>" << std::endl;
}

Publication* URL::clone() const
{
	return new URL(*this);
}


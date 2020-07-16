#include "Text.h"


Text::Text() : Publication()
{
}

Text::Text(int ID, const char* newContend)
{
	SetId(ID);
	SetContend(newContend);
}

Text::Text(const Text& other) : Publication(other)
{
}

Text& Text::operator=(const Text& rhs)
{
	if (this != &rhs)
	{
		Publication::operator=(rhs);
	}
	return *this;
}


Text::~Text()
{
}

void Text::SaveToFile(std::ofstream& out, const char* actor, int ID)
{
	out.open("Publication-Text.html");
	if (!out)
	{
		std::cerr << "Could not create the html file!\n";
		return;
	}
	out << actor << " viewed post with id=" << ID << '\n';
	out << GetContend() << std::endl;
	out.close();
}

void Text::SaveManyToFile(std::ofstream& out)
{
	out << GetContend() << '\n';
}

Publication* Text::clone() const
{
	return new Text(*this);
}

#include "Text.h"


Text::Text() : Publication()
{
}

Text::Text(int ID, const char* newContent)
{
	SetId(ID);
	SetContent(newContent);
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
	out << GetContent() << std::endl;
	out.close();
}

void Text::SaveManyToFile(std::ofstream& out)
{
	out << GetContent() << '\n';
}

Publication* Text::clone() const
{
	return new Text(*this);
}

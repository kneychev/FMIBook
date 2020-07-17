#include "Image.h"


Image::Image() : Publication()
{
}

Image::Image(int id, const char* content)
{
	SetId(id);
	SetContent(content);
}

Image::Image(const Image& other) : Publication(other)
{
}

Image & Image::operator=(const Image& rhs)
{
	if (this != &rhs)
	{
		Publication::operator=(rhs);
	}
	return *this;
}

Image::~Image()
{
}

void Image::SaveToFile(std::ofstream& out, const char* actor, int ID)
{
	out.open("Publication-Image.html");
	if (!out)
	{
		std::cerr << "Could not create the html file!\n";
		return;
	}
	out << actor << " viewed post with id=" << ID << '\n';
	out << "<img src=\"" << GetContent() << "\">";
	out.close();
}

void Image::SaveManyToFile(std::ofstream& out)
{
	out << "<img src=\"" << GetContent() << "\">\n";
}

Publication* Image::clone() const
{
	return new Image(*this);
}


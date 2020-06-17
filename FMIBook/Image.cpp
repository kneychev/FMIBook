#include "Image.h"


Image::Image() : Publication()
{
}

Image::Image(int id, const char* contend)
{
	SetId(id);
	SetContend(contend);
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

void Image::SaveToFile(std::ofstream& out)
{
	out.open("Publication-Image.html");
	if (!out)
	{
		std::cerr << "Could not create the html file!\n";
		return;
	}
	out << "<img src=\"" << GetContend() << "\">";
	out.close();
}

void Image::SaveManyToFile(std::ofstream& out)
{
	out << "<img src=\"" << GetContend() << "\">\n";
}

Publication* Image::clone() const
{
	return new Image(*this);
}


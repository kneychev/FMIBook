#pragma once
#include "Publication.h"
#include "Image.h"
#include "URL.h"
#include "Text.h"
#include "People.h"

class Posts
{
public:
	Posts();
	~Posts();

	const int GetSizeOfPostsArr() const;
	Publication& operator[](int idx);

	void Add(const Publication& p);
	void Remove(int ID);
	void ViewPost(int ID) const;

private:
	void resize();

private:
	Publication ** posts;
	int sizeOfPostsArr;
	int capacityOfPostsArr;
};


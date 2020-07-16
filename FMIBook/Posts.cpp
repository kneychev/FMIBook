#include "Posts.h"

Posts::Posts() : posts(nullptr), sizeOfPostsArr(0), capacityOfPostsArr(0)
{
}

Posts::~Posts()
{
	for (int i = 0; i < sizeOfPostsArr; ++i)
	{
		delete[] posts[i];
	}
	delete[] posts;
}

const int Posts::GetSizeOfPostsArr() const
{
	return sizeOfPostsArr;
}

Publication& Posts::operator[](int idx)
{
	return *posts[idx];
}

void Posts::Add(const Publication& p)
{
	if (sizeOfPostsArr == capacityOfPostsArr)
		resize();

	posts[sizeOfPostsArr++] = p.clone();
}

void Posts::Remove(int ID)
{
	int idx = -1;
	for (int i = 0; i < sizeOfPostsArr; ++i)
	{
		if (posts[i]->GetID() == ID)
		{
			idx = i;
			break;
		}
	}

	if (idx == -1)
	{
		std::cerr << "Invalid id!\n";
		return;
	}

	Publication** temp = new(std::nothrow) Publication*[capacityOfPostsArr];
	if (!temp)
	{
		std::cerr << "Not enough memory!\n";
		exit(1);
	}

	int j = 0;

	for (int i = 0; i < sizeOfPostsArr; ++i)
	{
		if (i == idx)
			continue;
		temp[j] = posts[i]->clone();
		j++;
	}

	for (int i = 0; i < sizeOfPostsArr; ++i)
	{
		delete[] posts[i];
	}

	delete[] posts;
	posts = temp;

	sizeOfPostsArr--;
}

void Posts::ViewPost(const char* actor, int ID) const
{
	std::ofstream out;
	for (int i = 0; i < sizeOfPostsArr; ++i)
	{
		if (posts[i]->GetID() == ID)
		{
			posts[i]->SaveToFile(out, actor, ID);
			std::cout << actor << " viewed post " << ID << std::endl;
			return;
		}
	}
	std::cerr << "Invalid ID!\n";
}

void Posts::resize()
{
	if (capacityOfPostsArr == 0)
		capacityOfPostsArr = 1;

	capacityOfPostsArr *= 2;
	Publication** newPosts = new(std::nothrow) Publication*[capacityOfPostsArr];
	if (!newPosts)
	{
		std::cerr << "Could not allocate array for the posts!\n";
		exit(1);
	}
	memset(newPosts, 0, sizeOfPostsArr * 2 * sizeof(Publication*));

	for (int i = 0; i < sizeOfPostsArr; ++i)
	{
		newPosts[i] = posts[i];
	}
	delete[] posts;
	posts = newPosts;
}

#pragma once
#include "People.h"
#include "Posts.h"

class FMIBook
{
public:
	FMIBook();
	~FMIBook();

	void Execute();

private:
	void MakePost(const char* actor, const char* type);
	void ViewAllPosts(const char* owner);
	void Info();
	void RemoveSomeonePosts(const char* name);
private:
	People people;
	Posts posts;
	int id;
};


#pragma once
#include <string>
#include <unordered_map>
#include "People.h"
#include "Posts.h"

class FMIBook
{
public:
	FMIBook();
	~FMIBook();

	void Execute();

private:
	void add_user(const char* actor);
	void add_moderator(const char* actor);
	void remove_user(const char* actor);
	void remove_moderator(const char* actor);
	void block(const char* actor);
	void unblock(const char* actor);
	void change_name(const char* actor);
	void post(const char* actor);
	void remove_post(const char* actor);
	void view_post(const char* actor);
	void view_all_posts(const char* actor);

private:
	void MakePost(const char* actor, const char* type);
	void ViewAllPosts(const char* actor, const char* owner);
	void Info();
	void RemoveSomeonePosts(const char* name);
private:
	People people;
	Posts posts;
	int id;
};


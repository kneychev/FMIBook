#include "FMIBook.h"

const int MAX_COMMAND_SIZE = 17; // the length of "remove_moderator"
const int MAX_NICKNAME_LENGTH = 128;
const int MAX_POST_TYPE_NAME_LENGHT = 8; // [image]
const int MAX_POST_CONTENT_LENGTH = 512;
const int MAX_INPUT_LENGTH = 128;
const int MAX_ROW_LENGTH = 1024;

FMIBook::FMIBook() : id(0)
{
}

FMIBook::~FMIBook()
{
}

void FMIBook::Execute()
{
/*	while (true)
	{
		char actor[MAX_NICKNAME_LENGTH];
		std::cin >> actor;

		if (strcmp(actor, "quit") == 0)
		{
			break;
		}
		if (strcmp(actor, "info") == 0)
		{
			Info();
			std::cin.ignore(10000, '\n');
			continue;
		}

		char command[MAX_COMMAND_SIZE];
		std::cin >> command;

		if (strcmp(command, "add_user") == 0)
		{
			char userNickname[MAX_NICKNAME_LENGTH];
			std::cin >> userNickname;

			int age;
			std::cin >> age;
			people.AddUser(actor, userNickname, age);
		}
		else if (strcmp(command, "add_moderator") == 0)
		{
			char moderatorNickname[MAX_NICKNAME_LENGTH];
			std::cin >> moderatorNickname;

			int age;
			std::cin >> age;
			people.AddModerator(actor, moderatorNickname, age);
		}
		else if (strcmp(command, "remove_user") == 0)
		{
			char userNickname[MAX_NICKNAME_LENGTH];
			std::cin >> userNickname;

			people.RemoveUser(actor, userNickname);
			RemoveSomeonePosts(userNickname);
		}
		else if (strcmp(command, "remove_moderator") == 0)
		{
			char moderatorNickname[MAX_NICKNAME_LENGTH];
			std::cin >> moderatorNickname;

			people.RemoveModerator(actor, moderatorNickname);
			RemoveSomeonePosts(moderatorNickname);
		}
		else if (strcmp(command, "block") == 0)
		{
			char blocked[MAX_NICKNAME_LENGTH];
			std::cin >> blocked;

			people.Block(actor, blocked);
		}
		else if (strcmp(command, "unblock") == 0)
		{
			char unblocked[MAX_NICKNAME_LENGTH];
			std::cin >> unblocked;

			people.Unblock(actor, unblocked);
		}
		else if (strcmp(command, "change_name") == 0)
		{
			char newNick[MAX_NICKNAME_LENGTH];
			std::cin >> newNick;

			people.ChangeNickname(actor, newNick);
		}
		else if (strcmp(command, "post") == 0)
		{
			char type[MAX_POST_TYPE_NAME_LENGHT];
			std::cin >> type;

			MakePost(actor, type);
		}
		else if (strcmp(command, "remove_post") == 0) 
		{
			if ( !people.isAdmin(actor) && !people.isModerator(actor) )
			{
				std::cout << actor << " has no rights to remove posts!\n";
				continue;
			}

			int idRemove;
			std::cin >> idRemove;

			posts.Remove(idRemove);
		}
		else if (strcmp(command, "view_post") == 0)
		{
			int idView;
			std::cin >> idView;

			posts.ViewPost(actor, idView);
		}
		else if (strcmp(command, "view_all_posts") == 0)
		{
			char postsOwner[MAX_NICKNAME_LENGTH];
			std::cin.ignore(100, ' ');
			std::cin.getline(postsOwner, MAX_NICKNAME_LENGTH);

			ViewAllPosts(actor, postsOwner);
		}
		else
		{
			std::cout << "Unknown command!\n";
			std::cin.ignore(10000, '\n');
		}
	}*/
	
	bool shouldWork = true;

	while (shouldWork)
	{
		std::unordered_map<std::string, void (FMIBook::*)(const char*)> userCommands =
		{
			{ "add_user", &FMIBook::add_user },
			{ "add_moderator", &FMIBook::add_moderator },
			{ "remove_user", &FMIBook::remove_user },
			{ "remove_moderator", &FMIBook::remove_moderator },
			{ "block", &FMIBook::block },
			{ "unblock", &FMIBook::unblock },
			{ "change_name", &FMIBook::change_name },
			{ "post", &FMIBook::post },
			{ "remove_post", &FMIBook::remove_post },
			{ "view_post", &FMIBook::view_post },
			{ "view_all_posts", &FMIBook::view_all_posts }
		};

		char input[MAX_INPUT_LENGTH];
		std::cin >> input;

		if (strcmp(input, "quit") == 0)
		{
			shouldWork = false;
			continue;
		}

		if (strcmp(input, "info") == 0)
		{
			Info();
			continue;
		}

		char command[MAX_COMMAND_SIZE];
		std::cin >> command;

		auto it = userCommands.find(command);

		if (it == userCommands.end())
		{
			std::cout << "Invalid command!\n";
			continue;
		}

		(this->*(it->second))(input);
	}
}

void FMIBook::add_user(const char* actor)
{
	char userNickname[MAX_NICKNAME_LENGTH];
	std::cin >> userNickname;

	int age;
	std::cin >> age;

	people.AddUser(actor, userNickname, age);
}

void FMIBook::add_moderator(const char* actor)
{
	char moderatorNickname[MAX_NICKNAME_LENGTH];
	std::cin >> moderatorNickname;

	int age;
	std::cin >> age;

	people.AddModerator(actor, moderatorNickname, age);
}

void FMIBook::remove_user(const char* actor)
{
	char userNickname[MAX_NICKNAME_LENGTH];
	std::cin >> userNickname;

	people.RemoveUser(actor, userNickname);
	RemoveSomeonePosts(userNickname);
}

void FMIBook::remove_moderator(const char* actor)
{
	char moderatorNickname[MAX_NICKNAME_LENGTH];
	std::cin >> moderatorNickname;

	people.RemoveModerator(actor, moderatorNickname);
	RemoveSomeonePosts(moderatorNickname);
}

void FMIBook::block(const char* actor)
{
	char blocked[MAX_NICKNAME_LENGTH];
	std::cin >> blocked;

	people.Block(actor, blocked);
}

void FMIBook::unblock(const char* actor)
{
	char unblocked[MAX_NICKNAME_LENGTH];
	std::cin >> unblocked;

	people.Unblock(actor, unblocked);
}

void FMIBook::change_name(const char* actor)
{
	char newNick[MAX_NICKNAME_LENGTH];
	std::cin >> newNick;

	people.ChangeNickname(actor, newNick);
}

void FMIBook::post(const char* actor)
{
	char type[MAX_POST_TYPE_NAME_LENGHT];
	std::cin >> type;

	MakePost(actor, type);
}

void FMIBook::remove_post(const char* actor)
{
	if (!people.isAdmin(actor) && !people.isModerator(actor))
	{
		std::cout << actor << " has no rights to remove posts!\n";
		std::cin.ignore(MAX_ROW_LENGTH, '\n');
		return;
	}

	int idRemove;
	std::cin >> idRemove;

	posts.Remove(idRemove);
}

void FMIBook::view_post(const char* actor)
{
	int idView;
	std::cin >> idView;

	posts.ViewPost(actor, idView);
}

void FMIBook::view_all_posts(const char* actor)
{
	char postsOwner[MAX_NICKNAME_LENGTH];
	std::cin.getline(postsOwner, MAX_NICKNAME_LENGTH);

	ViewAllPosts(actor, postsOwner);
}

void FMIBook::MakePost(const char* actor, const char* type)
{
	if (strcmp(type, "[image]") == 0)
	{
		char directory[MAX_POST_CONTENT_LENGTH];
		std::cin.ignore(100, ' ');
		std::cin >> directory;

		if (people.isBlocked(actor))
		{
			std::cerr << actor << " is blocked!\n";
		}
		else
		{
			Image img(id, directory);
			posts.Add(img);
			(people.FindPerson(actor)).AddId(id);
			id++;
		}
	}
	else if (strcmp(type, "[url]") == 0)
	{
		char link[MAX_POST_CONTENT_LENGTH];
		std::cin >> link;
		std::cin.ignore(100, ' ');

		char description[MAX_POST_CONTENT_LENGTH];
		std::cin.getline(description, MAX_POST_CONTENT_LENGTH);

		if (people.isBlocked(actor))
		{
			std::cerr << actor << " is blocked!\n";
		}
		else
		{
			URL url(id, link, description);
			posts.Add(url);
			(people.FindPerson(actor)).AddId(id);
			id++;
		}
	}
	else if (strcmp(type, "[text]") == 0)
	{
		std::cin.ignore(100, ' ');
		char text[MAX_POST_CONTENT_LENGTH];
		std::cin.getline(text, MAX_POST_CONTENT_LENGTH);

		if (people.isBlocked(actor))
		{
			std::cerr << actor << " is blocked!\n";
		}
		else
		{
			Text t(id, text);
			posts.Add(t);
			(people.FindPerson(actor)).AddId(id);
			std::cout << actor << " created Post " << id << std::endl;
			id++;
		}
	}
}

void FMIBook::ViewAllPosts(const char* actor, const char* owner)
{
	if (!people.PersonExists(actor))
	{
		std::cout << actor << " does not exist!\n";
		return;
	}

	if (!people.PersonExists(owner))
	{
		std::cout << owner << " does not exist!\n";
		return;
	}

	char* fileName = new char[strlen(owner) + strlen("'s posts.html") + 1];
	if (!fileName)
	{
		std::cerr << "Could not allocate memory!\n";
		exit(1);
	}
	
	strncpy(fileName, owner, strlen(owner) + 1);
	strcat(fileName, "'s posts.html");

	std::ofstream out;
	out.open(fileName);
	if (!out)
	{
		std::cout << "Could not create " << fileName << "!\n";
		delete[] fileName;
		return;
	}

	out << actor << " viewed " << owner << "'s posts.";

	User tmp(people.FindPerson(owner)); // we need copy constructor, because when we get out
										// of the scope, we will delete our data
	for (int i = 0; i < tmp.GetSizeOfIdsArr(); ++i)
	{
		for (int j = 0; j < posts.GetSizeOfPostsArr(); ++j)
		{
			if (tmp.GetID()[i] == posts[j].GetID())
			{
				posts[j].SaveManyToFile(out);
			}
		}
	}
	delete[] fileName;
	out.close();
}

void FMIBook::Info()
{
	std::cout << "Admin is online\n"
		<< "Users - " << people.GetSizeOfUsersArr() << std::endl
		<< "Moderators - " << people.GetSizeOfModsArr() << std::endl
		<< "|Blocked| = " << people.GetSizeOfBlockedNamesArr() << std::endl
		<< "Blocked = { ";
	people.printBlocked();
	std::cout << "}\n";
	people.printYoungest();
	people.printOldest();
	people.printMostActive();
}

void FMIBook::RemoveSomeonePosts(const char* name)
{
	User tmp(people.FindPerson(name));

	for (int i = 0; i < tmp.GetSizeOfIdsArr(); ++i)
	{
		for (int j = 0; j < posts.GetSizeOfPostsArr(); ++j)
		{
			if (tmp.GetID()[i] == posts[j].GetID())
			{
				//int ID = posts[j].GetID();
				posts.Remove(posts[j].GetID());
			}
		}
	}
}

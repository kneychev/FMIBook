#include "People.h"

const int MAX_NAME_LENGTH = 128;

People::People() : mods(nullptr), sizeOfModsArr(0), capacityOfModsArr(0),
				users(nullptr), sizeOfUsersArr(0), capacityOfUsersArr(0),
				blockedNames(nullptr), sizeOfBlockedNamesArr(0), 
				capacityOfBLockedNamesArr(0)
{
	admin.SetNickname("Admin");
	admin.SetAge(14); // He is only 8th grade
}

People::~People()
{
	free();
}

void People::AddModerator(const char* adminName, const char* modName, int age)
{
	if (strcmp(adminName, admin.GetNickname()))
	{
		std::cerr << "There is no admin with this name!\n";
		return;
	}

	if (NameIsBusy(modName))
	{
		return;
	}

	if (sizeOfModsArr == capacityOfModsArr)
		resizeMods();

	Moderator tmp(modName, age);

	mods[sizeOfModsArr++] = tmp;
	std::cout << admin.GetNickname() << " added moderator " << tmp.GetNickname() << "!\n";
}

void People::RemoveModerator(const char* adminName, const char* modName)
{
	if (strcmp(adminName, admin.GetNickname()))
	{
		std::cerr << "There is no admin with this name!\n";
		return;
	}

	int idx = -1;

	for (int i = 0; i < sizeOfModsArr; ++i)
	{
		if (strcmp(mods[i].GetNickname(), modName) == 0)
		{
			idx = i;
			break;
		}
	}

	if (idx == -1)
	{
		std::cerr << "Moderator " << modName << " doesn't exist!\n";
		return;
	}

	std::cout << admin.GetNickname() << " removed moderator " << mods[idx].GetNickname() << "!\n";

	for (int i = idx; i < sizeOfModsArr-1; ++i)
	{
		mods[i] = mods[i + 1];
	}

	sizeOfModsArr--;
}

void People::AddUser(const char* adminName, const char* userName, int age)
{
	if (strcmp(adminName, admin.GetNickname()))
	{
		std::cerr << "There is no admin with this name!\n";
		return;
	}
	
	if (NameIsBusy(userName))
	{
		return;
	}

	if (sizeOfUsersArr == capacityOfUsersArr)
		resizeUsers();

	User tmp(userName, age);

	users[sizeOfUsersArr++] = tmp;

	std::cout << admin.GetNickname() << " added user " << tmp.GetNickname() << "!\n";
}

void People::RemoveUser(const char* adminName, const char* userName)
{
	if (strcmp(adminName, admin.GetNickname()))
	{
		std::cerr << "There is no admin named " << adminName << "!\n";
		return;
	}

	int idx = -1;

	for (int i = 0; i < sizeOfUsersArr; ++i)
	{
		if (strcmp(users[i].GetNickname(), userName) == 0)
		{
			idx = i;
			break;
		}
	}

	if (idx == -1)
	{
		std::cerr << "User " << userName << " doesn't exist!\n";
		return;
	}

	std::cout << admin.GetNickname() << " removed user " << users[idx].GetNickname() << "!\n";
	
	for (int i = idx; i < sizeOfUsersArr - 1; ++i)
	{
		users[i] = users[i + 1];
	}
	
	sizeOfUsersArr--;
}

void People::Block(const char* blocker, const char* blocked)
{
	bool isModerator = false;
	bool isAdmin = false;

	if (strcmp(blocked, admin.GetNickname()) == 0) // trying to block admin -> not cool
	{
		std::cerr << "Nobody have rights to block the admin!\n";
		return;
	}

	if (!PersonExists(blocker))
	{
		std::cerr << blocker << " doesn't exist!\n";
		return;
	}

	if (!PersonExists(blocked))
	{
		std::cerr << blocked << " doesn't exist!\n";
		return;
	}

	if (strcmp(blocker, admin.GetNickname()) == 0) // if the "blocker" is the admin
	{
		isAdmin = true;
	}
	else // if the "blocker" is moderator
	{
		for (int i = 0; i < sizeOfModsArr; ++i)
		{
			if (strcmp(blocker, mods[i].GetNickname()) == 0)
			{
				isModerator = true;
				break;
			}
		}
	}

	if ((isAdmin == false) && (isModerator == false)) // if "blocker" is user
	{
		std::cerr << blocker << " has no rights to do that!\n";
		return;
	}

	for (int c = 0; c < sizeOfUsersArr; ++c) // if "blocked" is user
	{
		if (strcmp(blocked, users[c].GetNickname()) == 0)
		{
			if (isBlocked(users[c].GetNickname()) == false)
			{
				AddToBlocked(users[c].GetNickname());
				std::cout << "User " << users[c].GetNickname() << " -> blocked!\n";
				return;
			}
			else
			{
				std::cerr << "User " << users[c].GetNickname() << " is already blocked!\n";
				return;
			}
		}
	}

	for (int c = 0; c < sizeOfModsArr; ++c) // if "blocked" is moderator
	{
		if (strcmp(blocked, mods[c].GetNickname()) == 0)
		{
			if (isBlocked(mods[c].GetNickname()) == false)
			{
				AddToBlocked(mods[c].GetNickname());
				std::cout << "Moderator " << mods[c].GetNickname() << " -> blocked!\n";
				return;
			}
			else
			{
				std::cerr << "Moderator " << mods[c].GetNickname() << " is already blocked!\n";
				return;
			}
		}
	}
}

void People::Unblock(const char* unblocker, const char* unblocked)
{
	bool isModerator = false;
	bool isAdmin = false;

	if (strcmp(unblocked, admin.GetNickname()) == 0) // trying to unblock admin
	{
		std::cerr << admin.GetNickname() << " can't be blocked => can't be unblocked!\n";
		return;
	}

	if (!PersonExists(unblocker))
	{
		std::cerr << unblocker << " doesn't exist!\n";
		return;
	}

	if (!PersonExists(unblocked))
	{
		std::cerr << unblocked << " doesn't exist!\n";
		return;
	}

	if (strcmp(unblocker, admin.GetNickname()) == 0) // if the "unblocker" is the admin
	{
		isAdmin = true;
	}
	else // if the "unblocker" is moderator
	{
		for (int i = 0; i < sizeOfModsArr; ++i)
		{
			if (strcmp(unblocker, mods[i].GetNickname()) == 0)
			{
				isModerator = true;
				break;
			}
		}
	}

	if ((isAdmin == false) && (isModerator == false)) // if "unblocker" is user
	{
		std::cerr << unblocker << " has no rights to do that!\n";
		return;
	}

	for (int c = 0; c < sizeOfUsersArr; ++c) // if "unblocked" is user
	{
		if (strcmp(unblocked, users[c].GetNickname()) == 0)
		{
			if (isBlocked(users[c].GetNickname()) == true)
			{
				RemoveFromBlocked(users[c].GetNickname());
				std::cout << "User " << users[c].GetNickname() << " -> unblocked!\n";
				return;
			}
			else
			{
				std::cerr << "User " << users[c].GetNickname() << " is not blocked!\n";
				return;
			}
		}
	}

	for (int c = 0; c < sizeOfModsArr; ++c) // if "unblocked" is moderator
	{
		if (strcmp(unblocked, mods[c].GetNickname()) == 0)
		{
			if (isBlocked(mods[c].GetNickname()) == true)
			{
				RemoveFromBlocked(mods[c].GetNickname());
				std::cout << "Moderator " << mods[c].GetNickname() << " -> unblocked!\n";
				return;
			}
			else
			{
				std::cerr << "Moderator " << mods[c].GetNickname() << " is not blocked!\n";
				return;
			}
		}
	}
}

void People::ChangeNickname(const char* oldNick, const char* newNick)
{	
	if (NameIsBusy(newNick))
	{
		return;
	}

	if (!PersonExists(oldNick))
	{
		std::cerr << "There is no person named " << oldNick << "!\n";
		return;
	}

	if (strcmp(oldNick, admin.GetNickname()) == 0) // check if the old name
	{											   // is the admin's name
		admin.SetNickname(newNick);

		std::cout << oldNick
			<< " changed his name to " 
			<< newNick << "!\n";
		
		return;
	}

	for (int i = 0; i < sizeOfUsersArr; ++i) // check if the old name is among users' names
	{
		if (strcmp(oldNick, users[i].GetNickname()) == 0)
		{
			users[i].SetNickname(newNick);
			
			std::cout << oldNick
				<< " changed his name to " 
				<< newNick << "!\n";
			
			return;
		}
	}
											// check if the old name concides
	for (int i = 0; i < sizeOfModsArr; ++i) // with some moderator's name
	{
		if (strcmp(oldNick, mods[i].GetNickname()) == 0)
		{
			mods[i].SetNickname(newNick);

			std::cout << oldNick
				<< " changed his name to " 
				<< newNick << "!\n";
			
			return;
		}
	}
}

User& People::FindPerson(const char* nickname)
{
	if (strcmp(admin.GetNickname(), nickname) == 0)
	{
		return admin;
	}

	for (int i = 0; i < sizeOfModsArr; ++i)
	{
		if (strcmp(mods[i].GetNickname(), nickname) == 0)
		{
			return mods[i];
		}
	}

	for (int i = 0; i < sizeOfUsersArr; ++i)
	{
		if (strcmp(users[i].GetNickname(), nickname) == 0)
		{
			return users[i];
		}
	}
}

bool People::isModerator(const char* nickname) const
{
	for (int i = 0; i < sizeOfModsArr; ++i)
	{
		if (strcmp(mods[i].GetNickname(), nickname) == 0)
		{
			return true;
		}
	}
	return false;
}

bool People::isAdmin(const char* nickname) const
{
	return (strcmp(admin.GetNickname(), nickname) == 0);
}

bool People::PersonExists(const char* nickname) const
{
	if (strcmp(admin.GetNickname(), nickname) == 0) // if the person is admin
	{
		return true;
	}

	for (int i = 0; i < sizeOfModsArr; ++i) // if the person is moderator
	{
		if (strcmp(mods[i].GetNickname(), nickname) == 0)
		{
			return true;
		}
	}

	for (int i = 0; i < sizeOfUsersArr; ++i) // if the person is user
	{
		if (strcmp(users[i].GetNickname(), nickname) == 0)
		{
			return true;
		}
	}

	return false;
}

bool People::NameIsBusy(const char* nickname) const
{
	if (strcmp(nickname, admin.GetNickname()) == 0) // check if the new name coincides
	{											    // with the admin's name
		std::cerr << "The name " << nickname << " is busy!\n";
		return true;
	}
									// check if the new name
	for (int i = 0; i < sizeOfUsersArr; ++i) // concides with some user's name
	{
		if (strcmp(nickname, users[i].GetNickname()) == 0)
		{
			std::cerr << "The name " << nickname << " is busy!\n";
			return true;
		}
	}
									// check if the new name
	for (int i = 0; i < sizeOfModsArr; ++i) // coincides some moderator's name
	{
		if (strcmp(nickname, mods[i].GetNickname()) == 0)
		{
			std::cerr << "The name " << nickname << " is busy!\n";
			return true;
		}
	}

	return false;
}

bool People::isBlocked(const char* nickname) const
{
	for (int i = 0; i < sizeOfBlockedNamesArr; ++i)
	{
		if (strcmp(nickname, blockedNames[i]) == 0)
		{
			return true;
		}
	}

	return false;
}

const int People::GetSizeOfModsArr() const
{
	return sizeOfModsArr;
}

const int People::GetSizeOfUsersArr() const
{
	return sizeOfUsersArr;
}

const int People::GetSizeOfBlockedNamesArr() const
{
	return sizeOfBlockedNamesArr;
}

void People::printMostActive() const
{
	char name[MAX_NAME_LENGTH] = "";
	int postCount;

	postCount = admin.GetSizeOfIdsArr();
	strncpy(name, admin.GetNickname(), strlen(admin.GetNickname()) + 1);

	for (int i = 0; i < sizeOfUsersArr; ++i)
	{
		if (postCount < users[i].GetSizeOfIdsArr())
		{
			postCount = users[i].GetSizeOfIdsArr();
			strncpy(name, users[i].GetNickname(), strlen(users[i].GetNickname()) + 1);
		}
	}

	for (int i = 0; i < sizeOfModsArr; ++i)
	{
		if (postCount < mods[i].GetSizeOfIdsArr())
		{
			postCount = mods[i].GetSizeOfIdsArr();
			strncpy(name, mods[i].GetNickname(), strlen(mods[i].GetNickname()) + 1);
		}
	}

	std::cout << "Most active -> Name: " << name
		<< ", Posts: " << postCount << std::endl;
}

void People::printYoungest() const
{
	char name[MAX_NAME_LENGTH] = "";
	int minAge = 122; // the oldest person ever 

	for (int i = 0; i < sizeOfUsersArr; ++i)
	{
		if (users[i].GetAge() < minAge)
		{
			minAge = users[i].GetAge();
			strncpy(name, users[i].GetNickname(), strlen(users[i].GetNickname()) + 1);
		}
	}

	for (int i = 0; i < sizeOfModsArr; ++i)
	{
		if (mods[i].GetAge() < minAge)
		{
			minAge = mods[i].GetAge();
			strncpy(name, mods[i].GetNickname(), strlen(mods[i].GetNickname()) + 1);
		}
	}

	std::cout << "Oldest -> Name: " << name
		<< ", Age: " << minAge << std::endl;
}

void People::printOldest() const
{
	char name[MAX_NAME_LENGTH] = "";
	int maxAge = 0;

	for (int i = 0; i < sizeOfUsersArr; ++i)
	{
		if (users[i].GetAge() > maxAge)
		{
			maxAge = users[i].GetAge();
			strncpy(name, users[i].GetNickname(), strlen(users[i].GetNickname()) + 1);
		}
	}

	for (int i = 0; i < sizeOfModsArr; ++i)
	{
		if (mods[i].GetAge() > maxAge)
		{
			maxAge = mods[i].GetAge();
			strncpy(name, mods[i].GetNickname(), strlen(mods[i].GetNickname()) + 1);
		}
	}

	std::cout << "Youngest -> Name: " << name
		<< ", Age: " << maxAge << std::endl;
}

void People::printBlocked() const
{
	for (int i = 0; i < sizeOfBlockedNamesArr; ++i)
	{
		std::cout << blockedNames[i] << ' ';
	}
}

void People::resizeMods()
{
	if (capacityOfModsArr == 0)
		capacityOfModsArr = 1;

	capacityOfModsArr *= 2;
	Moderator *newMods = new(std::nothrow) Moderator[capacityOfModsArr];
	if (!newMods)
	{
		std::cerr << "Not enough memory!\n";
		exit(1);
	}

	for (int i = 0; i < sizeOfModsArr; ++i)
	{
		newMods[i] = mods[i];
	}
	delete[] mods;
	mods = newMods;
}

void People::resizeUsers()
{
	if (capacityOfUsersArr == 0)
		capacityOfUsersArr = 1;

	capacityOfUsersArr *= 2;
	User *newUsers = new(std::nothrow) User[capacityOfUsersArr];
	if (!newUsers)
	{
		std::cerr << "Not enough memory!\n";
		exit(1);
	}

	for (int i = 0; i < sizeOfUsersArr; ++i)
	{
		newUsers[i] = users[i];
	}
	delete[] users;
	users = newUsers;
}

void People::resizeBlocked()
{
	if (capacityOfBLockedNamesArr == 0)
		capacityOfBLockedNamesArr = 1;

	capacityOfBLockedNamesArr *= 2;

	char** newBlockedNames = new(std::nothrow) char*[capacityOfBLockedNamesArr]; // new array from pointers
	if (!newBlockedNames)
	{
		std::cerr << "Could not allocate memory!\n";
		exit(1);
	}

	for (int i = 0; i < sizeOfBlockedNamesArr; ++i) // allocating and copying every char* 
	{
		newBlockedNames[i] = new(std::nothrow) char[strlen(blockedNames[i]) + 1];
		if (!newBlockedNames[i])
		{
			std::cerr << "Could not allocate memory!\n";
			exit(1);
		}

		strncpy(newBlockedNames[i], blockedNames[i], strlen(blockedNames[i]) + 1);
	}

	for (int c = 0; c < sizeOfBlockedNamesArr; ++c)
	{
		delete[] blockedNames[c];
	}
	delete[] blockedNames;

	blockedNames = newBlockedNames;
}

void People::AddToBlocked(const char* nickname)
{
	if (sizeOfBlockedNamesArr == capacityOfBLockedNamesArr)
		resizeBlocked();

	blockedNames[sizeOfBlockedNamesArr] = new(std::nothrow) char[strlen(nickname) + 1]; // allocating memory for
	if (!blockedNames[sizeOfBlockedNamesArr])											// nickname in the array
	{
		std::cerr << "Could not allocate memory!\n";
		exit(1);
	}

	strncpy(blockedNames[sizeOfBlockedNamesArr], nickname, strlen(nickname) + 1);
	sizeOfBlockedNamesArr++;
}

void People::RemoveFromBlocked(const char* nickname)
{
	int idx = -1;
	for (int i = 0; i < sizeOfBlockedNamesArr; ++i) // finding the index of the nickname we want to "unblock"
	{
		if (strcmp(blockedNames[i], nickname) == 0)
		{
			idx = i;
			delete[] blockedNames[i]; // deallocating memory of the nickname
			break;
		}
	}

	for (int c = idx; c < sizeOfBlockedNamesArr - 1; c++)
	{
		blockedNames[c] = blockedNames[c + 1];
	}
	sizeOfBlockedNamesArr--;
}

void People::free()
{
	delete[] mods;
	sizeOfModsArr = 0;
	capacityOfModsArr = 0;

	delete[] users;
	sizeOfUsersArr = 0;
	capacityOfUsersArr = 0;
	
	for (int i = 0; i < sizeOfBlockedNamesArr; ++i) // deleting every one of the elements
	{
		delete[] blockedNames[i];
	}
	delete[] blockedNames; // deleting the pointers
	sizeOfBlockedNamesArr = 0;
	capacityOfBLockedNamesArr = 0;
}

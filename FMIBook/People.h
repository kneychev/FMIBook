#pragma once
#include "Administrator.h"

class People // We don't need copy constructor and assignment operator
{
public:
	People();
	~People();

	void AddModerator(const char* adminName, const char* modName, int age);
	void RemoveModerator(const char* adminName, const char* modName);
	void AddUser(const char* adminName, const char* userName, int age);
	void RemoveUser(const char* adminName, const char* userName);
	void Block(const char* blocker, const char* blocked);
	void Unblock(const char* unblocker, const char* unblocked);
	void ChangeNickname(const char* oldNick, const char* newNick);
	User& FindPerson(const char* nickname);

	bool isModerator(const char* nickname) const;
	bool isAdmin(const char* nickname) const;
	bool PersonExists(const char* nickname) const;
	bool NameIsBusy(const char* nickname) const;
	bool isBlocked(const char* nickname) const;

	const int GetSizeOfModsArr() const;
	const int GetSizeOfUsersArr() const;
	const int GetSizeOfBlockedNamesArr() const;

	void printMostActive() const;
	void printYoungest() const;
	void printOldest() const;
	void printBlocked() const;

private:
	void resizeMods();
	void resizeUsers();
	void resizeBlocked();
	
	void AddToBlocked(const char* nickname);
	void RemoveFromBlocked(const char* nickname);

	void free();

private:
	People(const People&) = delete;
	People& operator=(const People&) = delete;

private:
	Administrator admin;

	Moderator* mods;
	int sizeOfModsArr;
	int capacityOfModsArr;

	User* users;
	int sizeOfUsersArr;
	int capacityOfUsersArr;

	char** blockedNames;
	int sizeOfBlockedNamesArr;
	int capacityOfBLockedNamesArr;
};


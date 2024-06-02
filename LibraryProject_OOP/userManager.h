#pragma once
#include "command_id.h"
#include "user.h"
#include <vector>

/**
Class responsible for handling all user commands in the library system

@brief This class handles all commands related to modifying the user file,
creating, removing and updating user information. (CRUD operations)
*/
class UserManager
{
public:
	UserManager();
	~UserManager();

	Command_ID hashUserCommand(const std::string&) const;
	void userCommands(std::vector<std::string>&);

	void userAdd(std::vector<std::string>&);
	void userRemove(std::vector<std::string>&);
	void usersAll(std::vector<std::string>&) const;

	void loadUsers();
	void saveUsers() const;

	bool isUser() const;
	bool isAdmin() const;
	User* findUser(std::string&) const;
	size_t userPosition(const std::string&) const;
	void printUser(const User*) const;
	bool existUser(const std::string&) const;

	void usersPushBack(User*);
	User* getLoggedUser() const;
	void setLoggedUser(User*);

private:
	/**
	A pointer to the user which is currently logged in
	*/
	User* loggedUser;
	/**
	A vector that holds all the users in the system
	*/
	std::vector<User*> users;
};


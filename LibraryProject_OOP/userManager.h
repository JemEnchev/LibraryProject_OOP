#pragma once
#include "command_id.h"
#include "user.h"
#include <vector>

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

	void printUser(const User*) const;
	bool existUser(const std::string&) const;

	void usersPushBack(User*);
	User* getLoggedUser() const;
	void setLoggedUser(User*);

	bool isAdmin() const;
	bool isUser() const;
	User* findUser(std::string&) const;
	size_t userPosition(const std::string&) const;

	void loadUsers();
	void saveUsers() const;

private:
	User* loggedUser;
	std::vector<User*> users;
};


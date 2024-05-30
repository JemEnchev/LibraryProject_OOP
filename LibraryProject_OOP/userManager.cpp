#include "userManager.h"
#include "messages.h"
#include "helperFunctions.h"
#include <iostream>
#include <fstream>

using namespace HelperFunctions;

UserManager::UserManager()
{
	loggedUser = nullptr;
}

UserManager::~UserManager()
{
	delete loggedUser;

	for (size_t i = 0; i < users.size(); i++)
	{
		delete users[i];
	}
}



Command_ID UserManager::hashUserCommand(const std::string& command) const
{
	if (command == "all")    return Command_ID::_user_all;
	if (command == "add")    return Command_ID::_user_add;
	if (command == "remove") return Command_ID::_user_remove;
	return Command_ID::_error;
}

void UserManager::userCommands(std::vector<std::string>& command)
{
	std::string first = removeFirst(command);

	switch (hashUserCommand(first))
	{
	case _user_all:    usersAll(command);           break;
	case _user_add:    userAdd(command);            break;
	case _user_remove: userRemove(command);         break;
	case _error:       print(CMD_DOESNT_EXIST_MSG); break;
	}
}



void UserManager::userAdd(std::vector<std::string>& command)
{
	if (!checkCommandSize(command, 3)) return;
	if (!isAdmin()) return;

	std::string username = command[0];
	std::string password = command[1];
	bool isAdmin = (command[2] == "1") ? 1 : 0;

	if (existUser(username))
	{
		print(USER_EXISTS_MSG);
		return;
	}

	User* user = new User(username, password, isAdmin);

	users.push_back(user);
	saveUsers();

	print(USER_ADDED_SUCCESSFULLY_MSG);
}

void UserManager::userRemove(std::vector<std::string>& command)
{
	// В случай, че подадем команда: user remove <username> ...something...
	// Или само команда user remove
	if (!checkCommandSize(command, 1)) return;
	if (!isAdmin()) return;

	std::string username = command[0];

	if (!existUser(username))
	{
		print(USER_DOESNT_EXISTS_MSG);
		return;
	}

	if (!confirmation(CFM_USER_REMOVE_MSG))
	{
		std::cin.ignore();
		return;
	}

	users.erase(users.begin() + userPosition(username));
	saveUsers();

	print(USER_REMOVED_SUCCESSFULLY_MSG);
	std::cin.ignore();
}

void UserManager::usersAll(std::vector<std::string>& command) const
{
	if (!checkCommandSize(command, 0)) return;
	if (!isAdmin()) return;

	for (size_t i = 0; i < users.size(); i++)
	{
		std::cout << i + 1 << ". ";
		printUser(users[i]);
	}
}



void UserManager::printUser(const User* user) const
{
	print(user->getUsername());
	print(" ");
	print(user->getPassword());
	print(" ");
	print(user->checkAdmin() ? "Admin" : "User");
	print("\n");
}

bool UserManager::existUser(const std::string& username) const
{
	for (size_t i = 0; i < users.size(); i++)
	{
		if (users[i]->getUsername() == username) return true;
	}
	return false;
}

void UserManager::usersPushBack(User* user)
{
	this->users.push_back(user);
}

User* UserManager::getLoggedUser() const
{
	return this->loggedUser;
}

void UserManager::setLoggedUser(User* user)
{
	this->loggedUser = user;
}



bool UserManager::isAdmin() const
{
	if (loggedUser != nullptr)
	{
		if (loggedUser->checkAdmin())
		{
			return true;
		}
	}

	print(USER_ACCESS_DENIED_MSG);
	return false;
}

bool UserManager::isUser() const
{
	if (loggedUser != nullptr) return true;

	print(USER_NONUSER_ACCESS_DENIED_MSG);
	return false;
}

User* UserManager::findUser(std::string& username) const
{
	for (size_t i = 0; i < users.size(); i++)
	{
		if (users[i]->getUsername() == username) return users[i];
	}
	return nullptr;
}

size_t UserManager::userPosition(const std::string& username) const
{
	if (!existUser(username)) return -1;

	size_t pos = 0;

	for (size_t i = 0; i < users.size(); i++)
	{
		if (users[i]->getUsername() == username)
		{
			pos = i;
			break;
		}
	}

	return pos;
}



void UserManager::loadUsers()
{
	std::ifstream file(USERS_FILE);

	if (!file.is_open())
	{
		print(USER_FILE_FAILED_MSG);
		return;
	}

	std::string line;

	while (std::getline(file, line))
	{
		std::vector<string> parts = divideString(line);
		std::string& username = parts[0];
		std::string& password = parts[1];
		bool isAdmin = (parts[2] == "1") ? 1 : 0;

		if (existUser(username)) continue;

		User* temp = new User(username, password, isAdmin);

		users.push_back(temp);
	}

	file.close();
}

void UserManager::saveUsers() const
{
	std::ofstream file;

	file.open(USERS_FILE, std::ios::out);

	for (size_t i = 0; i < users.size(); i++)
	{
		file << users[i]->getUsername() << " "
			<< users[i]->getPassword() << " "
			<< users[i]->checkAdmin() << std::endl;
	}

	file.close();
}


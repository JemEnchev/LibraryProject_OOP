#include "userManager.h"
#include "messages.h"
#include "helperFunctions.h"
#include <iostream>
#include <fstream>

using namespace HelperFunctions;

/**
Constructor for the user manager class

@brief The constructor initializes the logged user with a nullptr
~~~.cpp
UserManager::UserManager()
{
	loggedUser = nullptr;
}
~~~
*/
UserManager::UserManager()
{
	loggedUser = nullptr;
}

/**
Destructor for the user manager class

@brief Deletes all user pointers in the vector holding them

~~~.cpp
UserManager::~UserManager()
{
	delete loggedUser;

	for (size_t i = 0; i < users.size(); i++)
	{
		delete users[i];
	}
}
~~~
*/
UserManager::~UserManager()
{
	delete loggedUser;

	for (size_t i = 0; i < users.size(); i++)
	{
		delete users[i];
	}
}



/**
Function for hashing the first word of the user input

@brief Depending on the given std::string, the function returns a
specific enum instance which is used later in the bookCommands()
function
@param command String containing the first word of the user input
@returns Returns an instance of the Command_ID enum
*/
Command_ID UserManager::hashUserCommand(const std::string& command) const
{
	if (command == "all")    return Command_ID::user_all;
	if (command == "add")    return Command_ID::user_add;
	if (command == "remove") return Command_ID::user_remove;
	return Command_ID::error;
}

/**
Function for distributing the given command and calling the correct function for it

@brief Accepts as input a std::vector with all the words from the user input command line and based on
the first word, after hashing it, calls the appropriate function to handle the command

@param command std::vector with all the words from the user input
*/
void UserManager::userCommands(std::vector<std::string>& command)
{
	std::string first = removeFirst(command);

	switch (hashUserCommand(first))
	{
	case Command_ID::user_all:    usersAll(command);           break;
	case Command_ID::user_add:    userAdd(command);            break;
	case Command_ID::user_remove: userRemove(command);         break;
	case Command_ID::error:       print(CMD_DOESNT_EXIST_MSG); break;
	}
}



/**
Function for adding a user in the memory

@brief Accepts std::vector which holds the data of the user we
want to add into the memory. Requires admin access.

@param command std::vector containing whats left from the user input
which should be username, password and access level
*/
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

/**
Function for removing a user from the memory

@brief Accepts std::vector which holds the data of the user we
want to remove from the memory. Requires admin access.

@param command std::vector containing whats left from the user input which
should be the username of the user we want to remove
*/
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

/**
Function for displaying all users information

@brief Accepts std::vector which at this point should be empty and then
prints the users in the memory. Required admin access level

@param command std::vector containing whats left from the user input
which should be nothing
*/
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



/**
Function that prints the information of a given user

@brief Accepts a user pointer and prints the information
of the user

@param user Pointer to the user we want to print
*/
void UserManager::printUser(const User* user) const
{
	print(user->getUsername());
	print(" ");
	print(user->getPassword());
	print(" ");
	print(user->checkAdmin() ? "Admin" : "User");
	print("\n");
}

/**
Function that checks if a user with a given username exists

@param username String that holds a user's username
@returns True if a user with the given username exist and False if it doesn't
*/
bool UserManager::existUser(const std::string& username) const
{
	for (size_t i = 0; i < users.size(); i++)
	{
		if (users[i]->getUsername() == username) return true;
	}
	return false;
}

/**
Function for adding a user in the vector which holds them

@param user A pointer to the user we want to add in the vector
*/
void UserManager::usersPushBack(User* user)
{
	this->users.push_back(user);
}



/**
Getter for the currently logged used in the system

@returns Returns a pointer to the currently logged user
*/
User* UserManager::getLoggedUser() const
{
	return this->loggedUser;
}

/**
Setter for the logged user

@param user A pointer to the user that is currently logged in
*/
void UserManager::setLoggedUser(User* user)
{
	this->loggedUser = user;
}



/**
Function that returns if a user is admin

@returns Returns True if the user is admin and
False otherwise
*/
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

/**
Function that returns if a user is not admin

@returns Returns True if the user is not admin and
False otherwise
*/
bool UserManager::isUser() const
{
	if (loggedUser != nullptr) return true;

	print(USER_NONUSER_ACCESS_DENIED_MSG);
	return false;
}

/**
Function for finding a user with a given username

@param username A reference to a string that holds the user's username
@returns Returns a pointer to the user with the given username
*/
User* UserManager::findUser(std::string& username) const
{
	for (size_t i = 0; i < users.size(); i++)
	{
		if (users[i]->getUsername() == username) return users[i];
	}
	return nullptr;
}

/**
Function that finds the index of a user in the vector

@brief Searches the user vector to find the index
of the user with the given username

@param username String that holds a user username
@returns The index of the user in the user vector
*/
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


/**
Function for loading the users in the memory

@brief Reads the information in the user.txt file and
loads in the system memory
*/
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
		std::vector<std::string> parts = divideString(line);
		std::string& username = parts[0];
		std::string& password = parts[1];
		bool isAdmin = (parts[2] == "1") ? 1 : 0;

		if (existUser(username)) continue;

		User* temp = new User(username, password, isAdmin);

		users.push_back(temp);
	}

	file.close();
}

/**
Function for saving the users in the user.txt file

@brief Writes the information from the system memory
in the user.txt file 
*/
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


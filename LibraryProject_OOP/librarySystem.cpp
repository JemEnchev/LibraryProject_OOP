#include "librarySystem.h"
#include "messages.h"
#include <iostream>
#include <fstream>

LibrarySystem::LibrarySystem()
{
	loadUsers();

	if (users.empty())
	{
		User* admin = new User("admin", "i<3c++", true);
		users.push_back(admin);
	}
}

LibrarySystem::~LibrarySystem()
{
	delete loggedUser;
}

void LibrarySystem::start()
{
	loadUsers();

	print(START_MSG);
	std::string command;

	while (true)
	{
		print("> ");
		std::getline(std::cin, command);

		executeCommand(command);
		//std::cin.ignore();
	}

}

void LibrarySystem::login(std::vector<std::string>& command)
{
	if (!checkCommandSize(command, 0)) return;

	if (loggedUser != nullptr)
	{
		print(USER_ALREADY_LOGGED_MSG);
		return;
	}
		
	std::string username, password;

	print(LOGIN_USERNAME_MSG);
	std::cin >> username;

	print(LOGIN_PASSWORD_MSG);
	std::cin >> password;

	if (existUser(username) && findUser(username)->getPassword() == password)
	{
		loggedUser = findUser(username);

		std::cout << USER_LOGGED_SUCCESSFULLY_MSG << username << '!' << std::endl;
		std::cin.ignore();
		return;
	}

	print(USER_LOGGED_FAILED_MSG);
	std::cin.ignore();
	return;
}

void LibrarySystem::logout()
{
	if (loggedUser == nullptr)
	{
		print(USER_NULL_LOGOUT_MSG);
		return;
	}

	loggedUser = nullptr;
	print(USER_LOGOUT_MSG);
}

void LibrarySystem::open(const std::string& file)
{

}

void LibrarySystem::close()
{

}

void LibrarySystem::save()
{

}

void LibrarySystem::saveas(const std::string& file)
{

}

void LibrarySystem::help() const
{
	print("\n");
	print(HELP_MENU_MSG);
	print(HELP_DISCL_1_MSG);
	print(HELP_DISCL_2_MSG);
	print(HELP_DISCL_3_MSG);
	print(HELP_LOGIN_MSG);
	print(HELP_LOGOUT_MSG);
	print(HELP_OPEN_MSG);
	print(HELP_CLOSE_MSG);
	print(HELP_SAVE_MSG);
	print(HELP_SAVEAS_MSG);
	print(HELP_EXIT_MSG);
	print(HELP_BOOKS_VIEW_MSG);
	print(HELP_BOOKS_ALL_MSG);
	print(HELP_BOOKS_FIND_MSG);
	print(HELP_BOOKS_SORT_MSG);
	print(HELP_HELP_MSG);

	if (loggedUser != nullptr && loggedUser->checkAdmin())
	{
		print("\n");
		print(HELP_BOOK_INFO_MSG);
		print(HELP_BOOK_ADD_MSG);
		print(HELP_BOOK_RMV_MSG);
		print(HELP_USER_ADD_MSG);
		print(HELP_USER_RMV_MSG);
	}
	print("\n");
}

void LibrarySystem::quit() const
{
	if (confirmation(CFM_EXIT_MSG))
	{
		saveUsers();
		exit(0);
	}
	std::cin.ignore();
}

void LibrarySystem::print(const std::string& message) const
{
	std::cout << message;
}



void LibrarySystem::executeCommand(const std::string& command)
{
	if (command.empty())
	{
		print(CMD_DOESNT_EXIST_MSG);
		return;
	}
	std::vector<std::string> parts = divideString(command);
	std::string first_command = parts[0];
	parts.erase(parts.begin());

	switch (hashCommand(first_command))
	{
	case _open:   open(parts[0]);              break;
	case _close:  close();                     break;
	case _save:   save();                      break;
	case _saveas: saveas(parts[0]);            break;
	case _help:   help();                      break;
	case _login:  login(parts);                break;
	case _logout: logout();                    break;
	case _quit:   quit();                      break;
	case _books:  bookCommands(parts);         break;
	case _users:  userCommands(parts);         break;
	case _error:  print(CMD_DOESNT_EXIST_MSG); break;
	}
}

void LibrarySystem::userCommands(std::vector<std::string>& command)
{
	if (command.empty())
	{
		print(CMD_DOESNT_EXIST_MSG);
		return;
	}

	std::string first = command[0];
	command.erase(command.begin());
	
	switch (hashUserCommand(first))
	{
	case _all:        usersAll(command);          break;
	case _add:        userAdd(command);           break;
	case _remove:     userRemove(command);        break;
	case _user_error: print(CMD_DOESNT_EXIST_MSG); break;
	}
}

void LibrarySystem::bookCommands(std::vector<std::string>& command)
{

}



void LibrarySystem::booksView() const
{
}

void LibrarySystem::booksAll() const
{
}

void LibrarySystem::booksFind() const
{
}

void LibrarySystem::booksSort() const
{
}

void LibrarySystem::bookInfo() const
{
}

void LibrarySystem::bookAdd()
{
}

void LibrarySystem::bookRemove()
{
}


void LibrarySystem::userAdd(std::vector<std::string>& command)
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

	print(USER_ADDED_SUCCESSFULLY_MSG);
}

void LibrarySystem::userRemove(std::vector<std::string>& command)
{
	// В случай, че подадем команда: user remove <username> ...something...
	// Или само команда user remove
	if (!checkCommandSize(command, 1)) return;
	if (!isAdmin()) return;

	if (!confirmation(CFM_USER_REMOVE_MSG)) return;

	std::string username = command[0];

	if (!existUser(username))
	{
		print(USER_DOESNT_EXISTS_MSG);
		return;
	}

	users.erase(users.begin() + userPosition(username));
	print(USER_REMOVED_SUCCESSFULLY_MSG);
}

void LibrarySystem::usersAll(std::vector<std::string>& command) const
{
	if (!checkCommandSize(command, 0)) return;
	if (!isAdmin()) return;

	for (size_t i = 0; i < users.size(); i++)
	{
		std::cout << i + 1 << ". ";
		print(users[i]->getUsername());
		print(" ");
		print(users[i]->getPassword());
		print(" ");
		print(users[i]->checkAdmin() ? "Admin" : "User");
		print("\n");
	}
}


bool LibrarySystem::confirmation(const std::string& question) const
{
	print(question);
	char input;
	std::cin >> input;

	while (input != 'y' && input != 'Y' &&
		input != 'n' && input != 'N')
	{
		print(CFM_WRONG_MSG);
		print(question);
		std::cin >> input;
	}

	if (input == 'y' || input == 'Y') return true;

	return false;
}

//bool LibrarySystem::contains(const std::vector<std::string>& vector, const std::string& key) const
//{
//	if (vector.empty()) return false;
//
//	for (size_t i = 0; i < vector.size(); i++)
//	{
//		if (vector[i] == key) return true;
//	}
//	return false;
//}

bool LibrarySystem::existUser(const std::string& username) const
{
	for (size_t i = 0; i < users.size(); i++)
	{
		if (users[i]->getUsername() == username) return true;
	}
	return false;
}

bool LibrarySystem::isAdmin() const
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

User* LibrarySystem::findUser(std::string& username) const
{
	for (size_t i = 0; i < users.size(); i++)
	{
		if (users[i]->getUsername() == username) return users[i];
	}
	return nullptr;
}

size_t LibrarySystem::userPosition(const std::string& username) const
{
	if (!existUser(username)) return 0;
	
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

std::vector<std::string> LibrarySystem::divideString(const std::string& command) const
{
	// Ако преди командата има празни места
	size_t start = 0;
	while (true)
	{
		if (command[start] != ' ') break;
		start++;
	}

	if (start + 1 == command.size())
	{
		print(CMD_DOESNT_EXIST_MSG);
		std::vector<std::string> empty = {};
		return empty;
	}

	std::vector<std::string> parts;
	std::string temp;

	for (size_t i = start; i < command.size(); i++)
	{
		// Проверяваме дали думата е свършила
		if (command[i] != ' ')
		{
			temp.push_back(command[i]);

			// Проверяваме дали сме до последния символ и вкарваме събраното дотук във вектора
			// По този начин не губим последната дума
			if (i + 1 == command.size())
			{
				parts.push_back(temp);
			}
			continue;
		}

		// Пъхаме сглобената дума във вектора и чистим временната
		parts.push_back(temp);
		temp.clear();
	}

	// Връщаме вектора
	return parts;
}

bool LibrarySystem::checkCommandSize(std::vector<std::string>& command, size_t size) const
{
	if (command.size() == size) return true;
	
	print(CMD_DOESNT_EXIST_MSG);
	return false;
}

void LibrarySystem::loadUsers()
{
	std::ifstream file(USERS_FILE);

	if (!file.is_open())
	{
		//print(USER_FILE_FAILED_MSG);
		return;
	}

	std::string line;

	while (std::getline(file, line))
	{
		//if (line.empty()) return;

		std::vector<string> parts = divideString(line);
		std::string username = parts[0];
		std::string password = parts[1];
		bool isAdmin = (parts[2] == "1") ? 1 : 0;

		if (existUser(username)) continue;

		User* temp = new User(username, password, isAdmin);

		users.push_back(temp);
	}

	file.close();
}

void LibrarySystem::saveUsers() const
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

void LibrarySystem::saveBooks() const
{

}

Command_ID LibrarySystem::hashCommand(const std::string& command) const
{
	if (command == "open")   return Command_ID::_open;
	if (command == "close")  return Command_ID::_close;
	if (command == "save")   return Command_ID::_save;
	if (command == "saveas") return Command_ID::_saveas;
	if (command == "help")   return Command_ID::_help;
	if (command == "login")  return Command_ID::_login;
	if (command == "logout") return Command_ID::_logout;
	if (command == "exit")   return Command_ID::_quit;
	if (command == "users" || command == "user")  return Command_ID::_users;
	if (command == "books" || command == "book") return Command_ID::_books;
	return Command_ID::_error;
}

User_Command_ID LibrarySystem::hashUserCommand(const std::string& command) const
{
	if (command == "all")    return User_Command_ID::_all;
	if (command == "add")    return User_Command_ID::_add;
	if (command == "remove") return User_Command_ID::_remove;
	return User_Command_ID::_user_error;
}

Book_Command_ID LibrarySystem::hashBookCommand(const std::string& command) const
{
	return Book_Command_ID();
}

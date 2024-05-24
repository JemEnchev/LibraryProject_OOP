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
	}

}

void LibrarySystem::login()
{
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

	if (!existUser(username))
	{
		print(USER_LOGGED_FAILED_MSG);
		return;
	}

	loggedUser = findUser(username);

	std::cout << USER_LOGGED_SUCCESSFULLY_MSG << username << '!' << std::endl;

}

void LibrarySystem::logout()
{
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

	if (loggedUser != nullptr)
	{
		if (loggedUser->checkAdmin())
		{
			print("\n");
			print(HELP_BOOK_INFO_MSG);
			print(HELP_BOOK_ADD_MSG);
			print(HELP_BOOK_RMV_MSG);
			print(HELP_USER_ADD_MSG);
			print(HELP_USER_RMV_MSG);
		}
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
}

void LibrarySystem::print(const std::string& message) const
{
	std::cout << message;
}

void LibrarySystem::bookCommands(const std::vector<std::string>& commands)
{

}

void LibrarySystem::userCommands(const std::vector<std::string>& commands)
{
	if (commands.size() < 2)
	{
		print(CMD_DOESNT_EXIST_MSG);
		return;
	}

	std::string first = commands[0];
	std::string username = commands[1];
	
	if (first == "add")
	{
		if (commands.size() < 4)
		{
			print(CMD_DOESNT_EXIST_MSG);
			return;
		}

		std::string password = commands[2];
		bool isAdmin = (commands[3] == "1") ? 1 : 0;

		userAdd(username, password, isAdmin);
		return;
	}

	if (first == "remove")
	{
		userRemove(username);
	}
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

void LibrarySystem::userAdd(const std::string& username, const std::string& password, bool isAdmin)
{
	if (existUser(username))
	{
		print(USER_EXISTS_MSG);
		return;
	}

	User user(username, password, isAdmin);

	users.push_back(&user);
}

void LibrarySystem::userRemove(const std::string& username)
{

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

	switch (hash(first_command))
	{
	case _open  : open(parts[0]);              break;
	case _close : close();                     break;
	case _save  : save();                      break;
	case _saveas: saveas(parts[0]);            break;
	case _help  : help();                      break;
	case _login : login();                     break;
	case _logout: logout();                    break;
	case _quit  : quit();                      break;
	case _books : bookCommands(parts);         break;
	case _users : userCommands(parts);         break;
	case _error : print(CMD_DOESNT_EXIST_MSG); break;
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

bool LibrarySystem::contains(const std::vector<std::string>& vector, const std::string& key) const
{
	if (vector.empty()) return false;

	for (size_t i = 0; i < vector.size(); i++)
	{
		if (vector[i] == key) return true;
	}
	return false;
}

bool LibrarySystem::existUser(const std::string& username) const
{
	for (size_t i = 0; i < users.size(); i++)
	{
		if (users[i]->getUsername() == username) return true;
	}
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

void LibrarySystem::loadUsers()
{
	std::ifstream file(USERS_FILE);

	if (!file.is_open())
	{
		print(USER_FILE_FAILED_MSG);
		return;
	}

	std::string line;

	if (line.empty()) return;

	while (std::getline(file, line))
	{
		std::vector<string> parts = divideString(line);
		std::string username = parts[0];
		std::string password = parts[1];
		bool isAdmin = (parts[2] == "1") ? 1 : 0;

		if (existUser(username)) continue;

		User temp(username, password, isAdmin);

		users.push_back(&temp);
	}

	file.close();
}

void LibrarySystem::saveUsers() const
{
	std::ofstream file;

	file.open(USERS_FILE);
	
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

Command_ID LibrarySystem::hash(const std::string& command) const
{
	if (command == "open") return Command_ID::_open;
	if (command == "close") return Command_ID::_close;
	if (command == "save") return Command_ID::_save;
	if (command == "saveas") return Command_ID::_saveas;
	if (command == "help") return Command_ID::_help;
	if (command == "login") return Command_ID::_login;
	if (command == "logout") return Command_ID::_logout;
	if (command == "exit") return Command_ID::_quit;
	if (command == "users") return Command_ID::_users;
	if (command == "books" || command == "book") return Command_ID::_books;
	else return _error;
}

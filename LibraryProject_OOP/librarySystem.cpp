#include "librarySystem.h"
#include "messages.h"
#include <iostream>

LibrarySystem::LibrarySystem()
{
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

	std::cout << START_MSG << std::endl;
	std::string command;

	while (true)
	{
		std::cout << "> ";
		std::getline(std::cin, command);
		executeCommand(command);
	}

}

void LibrarySystem::login()
{
	if (loggedUser != nullptr) std::cout << USER_ALREADY_LOGGED_MSG << std::endl;

	std::string username, password;

	std::cout << LOGIN_USERNAME_MSG;
	std::cin >> username;

	std::cout << LOGIN_PASSWORD_MSG;
	std::cin >> password;

	if (!existUser(users, username))
	{
		std::cout << USER_LOGGED_FAILED_MSG << std::endl;
		return;
	}

	loggedUser = findUser(username);

	std::cout << USER_LOGGED_SUCCESSFULLY_MSG << username << '!' << std::endl;

}

void LibrarySystem::logout()
{
	loggedUser = nullptr;

	std::cout << USER_LOGOUT_MSG << std::endl;
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
	std::cout << '\n';
	std::cout << HELP_MENU_MSG << std::endl;
	std::cout << HELP_DISCL_1_MSG << std::endl;
	std::cout << HELP_DISCL_2_MSG << std::endl;
	std::cout << HELP_DISCL_3_MSG << std::endl;
	std::cout << HELP_LOGIN_MSG << std::endl;
	std::cout << HELP_LOGOUT_MSG << std::endl;
	std::cout << HELP_OPEN_MSG << std::endl;
	std::cout << HELP_CLOSE_MSG << std::endl;
	std::cout << HELP_SAVE_MSG << std::endl;
	std::cout << HELP_SAVEAS_MSG << std::endl;
	std::cout << HELP_EXIT_MSG << std::endl;
	std::cout << HELP_BOOKS_VIEW_MSG << std::endl;
	std::cout << HELP_BOOKS_ALL_MSG << std::endl;
	std::cout << HELP_BOOKS_FIND_MSG << std::endl;
	std::cout << HELP_BOOKS_SORT_MSG << std::endl;
	std::cout << HELP_HELP_MSG << std::endl;

	if (loggedUser != nullptr)
	{
		if (loggedUser->checkAdmin())
		{
			std::cout << '\n';
			std::cout << HELP_BOOK_INFO_MSG << std::endl;
			std::cout << HELP_BOOK_ADD_MSG << std::endl;
			std::cout << HELP_BOOK_RMV_MSG << std::endl;
			std::cout << HELP_USER_ADD_MSG << std::endl;
			std::cout << HELP_USER_RMV_MSG << std::endl;
		}
	}
	std::cout << '\n';
}

void LibrarySystem::quit() const
{
	if (confirmation(CFM_EXIT_MSG))
	{
		exit(0);
	}
}

void LibrarySystem::error() const
{
	std::cout << CMD_DOESNT_EXIST_MSG << std::endl;
}

void LibrarySystem::bookCommands(const std::vector<std::string>& commands) const
{

}

void LibrarySystem::userCommands(const std::vector<std::string>& commands) const
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

void LibrarySystem::userAdd()
{
}

void LibrarySystem::userRemove()
{
}

void LibrarySystem::executeCommand(const std::string& command)
{
	if (command.empty())
	{
		error();
		return;
	}
	std::vector<std::string> parts = divideCommand(command);
	std::string first_command = parts[0];
	parts.erase(parts.begin());

	switch (hash(first_command))
	{
	case _open  : open(parts[0]);      break;
	case _close : close();             break;
	case _save  : save();              break;
	case _saveas: saveas(parts[0]);    break;
	case _help  : help();              break;
	case _login : login();             break;
	case _logout: logout();            break;
	case _quit  : quit();              break;
	case _books : bookCommands(parts); break;
	case _users : userCommands(parts); break;
	case _error : error();             break;
	}
}

bool LibrarySystem::confirmation(const std::string& question) const
{
	std::cout << question;
	char input;
	std::cin >> input;

	while (input != 'y' && input != 'Y' &&
		input != 'n' && input != 'N')
	{
		std::cout << CFM_WRONG_MSG << std::endl;
		std::cout << question;
		std::cin >> input;
	}

	if (input == 'y' || input == 'Y') return true;

	return false;
}

bool LibrarySystem::contains(const std::vector<std::string>& vector, const std::string& key) const
{
	for (size_t i = 0; i < vector.size(); i++)
	{
		if (vector[i] == key) return true;
	}
	return false;
}

bool LibrarySystem::existUser(const std::vector<User*>& users, const std::string& username) const
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

std::vector<std::string> LibrarySystem::divideCommand(const std::string& command) const
{
	// Ако преди командата има празни места
	size_t start = 0;
	while (true)
	{
		if (command[start] != ' ') break;
		start++;
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

}

void LibrarySystem::loadBooks()
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

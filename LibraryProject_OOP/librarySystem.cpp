#include "librarySystem.h"
#include "messages.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include "helperFunctions.h"

using namespace HelperFunctions;


LibrarySystem::LibrarySystem() : book_manager(user_manager)
{
	user_manager.loadUsers();

	if (!user_manager.existUser("admin"))
	{
		User* admin = new User("admin", "i<3c++", true);
		user_manager.usersPushBack(admin);
	}
}

void LibrarySystem::start()
{
	user_manager.loadUsers();

	print(START_MSG);
	std::string command;

	while (true)
	{
		print("> ");
		std::getline(std::cin, command);

		executeCommand(command);
	}

}

void LibrarySystem::login(std::vector<std::string>& command)
{
	if (!checkCommandSize(command, 0)) return;

	if (user_manager.getLoggedUser() != nullptr)
	{
		print(USER_ALREADY_LOGGED_MSG);
		return;
	}

	std::string username, password;

	print(LOGIN_USERNAME_MSG);
	std::cin >> username;

	
	print(LOGIN_PASSWORD_MSG);

	int ch;

	while (true) 
	{
		ch = _getch();

		if (ch == '\r' || ch == '\n') break;
		
		if (ch == 8) // ascii code 8 -> backsapce
		{
			if (!password.empty())
			{
				print("\b \b");
				password.pop_back();
			}
			continue;
		}
		
		password.push_back(ch);
		print(PASSWORD_SYMBOL);
	}

	print("\n");

	if (user_manager.existUser(username) && user_manager.findUser(username)->getPassword() == password)
	{
		user_manager.setLoggedUser(user_manager.findUser(username));

		std::cout << USER_LOGGED_SUCCESSFULLY_MSG << username << '!' << std::endl;
		std::cin.ignore();
		return;
	}

	print(USER_LOGGED_FAILED_MSG);
	std::cin.ignore();
	return;
}

void LibrarySystem::logout(std::vector<std::string>& command)
{
	if (!checkCommandSize(command, 0)) return;

	if (user_manager.getLoggedUser() == nullptr)
	{
		print(USER_NULL_LOGOUT_MSG);
		return;
	}

	user_manager.setLoggedUser(nullptr);
	print(USER_LOGOUT_MSG);
}

void LibrarySystem::open(std::vector<std::string>& command)
{
	if (!checkCommandSize(command, 1)) return;

	std::string file_name = removeFirst(command);
	std::ifstream file(file_name);

	if (!file.is_open())
	{
		if (user_manager.getLoggedUser() == nullptr || !user_manager.getLoggedUser()->checkAdmin())
		{
			print(FILE_DOESNT_EXIST_MSG);
			return;
		}

		std::ofstream temp(file_name);
		temp.close();

		file.open(file_name);

		if (!file.is_open())
		{
			print(FILE_FAILED_MSG);
			return;
		}
	}

	book_manager.setOpenedFile(file_name);

	std::vector<std::string> parts;
	std::string line;

	while (std::getline(file, line))
	{
		std::string holder;

		for (size_t i = 0; i < line.size(); i++)
		{
			if (line[i] == '~')
			{
				parts.push_back(holder);
				holder.clear();
				i += 2;
			}

			holder.push_back(line[i]);
		}
		parts.push_back(holder);

		// Id ~ Title ~ Author ~ Genre ~ Year ~ Rating ~ Keywords ~ Description

		int id = stoi(parts[0]);
		if (book_manager.existBook(id)) continue;

		string title = parts[1];
		string author = parts[2];
		string genre = parts[3];
		int year = stoi(parts[4]);
		float rating = stof(parts[5]);
		std::vector<std::string> keywords = divideString(parts[6]);
		std::string description = parts[7];
		parts.clear();

		Book* book = new Book(title, author, genre, description, keywords, id, year, rating);

		book_manager.booksPushBack(book);
	}

	file.close();

	print(FILE_OPENED_MSG);
	print(FILE_LOADED_COUNT_MSG);
	std::cout << book_manager.getBooks().size() << std::endl;
}

void LibrarySystem::close(std::vector<std::string>& command)
{
	if (!checkCommandSize(command, 0)) return;

	if (book_manager.getOpenedFile().empty())
	{
		print(FILE_NOTHING_TO_CLOSE_MSG);
		return;
	}

	book_manager.clearBooks();
	book_manager.setOpenedFile("");

	if (!confirmation(CFM_FILE_CLOSE_MSG)) return;

	print(FILE_CLOSED_MSG);
	std::cin.ignore();
}
// admin
void LibrarySystem::save(std::vector<std::string>& command)
{
	if (!checkCommandSize(command, 0)) return;
	if (!user_manager.isAdmin()) return;

	if (book_manager.getOpenedFile().empty())
	{
		print(FILE_NOTHING_TO_SAVE_MSG);
		return;
	}

	if (!confirmation(CFM_BOOK_SAVE_MSG)) return;

	std::ofstream file;

	file.open(book_manager.getOpenedFile(), std::ios::out);

	// Id ~ Title ~ Author ~ Genre ~ Year ~ Rating ~ Keywords ~ Description
	for (size_t i = 0; i < book_manager.getBooks().size(); i++)
	{
		Book* book = book_manager.getBooks()[i];
		file << book->getId() << "~ "
			<< book->getTitle() << "~ "
			<< book->getAuthor() << "~ "
			<< book->getGenre() << "~ "
			<< book->getYear() << "~ "
			<< book->getRating() << "~ ";

		std::vector<std::string> keywords = book->getKeywords();
		for (size_t j = 0; j < keywords.size(); j++)
		{
			file << keywords[j] << " ";
		}

		file << "~ " << book->getDescription() << std::endl;
	}

	file.close();

	print(FILE_SAVED_MSG);
	std::cin.ignore();
}
// admin
void LibrarySystem::saveas(std::vector<std::string>& command)
{
	if (!checkCommandSize(command, 1)) return;
	if (!user_manager.isAdmin()) return;

	if (book_manager.getOpenedFile().empty())
	{
		print(FILE_NOTHING_TO_SAVE_MSG);
		return;
	}

	std::string file_name = removeFirst(command);

	std::ifstream check(file_name);

	if (check.is_open())
	{
		print(FILE_ALREADY_EXISTS_MSG);
		check.close();
		return;
	}

	check.close();

	std::string curr_file = book_manager.getOpenedFile();
	book_manager.setOpenedFile(file_name);

	save(command);

	book_manager.setOpenedFile(curr_file);
}

void LibrarySystem::help(std::vector<std::string>& command) const
{
	if (!checkCommandSize(command, 0)) return;

	print("\n");
	print(HELP_MENU_MSG);
	print(HELP_DISCL_1_MSG);
	print(HELP_DISCL_2_MSG);
	print(HELP_DISCL_3_MSG);
	print(HELP_LOGIN_MSG);
	print(HELP_LOGOUT_MSG);
	print(HELP_OPEN_MSG);
	print(HELP_CLOSE_MSG);
	print(HELP_EXIT_MSG);
	print(HELP_BOOKS_VIEW_MSG);
	print(HELP_BOOKS_ALL_MSG);
	print(HELP_BOOKS_FIND_MSG);
	print(HELP_BOOKS_SORT_MSG);
	print(HELP_HELP_MSG);

	if (user_manager.getLoggedUser() != nullptr && user_manager.getLoggedUser()->checkAdmin())
	{
		print("\n");
		print(HELP_SAVE_MSG);
		print(HELP_SAVEAS_MSG);
		print(HELP_BOOK_INFO_MSG);
		print(HELP_USER_RMV_MSG);
		print(HELP_USER_ADD_MSG);
		print(HELP_BOOK_RMV_MSG);
		print(HELP_BOOK_ADD_MSG);
	}
	print("\n");
}

void LibrarySystem::quit(std::vector<std::string>& command) const
{
	if (!checkCommandSize(command, 0)) return;

	if (confirmation(CFM_EXIT_MSG))
	{
		exit(0);
	}
	std::cin.ignore();
}



void LibrarySystem::executeCommand(std::string& command_line)
{
	if (command_line.empty()) return; 

	std::vector<std::string> command = divideString(command_line);

	std::string first = removeFirst(command);

	switch (hashCommand(first))
	{
	case _open:   open(command);               break;
	case _close:  close(command);              break;
	case _save:   save(command);               break;
	case _saveas: saveas(command);             break;
	case _help:   help(command);               break;
	case _login:  login(command);              break;
	case _logout: logout(command);             break;
	case _quit:   quit(command);               break;
	case _books:  book_manager.bookCommands(command);       break;
	case _users:  user_manager.userCommands(command);       break;
	case _error:  print(CMD_DOESNT_EXIST_MSG); break;
	}
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

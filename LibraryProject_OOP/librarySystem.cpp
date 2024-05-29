﻿#include "librarySystem.h"
#include "messages.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include "helperFunctions.h"

using namespace HelperFunctions;


LibrarySystem::LibrarySystem()
{
	user_manager.loadUsers();

	if (!user_manager.existUser("admin"))
	{
		User* admin = new User("admin", "i<3c++", true);
		user_manager.usersPushBack(admin);
	}
}

LibrarySystem::~LibrarySystem()
{
	for (size_t i = 0; i < books.size(); i++)
	{
		delete books[i];
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

	openedFile = file_name;

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
		if (existBook(id)) continue;

		string title = parts[1];
		string author = parts[2];
		string genre = parts[3];
		int year = stoi(parts[4]);
		float rating = stof(parts[5]);
		std::vector<std::string> keywords = divideString(parts[6]);
		std::string description = parts[7];
		parts.clear();

		Book* book = new Book(title, author, genre, description, keywords, id, year, rating);

		books.push_back(book);
	}

	file.close();

	print(FILE_OPENED_MSG);
	print(FILE_LOADED_COUNT_MSG);
	std::cout << books.size() << std::endl;
}

void LibrarySystem::close(std::vector<std::string>& command)
{
	if (!checkCommandSize(command, 0)) return;

	if (openedFile.empty())
	{
		print(FILE_NOTHING_TO_CLOSE_MSG);
		return;
	}

	books.clear();
	openedFile.clear();

	if (!confirmation(CFM_FILE_CLOSE_MSG)) return;

	print(FILE_CLOSED_MSG);
	std::cin.ignore();
}
// admin
void LibrarySystem::save(std::vector<std::string>& command)
{
	if (!checkCommandSize(command, 0)) return;
	if (!user_manager.isAdmin()) return;

	if (openedFile.empty())
	{
		print(FILE_NOTHING_TO_SAVE_MSG);
		return;
	}

	if (!confirmation(CFM_BOOK_SAVE_MSG)) return;

	std::ofstream file;

	file.open(openedFile, std::ios::out);

	// Id ~ Title ~ Author ~ Genre ~ Year ~ Rating ~ Keywords ~ Description
	for (size_t i = 0; i < books.size(); i++)
	{
		file << books[i]->getId() << "~ "
			<< books[i]->getTitle() << "~ "
			<< books[i]->getAuthor() << "~ "
			<< books[i]->getGenre() << "~ "
			<< books[i]->getYear() << "~ "
			<< books[i]->getRating() << "~ ";

		std::vector<std::string> keywords = books[i]->getKeywords();
		for (size_t j = 0; j < keywords.size(); j++)
		{
			file << keywords[j] << " ";
		}

		file << "~ " << books[i]->getDescription() << std::endl;
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

	if (openedFile.empty())
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

	std::string curr_file = openedFile;
	openedFile = file_name;

	save(command);

	openedFile = curr_file;
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
	case _books:  bookCommands(command);       break;
	case _users:  user_manager.userCommands(command);       break;
	case _error:  print(CMD_DOESNT_EXIST_MSG); break;
	}
}

void LibrarySystem::bookCommands(std::vector<std::string>& command)
{
	std::string first = removeFirst(command); 

	switch (hashBookCommand(first))
	{
	case _book_all:    booksAll(command);     break;
	case _book_add:    bookAdd(command);      break;
	case _book_remove: bookRemove(command);   break;
	case _book_view:   booksView(command);    break;
	case _book_find:   booksFind(command);    break;
	case _book_sort:   booksSort(command);    break;
	case _book_info:   bookInfo(command);     break;
	case _error: print(CMD_DOESNT_EXIST_MSG); break;
	}
}


// non user
void LibrarySystem::booksView(std::vector<std::string>& command) const
{
	if (!checkCommandSize(command, 0)) return;

	if (books.empty())
	{
		print(FILE_NOT_LOADED_MSG);
		return;
	}

	for (size_t i = 0; i < books.size(); i++)
	{
		print(DIVIDER);
		print(BOOK_TITLE_PRINT_MSG);
		print(books[i]->getTitle());
		print("\n");

		print(BOOK_AUTHOR_PRINT_MSG);
		print(books[i]->getAuthor());
		print("\n");
	}

	print(DIVIDER);
	print(FILE_LOADED_COUNT_MSG);
	std::cout << books.size();
	print("\n");
}
// non user
void LibrarySystem::booksAll(std::vector<std::string>& command) const
{
	if (!checkCommandSize(command, 0)) return;

	if (books.empty())
	{
		print(FILE_NOT_LOADED_MSG);
		return;
	}

	for (size_t i = 0; i < books.size(); i++)
	{
		print(DIVIDER);
		printBook(books[i]);
	}

	print(DIVIDER);
	print(FILE_LOADED_COUNT_MSG);
	std::cout << books.size();
	print("\n");
}
// user
void LibrarySystem::booksFind(std::vector<std::string>& command) const
{
	if (command.size() < 2)
	{
		print(CMD_DOESNT_EXIST_MSG);
		return;
	}

	if (!user_manager.isUser()) return;
	if (openedFile.empty())
	{
		print(FILE_NOT_LOADED_MSG);
		return;
	}

	std::string criteria = removeFirst(command);
	std::string key;
	size_t counter = 0;

	for (size_t i = 0; i < command.size(); i++)
	{
		for (size_t j = 0; j < command[i].size(); j++)
		{
			key.push_back(command[i][j]);
		}

		if (i + 1 != command.size())
		{
			key.push_back(' ');
		}
	}

	if (criteria == "title")
	{
		for (size_t i = 0; i < books.size(); i++)
		{
			if ((toLower(books[i]->getTitle()).find(toLower(key))) != string::npos)
			{
				print(DIVIDER);
				printBook(books[i]);
				counter++;
			}
		}
		print(DIVIDER);
		print(BOOK_FIND_COUNTER_MSG);
		std::cout << counter << std::endl;
		print(DIVIDER);
		print("\n");
		return;
	}

	if (criteria == "author")
	{
		for (size_t i = 0; i < books.size(); i++)
		{
			if ((toLower(books[i]->getAuthor()).find(toLower(key))) != string::npos)
			{
				print(DIVIDER);
				printBook(books[i]);
				counter++;
			}
		}
		print(DIVIDER);
		print(BOOK_FIND_COUNTER_MSG);
		std::cout << counter << std::endl;
		print(DIVIDER);
		print("\n");
		return;
	}

	if (criteria == "genre")
	{
		for (size_t i = 0; i < books.size(); i++)
		{
			if ((toLower(books[i]->getGenre()).find(toLower(key))) != string::npos)
			{
				print(DIVIDER);
				printBook(books[i]);
				counter++;
			}
		}
		print(DIVIDER);
		print(BOOK_FIND_COUNTER_MSG);
		std::cout << counter << std::endl;
		print(DIVIDER);
		print("\n");
		return;
	}

	print(CMD_DOESNT_EXIST_MSG);
}
// user
void LibrarySystem::booksSort(std::vector<std::string>& command)
{
	if (command.size() < 1 || command.size() > 2)
	{
		print(CMD_DOESNT_EXIST_MSG);
		return;
	}

	if (!user_manager.isUser()) return;

	std::string criteria = removeFirst(command);

	if (criteria != "title" && criteria != "author" &&
		criteria != "year"  && criteria != "rating")
	{
		print(CMD_DOESNT_EXIST_MSG);
		return;
	}

	bool ascending = true;

	if (!command.empty())
	{
		if (command[0] == "desc")
		{
			ascending = false;
		}
		else if (command[0] == "asc") {}
		else 
		{ 
			print(CMD_DOESNT_EXIST_MSG); 
			return;
		}
	}

	for (size_t i = 0; i < books.size() - 1; i++)
	{
		for (size_t j = 0; j < books.size() - i - 1; j++)
		{
			if (compareBooks(books[j], books[j + 1], criteria, ascending))
			{
				Book* temp = books[j];
				books[j] = books[j + 1];
				books[j + 1] = temp;
			}
		}
	}
	
	print(BOOK_SORTED_MSG);
}
// admin
void LibrarySystem::bookInfo(std::vector<std::string>& command) const
{
	if (!checkCommandSize(command, 1)) return;
	if (!user_manager.isAdmin()) return;

	std::string id_raw = command[0];
	if (!validateId(id_raw)) return;
	int id = stoi(id_raw);

	if (!existBook(id))
	{
		print(BOOK_DOESNT_EXISTS_MSG);
		return;
	}

	print(DIVIDER);
	printBook(books[bookPosition(id)]);
	print(DIVIDER);
}



bool LibrarySystem::validateId(const std::string& id_raw) const
{
	int id;
	try
	{
		id = stoi(id_raw);
	}
	catch (const std::exception&)
	{
		print(BOOK_ID_ERROR_MSG);
		return false;
	}

	return true;
}

bool LibrarySystem::validateYear(const std::string& year_str) const
{
	int year;
	try
	{
		year = stoi(year_str);
	}
	catch (const std::exception&)
	{
		print(BOOK_YEAR_ERROR_MSG);
		return false;
	}

	if (year < 0 || year > 2024)
	{
		print(BOOK_YEAR_ERROR_MSG);
		return false;
	}

	return true;
}

bool LibrarySystem::validateRating(const std::string& rating_raw) const
{
	float rating;
	try
	{
		rating = stof(rating_raw);
	}
	catch (const std::exception&)
	{
		print(BOOK_RATING_ERROR_MSG);
		return false;
	}

	if (rating < 0.0f || rating > 10.0f)
	{
		print(BOOK_RATING_ERROR_MSG);
		return false;
	}

	return true;
}

bool LibrarySystem::validateTitle(const std::string& title) const
{
	if (title.empty() || hasOnlySpaces(title))
	{
		print(BOOK_TITLE_ERROR_MSG);
		return false;
	}

	return true;
}

bool LibrarySystem::validateAuthor(const std::string& author) const
{
	if (author.empty() || hasOnlySpaces(author))
	{
		print(BOOK_AUTHOR_ERROR_MSG);
		return false;
	}

	return true;
}

bool LibrarySystem::validateGenre(const std::string& genre) const
{
	if (genre.empty() || hasOnlySpaces(genre))
	{
		print(BOOK_GENRE_ERROR_MSG);
		return false;
	}

	return true;
}

bool LibrarySystem::validateKeywords(const std::vector<std::string>& keywords) const
{
	if (keywords.empty())
	{
		print(BOOK_KEYWORDS_ERROR_MSG);
		return false;
	}

	return true;
}

bool LibrarySystem::validateDescription(const std::string& description) const
{
	if (description.empty() || hasOnlySpaces(description))
	{
		print(BOOK_DESCRIPTION_ERROR_MSG);
		return false;
	}

	return true;
}



void LibrarySystem::bookAdd(std::vector<std::string>& command)
{
	if (!checkCommandSize(command, 0)) return;
	if (!user_manager.isAdmin()) return;

	std::string title, author, genre, description;
	int id, year;
	float rating;

	std::string id_raw, year_raw, rating_raw;

	print(BOOK_ADD_ID_MSG);
	std::getline(std::cin, id_raw);
	if (!validateId(id_raw)) return;
	id = stoi(id_raw);

	if (existBook(id))
	{
		print(BOOK_EXISTS_MSG);
		return;
	}

	print(BOOK_ADD_TITLE_MSG);
	std::getline(std::cin, title);
	if (!validateTitle(title)) return;

	print(BOOK_ADD_AUTHOR_MSG);
	std::getline(std::cin, author);
	if (!validateAuthor(author)) return;

	print(BOOK_ADD_GENRE_MSG);
	std::getline(std::cin, genre);
	if (!validateGenre(genre)) return;

	print(BOOK_ADD_DESCRIPTION_MSG);
	std::getline(std::cin, description);
	if (!validateDescription(description)) return;

	print(BOOK_ADD_YEAR_MSG);
	std::getline(std::cin, year_raw);
	if (!validateYear(year_raw)) return;
	year = stoi(year_raw);

	print(BOOK_ADD_RATING_MSG);
	std::getline(std::cin, rating_raw);
	if (!validateRating(rating_raw)) return;
	rating = stof(rating_raw);

	std::string keywords_all;
	print(BOOK_ADD_KEYWORDS_MSG);
	std::getline(std::cin, keywords_all);

	std::vector<std::string> keywords = divideString(keywords_all);

	Book* book = new Book(title, author, genre, description, keywords, id, year, rating);

	books.push_back(book);
	print(BOOK_ADDED_SUCCESSFULLY_MSG);
}

void LibrarySystem::bookRemove(std::vector<std::string>& command)
{
	if (!checkCommandSize(command, 1)) return;
	if (!user_manager.isAdmin()) return;

	std::string id_raw = command[0];
	if (!validateId(id_raw)) return;
	int id = stoi(id_raw);

	if (!existBook(id))
	{
		print(BOOK_DOESNT_EXISTS_MSG);
		return;
	}

	if (!confirmation(CFM_BOOK_REMOVE_MSG))
	{
		std::cin.ignore();
		return;
	}

	books.erase(books.begin() + bookPosition(id));

	print(BOOK_REMOVED_SUCCESSFULLY_MSG);
	std::cin.ignore();
}



void LibrarySystem::printBook(const Book* book) const
{
	print(BOOK_TITLE_PRINT_MSG);
	print(book->getTitle());
	print("\n");

	print(BOOK_AUTHOR_PRINT_MSG);
	print(book->getAuthor());
	print("\n");

	print(BOOK_GENRE_PRINT_MSG);
	print(book->getGenre());
	print("\n");

	print(BOOK_YEAR_PRINT_MSG);
	std::cout << book->getYear();
	print("\n");

	print(BOOK_RATING_PRINT_MSG);
	std::cout << book->getRating();
	print("\n");

	print(BOOK_KEYWORDS_PRINT_MSG);
	std::vector<std::string> keywords = book->getKeywords();
	for (size_t i = 0; i < keywords.size(); i++)
	{
		std::cout << keywords[i] << ' ';
	}

	print("\n");
	print(BOOK_DESCRIPTION_PRINT_MSG);
	print(book->getDescription());
	print("\n");
}

bool LibrarySystem::existBook(const int id) const
{
	for (size_t i = 0; i < books.size(); i++)
	{
		if (books[i]->getId() == id) return true;
	}
	return false;
}


size_t LibrarySystem::bookPosition(const int id) const
{
	if (!existBook(id)) return -1;

	size_t pos = 0;

	for (size_t i = 0; i < books.size(); i++)
	{
		if (books[i]->getId() == id)
		{
			pos = i;
			break;
		}
	}

	return pos;
}

bool LibrarySystem::compareBooks(const Book* first, const Book* second, const std::string& criteria, bool ascending) const
{
	if (criteria == "title") {
		return ascending ? first->getTitle() > second->getTitle() :
			first->getTitle() < second->getTitle();
	}

	if (criteria == "author") {
		return ascending ? first->getAuthor() > second->getAuthor() :
			first->getAuthor() < second->getAuthor();
	}

	if (criteria == "rating") {
		return ascending ? first->getRating() > second->getRating() :
			first->getRating() < second->getRating();
	}

	if (criteria == "year") {
		return ascending ? first->getYear() > second->getYear() :
			first->getYear() < second->getYear();
	}

	return false;
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

Command_ID LibrarySystem::hashBookCommand(const std::string& command) const
{
	if (command == "all")    return Command_ID::_book_all;
	if (command == "add")    return Command_ID::_book_add;
	if (command == "remove") return Command_ID::_book_remove;
	if (command == "view")   return Command_ID::_book_view;
	if (command == "find")   return Command_ID::_book_find;
	if (command == "sort")   return Command_ID::_book_sort;
	if (command == "info")   return Command_ID::_book_info;
	return Command_ID::_error;
}

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

void LibrarySystem::logout(std::vector<std::string>& command)
{
	if (!checkCommandSize(command, 0)) return;

	if (loggedUser == nullptr)
	{
		print(USER_NULL_LOGOUT_MSG);
		return;
	}

	loggedUser = nullptr;
	print(USER_LOGOUT_MSG);
}

void LibrarySystem::open(vector<string>& command)
{
	if (!checkCommandSize(command, 1)) return;

	std::string file_name = removeFirst(command);
	std::ifstream file(file_name);

	if (!file.is_open())
	{
		print(BOOK_FILE_FAILED_MSG);
		return;
	}

	std::string line;

	while (std::getline(file, line))
	{
		// TODO
	}

	file.close();
}

void LibrarySystem::close(vector<string>& command)
{

}

void LibrarySystem::save(vector<string>& command)
{

}

void LibrarySystem::saveas(vector<string>& command)
{

}

void LibrarySystem::help(vector<string>& command) const
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
		print(HELP_USER_RMV_MSG);
		print(HELP_USER_ADD_MSG);
		print(HELP_BOOK_RMV_MSG);
		print(HELP_BOOK_ADD_MSG);
	}
	print("\n");
}

void LibrarySystem::quit(vector<string>& command) const
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
	case _users:  userCommands(command);       break;
	case _error:  print(CMD_DOESNT_EXIST_MSG); break;
	}
}

void LibrarySystem::userCommands(std::vector<std::string>& command)
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



void LibrarySystem::booksView(vector<string>& command) const
{

}

void LibrarySystem::booksAll(vector<string>& command) const
{

}

void LibrarySystem::booksFind(vector<string>& command) const
{

}

void LibrarySystem::booksSort(vector<string>& command) const
{

}

void LibrarySystem::bookInfo(vector<string>& command) const
{

}

bool LibrarySystem::validateId(const string& id_raw) const
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

bool LibrarySystem::validateYear(const string& year_str) const
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

bool LibrarySystem::validateRating(const string& rating_raw) const
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

bool LibrarySystem::validateTitle(const string& title) const
{
	if (title.empty() || hasOnlySpaces(title))
	{
		print(BOOK_TITLE_ERROR_MSG);
		return false;
	}

	return true;
}

bool LibrarySystem::validateAuthor(const string& author) const
{
	if (author.empty() || hasOnlySpaces(author))
	{
		print(BOOK_AUTHOR_ERROR_MSG);
		return false;
	}

	return true;
}

bool LibrarySystem::validateGenre(const string& genre) const
{
	if (genre.empty() || hasOnlySpaces(genre))
	{
		print(BOOK_GENRE_ERROR_MSG);
		return false;
	}

	return true;
}

bool LibrarySystem::validateDescription(const string& description) const
{
	if (description.empty() || hasOnlySpaces(description))
	{
		print(BOOK_DESCRIPTION_ERROR_MSG);
		return false;
	}

	return true;
}



bool LibrarySystem::hasOnlySpaces(const string& str) const
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] != ' ') return false;
	}

	return true;
}

void LibrarySystem::bookAdd(vector<string>& command)
{
	if (!checkCommandSize(command, 0)) return;
	if (!isAdmin()) return;

	string title, author, genre, description;
	int id, year;
	float rating;

	string id_raw, year_raw, rating_raw;

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

	vector<string> keywords = divideString(keywords_all);

	Book* book = new Book(title, author, genre, description, keywords, id, year, rating);

	books.push_back(book);
	print(BOOK_ADDED_SUCCESSFULLY_MSG);
}

void LibrarySystem::bookRemove(vector<string>& command)
{
	if (!checkCommandSize(command, 1)) return;
	if (!isAdmin()) return;
	
	string id_raw = command[0];
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
	saveUsers();

	print(USER_ADDED_SUCCESSFULLY_MSG);
}

void LibrarySystem::userRemove(std::vector<std::string>& command)
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

	if (!confirmation(CFM_USER_REMOVE_MSG)) return;

	users.erase(users.begin() + userPosition(username));
	saveUsers();

	print(USER_REMOVED_SUCCESSFULLY_MSG);
	std::cin.ignore();
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


void LibrarySystem::print(const std::string& message) const
{
	std::cout << message;
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


bool LibrarySystem::existUser(const std::string& username) const
{
	for (size_t i = 0; i < users.size(); i++)
	{
		if (users[i]->getUsername() == username) return true;
	}
	return false;
}

bool LibrarySystem::existBook(const int id) const
{
	for (size_t i = 0; i < books.size(); i++)
	{
		if (books[i]->getId() == id) return true;
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

std::string LibrarySystem::removeFirst(std::vector<std::string>& vector) const
{
	if (vector.empty()) return "";

	std::string first = vector[0];
	vector.erase(vector.begin());

	return first;
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

	while (std::getline(file, line))
	{
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

Command_ID LibrarySystem::hashUserCommand(const std::string& command) const
{
	if (command == "all")    return Command_ID::_user_all;
	if (command == "add")    return Command_ID::_user_add;
	if (command == "remove") return Command_ID::_user_remove;
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

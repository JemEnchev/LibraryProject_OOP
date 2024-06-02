#include "bookManager.h"
#include "messages.h"
#include "helperFunctions.h"
#include "bookValidation.h"
#include <iostream>
#include <fstream>

using namespace HelperFunctions;
using namespace BookValidation;

/** 
Constructor for the book manager class

@brief The constructor initializes the opened file with an empty string

@param user_mngr Holds a reference to the user manager instance in the LibrarySystem class
~~~.cpp
BookManager::BookManager(const UserManager& user_mngr) : user_manager(user_mngr)
{
	openedFile = "";
}
~~~
*/
BookManager::BookManager(const UserManager& user_mngr) : user_manager(user_mngr)
{
	openedFile = "";
}

/**
Destructor for the book manager class

@brief Deletes all book pointers in the vector holding them

~~~.cpp
BookManager::~BookManager()
{
	for (size_t i = 0; i < books.size(); i++)
	{
		delete books[i];
	}
}
~~~
*/
BookManager::~BookManager()
{
	for (size_t i = 0; i < books.size(); i++)
	{
		delete books[i];
	}
}


/** 
Function for hashing the first word of the user input

@brief Depending on the given std::string, the function returns a 
specific enum instance which is used later in the bookCommands
function

@returns Returns an instance of the Command_ID enum
*/
Command_ID BookManager::hashBookCommand(const std::string& command) const
{
	// Depending on the given word we return the appropriate key
	if (command == "all")    return Command_ID::book_all;
	if (command == "add")    return Command_ID::book_add;
	if (command == "remove") return Command_ID::book_remove;
	if (command == "view")   return Command_ID::book_view;
	if (command == "find")   return Command_ID::book_find;
	if (command == "sort")   return Command_ID::book_sort;
	if (command == "info")   return Command_ID::book_info;
	return Command_ID::error;
}


/** 
Function for distributing the given command and calling the correct function for it

@brief Accepts as input a std::vector with all the words from the user input command line and based on 
the first word, after hashing it, calls the appropriate function to handle the command

@param command std::vector with all the words from the user input
*/
void BookManager::bookCommands(std::vector<std::string>& command)
{
	// We extract the first word from the vector
	std::string first = removeFirst(command);

	// We hash the word and use it to determine the correct function
	// to handle the next step
	switch (hashBookCommand(first))
	{
	case Command_ID::book_all:    booksAll(command);     break;
	case Command_ID::book_add:    bookAdd(command);      break;
	case Command_ID::book_remove: bookRemove(command);   break;
	case Command_ID::book_view:   booksView(command);    break;
	case Command_ID::book_find:   booksFind(command);    break;
	case Command_ID::book_sort:   booksSort(command);    break;
	case Command_ID::book_info:   bookInfo(command);     break;
	case Command_ID::error: print(CMD_DOESNT_EXIST_MSG); break;
	}
}


/** 
Function for displaying short book information (title and author)

@brief Accepts std::vector which at this point should be empty and then
prints the books in the memory (if there are such). Does not require
logged user or admin

@param command std::vector containing whats left from the user input
*/
void BookManager::booksView(std::vector<std::string>& command) const
{
	// The vector should be empty because we don't need any parameters
	if (!checkCommandSize(command, 0)) return;

	// Checking if there are books loaded in the memory
	if (books.empty())
	{
		print(FILE_NOT_LOADED_MSG);
		return;
	}

	// Looping through all books in the memory and printing the information
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

	// Printing the total books loaded
	print(DIVIDER);
	print(FILE_LOADED_COUNT_MSG);
	std::cout << books.size();
	print("\n");
}

/**
Function for displaying all book information

@brief Accepts std::vector which at this point should be empty and then
prints the books in the memory (if there are such). Does not require 
logged user or admin

@param command std::vector containing whats left from the user input
*/
void BookManager::booksAll(std::vector<std::string>& command) const
{
	// The vector should be empty because we don't need any parameters
	if (!checkCommandSize(command, 0)) return;

	// Checking if there are books loaded in the memory
	if (books.empty())
	{
		print(FILE_NOT_LOADED_MSG);
		return;
	}

	// Looping through all books in the memory and printing the information
	for (size_t i = 0; i < books.size(); i++)
	{
		print(DIVIDER);
		printBook(books[i]);
	}

	// Printing the total books loaded
	print(DIVIDER);
	print(FILE_LOADED_COUNT_MSG);
	std::cout << books.size();
	print("\n");
}

/**
Function for finding books that meet the given requirements

@brief Accepts std::vector which holds the requirements for searching
the books in the memory. Requires logged user or admin.

@param command std::vector containing whats left from the user input
*/
void BookManager::booksFind(std::vector<std::string>& command) const
{
	// At this point the command should have at least two words
	// [template] [string]
	if (command.size() < 2)
	{
		print(CMD_DOESNT_EXIST_MSG);
		return;
	}

	// Checking if the user is logged
	if (!user_manager.isUser()) return;

	// Checking if we have opened file
	if (openedFile.empty())
	{
		print(FILE_NOT_LOADED_MSG);
		return;
	}

	// Extracting the first word in the given command
	std::string criteria = removeFirst(command);
	// What's left in the command should be the string we using for the search
	std::string key;
	size_t counter = 0;

	// Constructing the key string from the words in the command vector
	for (size_t i = 0; i < command.size(); i++)
	{
		// Normal iteration
		for (size_t j = 0; j < command[i].size(); j++)
		{
			key.push_back(command[i][j]);
		}

		// Last iteration
		if (i + 1 != command.size())
		{
			key.push_back(' ');
		}
	}

	// If the criteria is title
	if (criteria == "title")
	{
		// Iterating through the books
		for (size_t i = 0; i < books.size(); i++)
		{
			// Checking if the current book meets the given criteria and printing it
			if ((toLower(books[i]->getTitle()).find(toLower(key))) != string::npos)
			{
				print(DIVIDER);
				printBook(books[i]);
				counter++;
			}
		}
		// Printing the total count of the books that meet the criteria
		print(DIVIDER);
		print(BOOK_FIND_COUNTER_MSG);
		std::cout << counter << std::endl;
		print(DIVIDER);
		print("\n");
		return;
	}

	// If the criteria is author
	if (criteria == "author")
	{
		// Iterating through the books
		for (size_t i = 0; i < books.size(); i++)
		{
			// Checking if the current book meets the given criteria and printing it
			if ((toLower(books[i]->getAuthor()).find(toLower(key))) != string::npos)
			{
				print(DIVIDER);
				printBook(books[i]);
				counter++;
			}
		}
		// Printing the total count of the books that meet the criteria
		print(DIVIDER);
		print(BOOK_FIND_COUNTER_MSG);
		std::cout << counter << std::endl;
		print(DIVIDER);
		print("\n");
		return;
	}

	// If the criteria is genre
	if (criteria == "genre")
	{
		// Iterating through the books
		for (size_t i = 0; i < books.size(); i++)
		{
			// Checking if the current book meets the given criteria and printing it
			if ((toLower(books[i]->getGenre()).find(toLower(key))) != string::npos)
			{
				print(DIVIDER);
				printBook(books[i]);
				counter++;
			}
		}
		// Printing the total count of the books that meet the criteria
		print(DIVIDER);
		print(BOOK_FIND_COUNTER_MSG);
		std::cout << counter << std::endl;
		print(DIVIDER);
		print("\n");
		return;
	}

	// Printing error message otherwise
	print(CMD_DOESNT_EXIST_MSG);
}

/**
Function for sorting the books that are loaded in the memory

@brief Accepts std::vector which holds the requirements for sorting
the books in the memory. Requires logged user or admin.

@param command std::vector containing whats left from the user input
*/
void BookManager::booksSort(std::vector<std::string>& command)
{
	// At this point the command should have 1 or 2 words
	// Them being the criteria and asc/desc (optional)
	if (command.size() < 1 || command.size() > 2)
	{
		print(CMD_DOESNT_EXIST_MSG);
		return;
	}

	// Checking if the user is logged
	if (!user_manager.isUser()) return;

	// Extracting the first word of the command which
	// should be the criteria
	std::string criteria = removeFirst(command);

	// Checking if given criteria is correct
	if (criteria != "title" && criteria != "author" &&
		criteria != "year" && criteria != "rating")
	{
		print(CMD_DOESNT_EXIST_MSG);
		return;
	}

	// Initializing boolean variable for the order
	// that is ascending by default
	bool ascending = true;

	// Checking if the second word is correct and if
	// it is asc or desc
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

	// Finaly sorting the books by the given criteria and
	// in the correct order
	// (using bubble sort)
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

/**
Function that prints information about a book by a given id

@brief Accepts std::vector which holds the id for a book that should
be printed. Requires admin access.

@param command
*/
void BookManager::bookInfo(std::vector<std::string>& command) const
{
	// Checking if the command has exactly one word
	// Otherwise it must be incorrect
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

void BookManager::bookAdd(std::vector<std::string>& command)
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

void BookManager::bookRemove(std::vector<std::string>& command)
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



void BookManager::open(std::vector<std::string>& command)
{
	if (!checkCommandSize(command, 1)) return;

	std::string file_name = removeFirst(command);
	std::ifstream file(file_name);

	if (!file.is_open())
	{
		if (user_manager.getLoggedUser() == nullptr || 
		   !user_manager.getLoggedUser()->checkAdmin())
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

void BookManager::close(std::vector<std::string>& command)
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
void BookManager::save(std::vector<std::string>& command)
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
		Book* book = books[i];
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
void BookManager::saveas(std::vector<std::string>& command)
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



void BookManager::printBook(const Book* book) const
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

bool BookManager::existBook(const int id) const
{
	for (size_t i = 0; i < books.size(); i++)
	{
		if (books[i]->getId() == id) return true;
	}
	return false;
}

size_t BookManager::bookPosition(const int id) const
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

bool BookManager::compareBooks(const Book* first, const Book* second, const std::string& criteria, bool ascending) const
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

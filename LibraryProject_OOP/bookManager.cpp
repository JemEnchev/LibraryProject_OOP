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
specific enum instance which is used later in the bookCommands()
function
@param command String containing the first word of the user input
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
which should be nothing
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
which should be nothing
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
which should be the criteria and the key
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
			if ((toLower(books[i]->getTitle()).find(toLower(key))) != std::string::npos)
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
			if ((toLower(books[i]->getAuthor()).find(toLower(key))) != std::string::npos)
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
			if ((toLower(books[i]->getGenre()).find(toLower(key))) != std::string::npos)
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
which should be the criteria and the order
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

@param command std::vector containing whats left from the user input 
which should be the id of the book
*/
void BookManager::bookInfo(std::vector<std::string>& command) const
{
	// Checking if the command has exactly one word
	// (this being the book id)
	// Otherwise it must be incorrect
	if (!checkCommandSize(command, 1)) return;

	// Checking if the logged user is admin
	if (!user_manager.isAdmin()) return;

	// Checking if the id is in correct format using
	// the validateId function
	std::string id_raw = command[0];
	if (!validateId(id_raw)) return;
	// Converting String TO Int
	int id = stoi(id_raw);

	// Checking if a book with such id exists
	if (!existBook(id))
	{
		// If not, printing the error
		print(BOOK_DOESNT_EXISTS_MSG);
		return;
	}

	// Finaly printing the book with the given id
	print(DIVIDER);
	printBook(books[bookPosition(id)]);
	print(DIVIDER);
}

/**
Function for adding a book in the memory

@brief Accepts std::vector which holds the data of the book we
want to add into the memory. Requires admin access.

@param command std::vector containing whats left from the user input
which should be nothing
*/
void BookManager::bookAdd(std::vector<std::string>& command)
{
	// Checking if the command has 0 words
	// It should be empty because we get the
	// information for the book from the user
	// afterwards
	if (!checkCommandSize(command, 0)) return;

	// Checking if the logged user is admin
	if (!user_manager.isAdmin()) return;

	// Declaring the required variables
	std::string title, author, genre, description;
	int id, year;
	float rating;
	
	// Variables for storing the "raw" data, aka
	// a string
	std::string id_raw, year_raw, rating_raw;

	// Getting the book id as user input
	print(BOOK_ADD_ID_MSG);
	std::getline(std::cin, id_raw);

	// Validating if the id format is correct
	if (!validateId(id_raw)) return;

	// Converting from string to int
	id = stoi(id_raw);

	// Checking if the book exists
	if (existBook(id))
	{
		// Printing error message
		print(BOOK_EXISTS_MSG);
		return;
	}

	// Getting the title via user input
	print(BOOK_ADD_TITLE_MSG);
	std::getline(std::cin, title);

	// Validating the title
	if (!validateTitle(title)) return;

	// Getting the author via user input
	print(BOOK_ADD_AUTHOR_MSG);
	std::getline(std::cin, author);

	// Validating the author
	if (!validateAuthor(author)) return;

	// Getting the title via user input
	print(BOOK_ADD_GENRE_MSG);
	std::getline(std::cin, genre);

	// Validating the genre
	if (!validateGenre(genre)) return;

	// Getting the description via user input
	print(BOOK_ADD_DESCRIPTION_MSG);
	std::getline(std::cin, description);

	// Validating the description
	if (!validateDescription(description)) return;

	// Getting the year via user input
	print(BOOK_ADD_YEAR_MSG);
	std::getline(std::cin, year_raw);

	// Validating the year and converting
	if (!validateYear(year_raw)) return;
	year = stoi(year_raw);

	// Getting the rating via user input
	print(BOOK_ADD_RATING_MSG);
	std::getline(std::cin, rating_raw);

	// Validating the rating and converting
	if (!validateRating(rating_raw)) return;
	rating = stof(rating_raw);

	// Getting the keywords via user input
	std::string keywords_all;
	print(BOOK_ADD_KEYWORDS_MSG);
	std::getline(std::cin, keywords_all);

	// Dividing the user input into words
	std::vector<std::string> keywords = divideString(keywords_all);

	// Creating a book pointer with the gathered data
	Book* book = new Book(title, author, genre, description, keywords, id, year, rating);

	// Pushing it in the books vector
	books.push_back(book);
	print(BOOK_ADDED_SUCCESSFULLY_MSG);
}

/**
Function for removing a book from the memory

@brief Accepts std::vector which holds the data of the book we
want to remove from the memory. Requires admin access.

@param command std::vector containing whats left from the user input which
should be the id of the book we want to remove
*/
void BookManager::bookRemove(std::vector<std::string>& command)
{
	// Checking if the command has exactly one word
	// This being the id of the book we want to remove
	if (!checkCommandSize(command, 1)) return;

	// Checking if the user is admin
	if (!user_manager.isAdmin()) return;

	// Validating and converting the id
	std::string id_raw = command[0];
	if (!validateId(id_raw)) return;
	int id = stoi(id_raw);

	// Checking if a book with this id exists
	if (!existBook(id))
	{
		// If not, printing error message
		print(BOOK_DOESNT_EXISTS_MSG);
		return;
	}

	// Asking for confirmation
	if (!confirmation(CFM_BOOK_REMOVE_MSG))
	{
		// Ignoring the randomly added newline
		std::cin.ignore();
		return;
	}

	// Removing the book from the vector using its index
	books.erase(books.begin() + bookPosition(id));
	
	print(BOOK_REMOVED_SUCCESSFULLY_MSG);
	std::cin.ignore();
}


/**
Function for loading a book file into the memory

@brief Accepts std::vector which holds the name of the book file we want to
load into the memory

@param command std::vector containing whats left from the user input which
should be the name of the file we want to open
*/
void BookManager::open(std::vector<std::string>& command)
{
	// Checking if the command has exactly one word
	// This being the name of the file
	if (!checkCommandSize(command, 1)) return;        
												      
	// Extracting the file name					      
	std::string file_name = removeFirst(command);     
	// Opening input file stream				      
	std::ifstream file(file_name);				      
												      
	// Checking if file opens
	// If it doesn't, most likely it doesn't exist
	if (!file.is_open())
	{
		// If the logged user is not admin we print error message
		if (user_manager.getLoggedUser() == nullptr || 
		   !user_manager.getLoggedUser()->checkAdmin())
		{
			print(FILE_DOESNT_EXIST_MSG);
			return;
		}

		// If it is admin, we create a file with the given name
		// We do that by opening an output stream which
		// automaticaly creates the file
		std::ofstream temp(file_name);
		temp.close();

		file.open(file_name);

		// If something goes wrong we print error message
		if (!file.is_open())
		{
			print(FILE_FAILED_MSG);
			return;
		}
	}

	// By this point a file with the given name exists
	// or if the logged user is admin, we created one
	// we update the current opened file
	openedFile = file_name;

	// Initializing variables for holding the incomming data
	std::vector<std::string> parts;
	std::string line;

	// Reading lines from the file until we get to the end
	while (std::getline(file, line))
	{
		// Initializing a holder for the symbols from the line
		std::string holder;

		// Iterating the current line and extracting the different
		// words with the delimeter ~
		for (size_t i = 0; i < line.size(); i++)
		{
			if (line[i] == '~')
			{
				// Saving the now whole word
				parts.push_back(holder);
				// Clearing the holder for the next word
				holder.clear();
				// Jumping over the ~ symbol
				i += 2;
			}
			// Pushing the next symbol from the i-th position in the line
			holder.push_back(line[i]);
		}
		// When exiting the loop we still have one word left in
		// the holder, so we push in the vector with the other words
		parts.push_back(holder);

		// Id ~ Title ~ Author ~ Genre ~ Year ~ Rating ~ Keywords ~ Description

		// Converting the id
		int id = stoi(parts[0]);

		// Checking if a book with this id exists and if so
		// we skip the next steps
		if (existBook(id)) continue;

		// Getting the data from the vector
		std::string title = parts[1];
		std::string author = parts[2];
		std::string genre = parts[3];
		int year = stoi(parts[4]);
		float rating = stof(parts[5]);
		std::vector<std::string> keywords = divideString(parts[6]);
		std::string description = parts[7];
		parts.clear();

		// Creating a book pointer with the gathered data
		Book* book = new Book(title, author, genre, description, keywords, id, year, rating);

		// Pushing the pointer in the vector
		books.push_back(book);
	}

	// After pushing all the books we close the file
	file.close();

	// Printing the appropriate message
	print(FILE_OPENED_MSG);
	print(FILE_LOADED_COUNT_MSG);
	std::cout << books.size() << std::endl;
}

/**
Function that closes the currently opened file

@brief Accepts std::vector which holds the name of the book file we want to
unload from the memory

@param command std::vector containing whats left from the user input
which should be nothing
*/
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

/**
Function that saves the loaded books into the opened file

@brief Saves the current state of the book vector in the 
currently opened file. Required admin access

@param command std::vector containing whats left from the user input
which should be nothing
*/
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

/**
Function that saves the loaded books in new file

@brief Saves the current state of the book vector in new file
with the given name. Required admin access

@param command std::vector containing whats left from the user input
which should be the name of the new file
*/
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



/**
Function that prints the information of a given book

@brief Accepts a book pointer and prints the information
of the book

@param book Pointer to the book we want to print
*/
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

/**
Function that checks if a book with a given id exists

@param id Integer value that holds a book id
@returns True if a book with the given id exist and False if it doesn't
*/
bool BookManager::existBook(const int id) const
{
	for (size_t i = 0; i < books.size(); i++)
	{
		if (books[i]->getId() == id) return true;
	}
	return false;
}

/**
Function that finds the index of a book in the vector

@brief Searches the book vector to find the position
of the book with the given id

@param id Integer value that holds a book id
@returns The index of the book in the vector
*/
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

/**
Function that compares two books for the booksSort() function

@brief Using the given criteria to compare the two books in 
the according order

@param first Book pointer for the first book
@param second Book pointer for the second book
@param criteria String reference to the sorting criteria
@param ascending Boolean that shows if the order is 
ascending or not
@returns True if the books are in the correct order 
according to the given criteria
*/
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

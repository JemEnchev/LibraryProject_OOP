#pragma once
#include <vector>
#include <string>
#include "command_id.h"
#include "book.h"
#include "userManager.h"

/**
Class responsible for handling all book commands in the library system

@brief This class handles all commands related to modifying book files, 
manipulating books loaded in the memory, creating, removing and updating 
books information. (CRUD operations)
*/
class BookManager
{
public:
	BookManager(const UserManager&);
	~BookManager();

	Command_ID hashBookCommand(const std::string&) const;
	void bookCommands(std::vector<std::string>&);

	void booksView(std::vector<std::string>&) const;
	void booksAll(std::vector<std::string>&) const;
	void booksFind(std::vector<std::string>&) const;
	void booksSort(std::vector<std::string>&);
	void bookInfo(std::vector<std::string>&) const;
	void bookAdd(std::vector<std::string>&);
	void bookRemove(std::vector<std::string>&);

	void open(std::vector<std::string>&);
	void close(std::vector<std::string>&);
	void save(std::vector<std::string>&);
	void saveas(std::vector<std::string>&);

	void printBook(const Book*) const;
	bool existBook(const int) const;
	size_t bookPosition(const int) const;
	bool compareBooks(const Book*, const Book*, const std::string&, bool) const;

private:
	/**
	The name of the file we are currently working with
	*/
	std::string openedFile;

	/**
	The vector holding all the books that are loaded in the memory
	*/
	std::vector<Book*> books;

	/**
	A reference to the UserManager class defined in 
	the LibrarySystem class, used for accessing some user data
	*/
	const UserManager& user_manager;
};


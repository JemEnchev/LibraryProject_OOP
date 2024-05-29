#pragma once
#include <vector>
#include "book.h"
#include "user.h"
#include "command_id.h"
#include "userManager.h"

class LibrarySystem
{
public:
	LibrarySystem();
	~LibrarySystem();

	void start();

private:
	void login(std::vector<std::string>&);
	void logout(std::vector<std::string>&);

	void open(std::vector<std::string>&);
	void close(std::vector<std::string>&);
	void save(std::vector<std::string>&);
	void saveas(std::vector<std::string>&);
	void help(std::vector<std::string>&) const;
	void quit(std::vector<std::string>&) const;

	void executeCommand(std::string&);
	void bookCommands(std::vector<std::string>&);

	void booksView(std::vector<std::string>&) const;
	void booksAll(std::vector<std::string>&) const;
	void booksFind(std::vector<std::string>&) const;
	void booksSort(std::vector<std::string>&);
	void bookInfo(std::vector<std::string>&) const;

	bool validateId(const std::string&) const;
	bool validateYear(const std::string&) const;
	bool validateRating(const std::string&) const;
	bool validateTitle(const std::string&) const;
	bool validateAuthor(const std::string&) const;
	bool validateGenre(const std::string&) const;
	bool validateKeywords(const std::vector<std::string>&) const;
	bool validateDescription(const std::string&) const;
	

	void bookAdd(std::vector<std::string>&);
	void bookRemove(std::vector<std::string>&);
	
	
	void printBook(const Book*) const;
	bool existBook(const int) const;

	
	size_t bookPosition(const int) const;
	bool compareBooks(const Book*, const Book*, const std::string&, bool) const;


	Command_ID hashCommand(const std::string&) const;
	Command_ID hashBookCommand(const std::string&) const;

	std::string openedFile;
	std::vector<Book*> books;

	UserManager user_manager;
};



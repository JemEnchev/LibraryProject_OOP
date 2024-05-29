#pragma once
#include <vector>
#include <string>
#include "command_id.h"
#include "book.h"


#include "userManager.h"


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

	void clearBooks();
	std::vector<Book*> getBooks() const;
	void booksPushBack(Book*);
	std::string getOpenedFile() const;
	void setOpenedFile(const std::string&);

	size_t bookPosition(const int) const;
	bool compareBooks(const Book*, const Book*, const std::string&, bool) const;

private:
	std::string openedFile;
	std::vector<Book*> books;

	const UserManager& user_manager;
};


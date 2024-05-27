#pragma once
#include <vector>
#include "book.h"
#include "user.h"

enum Command_ID
{
	_open,
	_close,
	_save,
	_saveas,
	_help,
	_login,
	_logout,
	_quit,
	_books,
	_users,
	_error,
	_user_all,
	_user_add,
	_user_remove,
	_book_all,
	_book_view,
	_book_find,
	_book_add,
	_book_remove,
	_book_sort,
	_book_info
};

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
	void userCommands(std::vector<std::string>&);
	void bookCommands(std::vector<std::string>&);

	void booksView(std::vector<std::string>&) const;
	void booksAll(std::vector<std::string>&) const;
	void booksFind(std::vector<std::string>&) const;
	void booksSort(std::vector<std::string>&) const;
	void bookInfo(std::vector<std::string>&) const;

	bool validateId(const std::string&) const;
	bool validateYear(const std::string&) const;
	bool validateRating(const std::string&) const;
	bool validateTitle(const std::string&) const;
	bool validateAuthor(const std::string&) const;
	bool validateGenre(const std::string&) const;
	bool validateDescription(const std::string&) const;
	bool hasOnlySpaces(const std::string&) const;

	void bookAdd(std::vector<std::string>&);
	void bookRemove(std::vector<std::string>&);
	void userAdd(std::vector<std::string>&);
	void userRemove(std::vector<std::string>&);
	void usersAll(std::vector<std::string>&) const;
	
	void print(const std::string&) const;
	void printBook(const Book*) const;
	void printUser(const User*) const;
	bool confirmation(const std::string&) const;

	bool existUser(const std::string&) const;
	bool existBook(const int) const;

	bool isAdmin() const;
	bool isUser() const;
	User* findUser(std::string&) const;
	size_t userPosition(const std::string&) const;
	size_t bookPosition(const int) const;
	bool compareBooks(const Book*, const Book*, const std::string&, bool);

	std::vector<std::string> divideString(const std::string&) const;
	bool checkCommandSize(std::vector<std::string>&, size_t) const;
	std::string removeFirst(std::vector<std::string>&) const;
	std::string toLower(const std::string&) const;

	void loadUsers();
	void saveUsers() const;

	Command_ID hashCommand(const std::string&) const;
	Command_ID hashUserCommand(const std::string&) const;
	Command_ID hashBookCommand(const std::string&) const;

	User* loggedUser;
	std::string openedFile;
	std::vector<Book*> books;
	std::vector<User*> users;
};



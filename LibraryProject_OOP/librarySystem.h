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
	_error
};

class LibrarySystem
{
public:
	LibrarySystem();
	~LibrarySystem();

	void start();

private:
	void login();
	void logout();

	void open();
	void close();
	void save();
	void saveas();
	void help() const;
	void quit() const;
	void error() const;

	void bookCommands() const;
	void userCommands() const;

	void booksView() const;
	void booksAll() const;
	void booksFind() const;
	void booksSort() const;
	void bookInfo() const;

	void bookAdd();
	void bookRemove();
	void userAdd();
	void userRemove();
	
	void executeCommand(const std::string&);
	bool confirmation(std::string) const;

	std::vector<std::string> divideCommand(const std::string&) const;

	void loadUsers();
	void loadBooks();
	Command_ID hash(const std::string&) const;

	const std::string USERS_FILE = "users.txt";
	const std::string BOOKS_FILE = "books.txt";

	User* loggedUser;
	std::vector<Book> books;
	std::vector<User> users;
};



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

	void open(const std::string&);
	void close();
	void save();
	void saveas(const std::string&);
	void help() const;
	void quit() const;
	void print(const std::string&) const;

	void bookCommands(const std::vector<std::string>&);
	void userCommands(const std::vector<std::string>&);

	void booksView() const;
	void booksAll() const;
	void booksFind() const;
	void booksSort() const;
	void bookInfo() const;

	void bookAdd();
	void bookRemove();
	void userAdd(const std::string&, const std::string&, bool);
	void userRemove(const std::string&);
	
	void executeCommand(const std::string&);
	bool confirmation(const std::string&) const;
	bool contains(const std::vector<std::string>&, const std::string&) const;
	bool existUser(const std::string&) const;
	User* findUser(std::string&) const;

	std::vector<std::string> divideString(const std::string&) const;

	void loadUsers();
	void saveUsers() const;
	void saveBooks() const;
	Command_ID hash(const std::string&) const;

	User* loggedUser;
	std::vector<Book*> books;
	std::vector<User*> users;
};



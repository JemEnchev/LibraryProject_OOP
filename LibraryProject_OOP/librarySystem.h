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

enum User_Command_ID
{
	_all,
	_add,
	_remove,
	_user_error
};

enum Book_Command_ID
{

};

class LibrarySystem
{
public:
	LibrarySystem();
	~LibrarySystem();

	void start();

private:
	void login(std::vector<std::string>&);
	void logout();

	void open(const std::string&);
	void close();
	void save();
	void saveas(const std::string&);
	void help() const;
	void quit() const;
	void print(const std::string&) const;

	void executeCommand(const std::string&);
	void userCommands(std::vector<std::string>&);
	void bookCommands(std::vector<std::string>&);

	void booksView() const;
	void booksAll() const;
	void booksFind() const;
	void booksSort() const;
	void bookInfo() const;

	void bookAdd();
	void bookRemove();
	void userAdd(std::vector<std::string>&);
	void userRemove(std::vector<std::string>&);
	void usersAll(std::vector<std::string>&) const;
	
	bool confirmation(const std::string&) const;
	//bool contains(const std::vector<std::string>&, const std::string&) const;
	bool existUser(const std::string&) const;
	bool isAdmin() const;
	User* findUser(std::string&) const;
	size_t userPosition(const std::string&) const;

	std::vector<std::string> divideString(const std::string&) const;
	bool checkCommandSize(std::vector<std::string>&, size_t) const;

	void loadUsers();
	void saveUsers() const;
	void saveBooks() const;
	Command_ID hashCommand(const std::string&) const;
	User_Command_ID hashUserCommand(const std::string&) const;
	Book_Command_ID hashBookCommand(const std::string&) const;

	User* loggedUser;
	std::vector<Book*> books;
	std::vector<User*> users;
};



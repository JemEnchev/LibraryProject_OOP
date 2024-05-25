#pragma once
#include <vector>
#include "book.h"
#include "user.h"
using std::vector; 
using std::string;

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
	void login(vector<string>&);
	void logout(vector<string>&);

	void open(vector<string>&);
	void close(vector<string>&);
	void save(vector<string>&);
	void saveas(vector<string>&);
	void help(vector<string>&) const;
	void quit(vector<string>&) const;

	void executeCommand(string&);
	void userCommands(vector<string>&);
	void bookCommands(vector<string>&);

	void booksView(vector<string>&) const;
	void booksAll(vector<string>&) const;
	void booksFind(vector<string>&) const;
	void booksSort(vector<string>&) const;
	void bookInfo(vector<string>&) const;

	bool validateId(const string&) const;
	bool validateYear(const string&) const;
	bool validateRating(const string&) const;
	bool validateTitle(const string&) const;
	bool validateAuthor(const string&) const;
	bool validateGenre(const string&) const;
	bool validateDescription(const string&) const;
	bool hasOnlySpaces(const string&) const;

	void bookAdd(vector<string>&);
	void bookRemove(vector<string>&);
	void userAdd(vector<string>&);
	void userRemove(vector<string>&);
	void usersAll(vector<string>&) const;
	
	void print(const string&) const;
	void printBook(const int) const;
	bool confirmation(const string&) const;

	bool existUser(const string&) const;
	bool existBook(const int) const;

	bool isAdmin() const;
	User* findUser(string&) const;
	size_t userPosition(const string&) const;
	size_t bookPosition(const int) const;

	vector<string> divideString(const string&) const;
	bool checkCommandSize(vector<string>&, size_t) const;
	string removeFirst(vector<string>&) const;

	void loadUsers();
	void saveUsers() const;

	Command_ID hashCommand(const string&) const;
	Command_ID hashUserCommand(const string&) const;
	Command_ID hashBookCommand(const string&) const;

	User* loggedUser;
	vector<Book*> books;
	vector<User*> users;
};



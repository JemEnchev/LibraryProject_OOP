#pragma once
#include <vector>
#include "book.h"
#include "user.h"


class LibrarySystem
{
public:
	LibrarySystem();
	~LibrarySystem();

	void start();

	void login(const std::string&, const std::string&);
	void logout();

	void open();
	void close();
	void save();
	void saveas();
	void help() const;
	//void exit();

	void booksView() const;
	void booksAll() const;
	void booksFind() const;
	void booksSort() const;

	void bookAdd();
	void bookRemove();
	void userAdd();
	void userRemove();
	
private:
	void executeCommand(const std::string&);

	void loadUsers();
	void loadBooks();

	const std::string USERS_FILE = "users.txt";
	const std::string BOOKS_FILE = "books.txt";

	User* loggedUser;
	std::vector<Book> books;
	std::vector<User> users;
};


#pragma once
#include <vector>
#include "book.h"
#include "user.h"


class LibrarySystem
{
public:
	LibrarySystem();
	~LibrarySystem();



private:
	const std::string USERS_FILE = "users.txt";
	const std::string BOOKS_FILE = "books.txt";

	User* loggedUser;
	std::vector<Book> books;
	std::vector<User> users;
};


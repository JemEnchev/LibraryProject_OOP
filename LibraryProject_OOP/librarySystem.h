#pragma once
#include <vector>
#include "book.h"
#include "user.h"
#include "command_id.h"
#include "userManager.h"
#include "bookManager.h"

/**
Class for starting the program and handling the user input
*/
class LibrarySystem
{
public:
	LibrarySystem();

	void start();

private:
	void login(std::vector<std::string>&);
	void logout(std::vector<std::string>&);

	void help(std::vector<std::string>&) const;
	void quit(std::vector<std::string>&) const;

	void executeCommand(std::string&);
	Command_ID hashCommand(const std::string&) const;
	
	/**
	Instance of the UserManager class
	*/
	UserManager user_manager;

	/**
	Instance of the BookManager class
	*/
	BookManager book_manager;
};



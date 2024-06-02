#include "librarySystem.h"
#include "messages.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include "helperFunctions.h"

using namespace HelperFunctions;

/**
Constructor for the LibrarySystem class

@brief Loads the users into the memory of the system.
Gives a reference to the user manager instance to the book manager class.
If there is not an admin user loaded, it creates one.
*/
LibrarySystem::LibrarySystem() : book_manager(user_manager)
{
	user_manager.loadUsers();

	if (!user_manager.existUser("admin"))
	{
		User* admin = new User("admin", "i<3c++", true);
		user_manager.usersPushBack(admin);
	}
}

/**
Function for starting the library system program

@brief When called it loads the users in the system memory and
accepts user input commands in a loop
*/
void LibrarySystem::start()
{
	user_manager.loadUsers();

	print(START_MSG);
	std::string command;

	while (true)
	{
		print("> ");
		std::getline(std::cin, command);

		executeCommand(command);
	}

}

/**
Function for logging a user in the library system

@brief First asks for a username and then for a password and
if they are correct, the user is logged in the system

@param command Std::vector which should be empty
*/
void LibrarySystem::login(std::vector<std::string>& command)
{
	if (!checkCommandSize(command, 0)) return;

	if (user_manager.getLoggedUser() != nullptr)
	{
		print(USER_ALREADY_LOGGED_MSG);
		return;
	}

	std::string username, password;

	print(LOGIN_USERNAME_MSG);
	std::cin >> username;

	
	print(LOGIN_PASSWORD_MSG);

	int ch;

	while (true) 
	{
		ch = _getch();

		if (ch == '\r' || ch == '\n') break;
		
		if (ch == 8) // ascii code 8 -> backsapce
		{
			if (!password.empty())
			{
				print("\b \b");
				password.pop_back();
			}
			continue;
		}
		
		password.push_back(ch);
		print(PASSWORD_SYMBOL);
	}

	print("\n");

	if (user_manager.existUser(username) && 
		user_manager.findUser(username)->getPassword() == password)
	{
		user_manager.setLoggedUser(user_manager.findUser(username));

		std::cout << USER_LOGGED_SUCCESSFULLY_MSG << username << '!' << std::endl;
		std::cin.ignore();
		return;
	}

	print(USER_LOGGED_FAILED_MSG);
	std::cin.ignore();
	return;
}

/**
Function for logging out a user of the library system

@param command Vector which should be empty

@attention This functions requrires a logged user, 
otherwise it does nothing
*/
void LibrarySystem::logout(std::vector<std::string>& command)
{
	if (!checkCommandSize(command, 0)) return;

	if (user_manager.getLoggedUser() == nullptr)
	{
		print(USER_NULL_LOGOUT_MSG);
		return;
	}

	user_manager.setLoggedUser(nullptr);
	print(USER_LOGOUT_MSG);
}

/**
Function for printing the help menu

@param command Vector which should be empty
*/
void LibrarySystem::help(std::vector<std::string>& command) const
{
	if (!checkCommandSize(command, 0)) return;

	print("\n");
	print(HELP_MENU_MSG);
	print(HELP_DISCL_1_MSG);
	print(HELP_DISCL_2_MSG);
	print(HELP_DISCL_3_MSG);
	print(HELP_LOGIN_MSG);
	print(HELP_LOGOUT_MSG);
	print(HELP_OPEN_MSG);
	print(HELP_CLOSE_MSG);
	print(HELP_EXIT_MSG);
	print(HELP_BOOKS_VIEW_MSG);
	print(HELP_BOOKS_ALL_MSG);
	print(HELP_BOOKS_FIND_MSG);
	print(HELP_BOOKS_SORT_MSG);
	print(HELP_HELP_MSG);

	if (user_manager.getLoggedUser() != nullptr && user_manager.getLoggedUser()->checkAdmin())
	{
		//print("\n");
		print(HELP_SAVE_MSG);
		print(HELP_SAVEAS_MSG);
		print(HELP_BOOK_INFO_MSG);
		print(HELP_USER_RMV_MSG);
		print(HELP_USER_ADD_MSG);
		print(HELP_BOOK_RMV_MSG);
		print(HELP_BOOK_ADD_MSG);
	}
	print("\n");
}

/**
Function for quiting the library system

@param Vector which should be empty

@warning After quiting the library system all unsaved 
changes to the book files won't be saved!
*/
void LibrarySystem::quit(std::vector<std::string>& command) const
{
	if (!checkCommandSize(command, 0)) return;

	if (confirmation(CFM_EXIT_MSG))
	{
		exit(0);
	}
	std::cin.ignore();
}



/**
Function for distributing the given command and calling the correct function for it

@brief Accepts as input a std::vector with all the words from the user input command line and based on
the first word, after hashing it, calls the appropriate function to handle the command

@param command std::vector with all the words from the user input
*/
void LibrarySystem::executeCommand(std::string& command_line)
{
	if (command_line.empty()) return; 

	std::vector<std::string> command = divideString(command_line);

	std::string first = removeFirst(command);

	switch (hashCommand(first))
	{
	case Command_ID::help:                help(command);           break;
	case Command_ID::login:               login(command);          break;
	case Command_ID::logout:              logout(command);         break;
	case Command_ID::quit:                quit(command);           break;
	case Command_ID::open:   book_manager.open(command);           break;
	case Command_ID::close:  book_manager.close(command);          break;
	case Command_ID::save:   book_manager.save(command);           break;
	case Command_ID::saveas: book_manager.saveas(command);         break;
	case Command_ID::books:  book_manager.bookCommands(command);   break;
	case Command_ID::users:  user_manager.userCommands(command);   break;
	case Command_ID::error:  print(CMD_DOESNT_EXIST_MSG);          break;
	}
}

/**
Function for hashing the first word of the user input

@brief Depending on the given std::string, the function returns a
specific enum instance which is used later in the executeCommand()
function
@param command String containing the first word of the user input
@returns Returns an instance of the Command_ID enum
*/
Command_ID LibrarySystem::hashCommand(const std::string& command) const
{
	if (command == "open")   return Command_ID::open;
	if (command == "close")  return Command_ID::close;
	if (command == "save")   return Command_ID::save;
	if (command == "saveas") return Command_ID::saveas;
	if (command == "help")   return Command_ID::help;
	if (command == "login")  return Command_ID::login;
	if (command == "logout") return Command_ID::logout;
	if (command == "exit")   return Command_ID::quit;
	if (command == "users" || command == "user")  return Command_ID::users;
	if (command == "books" || command == "book") return Command_ID::books;
	return Command_ID::error;
}

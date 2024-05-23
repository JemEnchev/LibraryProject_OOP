#include "librarySystem.h"
#include <iostream>

LibrarySystem::LibrarySystem()
{
    if (users.empty())
    {
        users.push_back(User("admin", "i<3c++", true));
    }
}

LibrarySystem::~LibrarySystem()
{
	delete loggedUser;
}

void LibrarySystem::start()
{
    std::cout << "=== Welcome to the Library System Project ===" << std::endl;
    std::cout << "Type 'help' for more info..." << std::endl;

    while (true)
    {
        std::cout << ">";
        std::getline(std::cin, command);
        executeCommand(command);
    }

}

void LibrarySystem::login(const std::string&, const std::string&)
{
}

void LibrarySystem::logout()
{
}

void LibrarySystem::open()
{
}

void LibrarySystem::close()
{
}

void LibrarySystem::save()
{
}

void LibrarySystem::saveas()
{
}

void LibrarySystem::help() const
{
}

//void LibrarySystem::exit()
//{
//
//}

void LibrarySystem::booksView() const
{
}

void LibrarySystem::booksAll() const
{
}

void LibrarySystem::booksFind() const
{
}

void LibrarySystem::booksSort() const
{
}

void LibrarySystem::bookAdd()
{
}

void LibrarySystem::bookRemove()
{
}

void LibrarySystem::userAdd()
{
}

void LibrarySystem::userRemove()
{
}

void LibrarySystem::executeCommand(const std::string& command)
{
    std::istringstream ss(command);
    ss >> command;

    switch (command)
    {
        case "exit": exit(); break;
        default:
            break;
    }
}

void LibrarySystem::loadUsers()
{
}

void LibrarySystem::loadBooks()
{
}

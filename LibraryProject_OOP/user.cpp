#include "user.h"

User::User(std::string _username, 
		   std::string _password, 
		   bool _isAdmin)
	: username(_username),
	  password(_password),
	  isAdmin(_isAdmin)
{}

std::string User::getUsername() const
{
	return this->username;
}

std::string User::getPassword() const
{
	return this->password;
}

bool User::checkAdmin() const
{
	return this->isAdmin;
}

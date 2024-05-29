#include "user.h"

User::User(const std::string& _username, 
		   const std::string& _password, 
		   bool _isAdmin)
	: username(_username),
	  password(_password),
	  isAdmin(_isAdmin)
{}

const std::string& User::getUsername() const
{
	return username;
}

const std::string& User::getPassword() const
{
	return this->password;
}

void User::setUsername(const std::string& username)
{
	this->username = username;
}

void User::setPassword(const std::string& password)
{
	this->password = password;
}

bool User::checkAdmin() const
{
	return this->isAdmin;
}
#include "user.h"

/// Constructor for the user class
/// @param _username Holds the user's username
/// @param _password Holds the user's password
/// @param _isAdmin Holds a boolean value indicating if the user is an admin or not
User::User(const std::string& _username, 
		   const std::string& _password, 
		   bool _isAdmin)
	: username(_username),
	  password(_password),
	  isAdmin(_isAdmin)
{}

/// Getter for the user's username
/// ~~~.cpp
/// const std::string& User::getUsername() const
/// {
///	 return username;
/// }
/// ~~~
/// @returns Returns a std::string reference to the user's username
const std::string& User::getUsername() const
{
	return username;
}

/// Getter for the user's password
/// ~~~.cpp
/// const std::string& User::getPassword() const
///{
///	return this->password;
///}
/// ~~~
/// @returns Returns a std::string reference to the user's password
const std::string& User::getPassword() const
{
	return this->password;
}

/// Getter for the user's access level
/// ~~~.cpp
/// bool User::checkAdmin() const
/// {
///	 return this->isAdmin;
/// }
/// ~~~
/// @returns Returns a boolean value indicating if the user is an admin or not
bool User::checkAdmin() const
{
	return this->isAdmin;
}
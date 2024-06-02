#pragma once
#include <string>

/**
Class for the users in the library system

@brief This class contains and gives information about
the users that login in the library system, including their
usernames, passwords and access level
*/
class User
{
public:
	User(const std::string&, const std::string&, bool);

	const std::string& getUsername() const;
	const std::string& getPassword() const;
	bool checkAdmin() const;

private:
	/**
	User username
	*/
	std::string username;
	/**
	User password
	*/
	std::string password;
	/**
	User access level
	*/
	bool isAdmin;
};


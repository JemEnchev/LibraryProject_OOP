#pragma once
#include <string>

class User
{
public:
	User(std::string, std::string, bool);

	std::string getUsername() const;
	std::string getPassword() const;
	bool checkAdmin() const;

private:
	std::string username;
	std::string password;
	bool isAdmin;
};


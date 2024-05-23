#pragma once
#include <string>

class User
{
public:
	User(const std::string&, const std::string&, bool);

	std::string getUsername() const;
	std::string getPassword() const;
	void setUsername(const std::string&);
	void setPassword(const std::string&);
	bool checkAdmin() const;

private:
	std::string username;
	std::string password;
	bool isAdmin;
};


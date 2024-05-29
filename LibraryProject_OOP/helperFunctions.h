#pragma once
#include <vector>
#include <string>

namespace HelperFunctions
{
	std::vector<std::string> divideString(const std::string&);
	bool checkCommandSize(std::vector<std::string>&, size_t);
	std::string removeFirst(std::vector<std::string>&);
	std::string toLower(const std::string&);
	void print(const std::string&);
	bool confirmation(const std::string&);
	bool hasOnlySpaces(const std::string&);
};


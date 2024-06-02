#pragma once
#include <string>
#include <vector>

/**
Class with helper functions for validating
the book parameters
*/
namespace BookValidation
{
	bool validateId(const std::string&);
	bool validateYear(const std::string&);
	bool validateRating(const std::string&);
	bool validateTitle(const std::string&);
	bool validateAuthor(const std::string&);
	bool validateGenre(const std::string&);
	bool validateKeywords(const std::vector<std::string>&);
	bool validateDescription(const std::string&);
};


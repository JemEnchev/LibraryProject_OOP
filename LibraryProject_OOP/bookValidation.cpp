#include "bookValidation.h"
#include "helperFunctions.h"
#include "messages.h"

using namespace HelperFunctions;

namespace BookValidation
{
	/**
	Function for validating the correctness of the given id

	@param id_raw String reference to the id given by the user
	@returns True if it is correctly given and False otherwise
	*/
	bool validateId(const std::string& id_raw)
	{
		int id;
		try
		{
			id = stoi(id_raw);
		}
		catch (const std::exception&)
		{
			print(BOOK_ID_ERROR_MSG);
			return false;
		}

		return true;
	}

	/**
	Function for validating the correctness of the given year

	@param year_str String reference to the year given by the user
	@returns True if it is correctly given and False otherwise
	*/
	bool validateYear(const std::string& year_str)
	{
		int year;
		try
		{
			year = stoi(year_str);
		}
		catch (const std::exception&)
		{
			print(BOOK_YEAR_ERROR_MSG);
			return false;
		}

		if (year < 0 || year > 2024)
		{
			print(BOOK_YEAR_ERROR_MSG);
			return false;
		}

		return true;
	}

	/**
	Function for validating the correctness of the given rating

	@param rating_raw String reference to the rating given by the user
	@returns True if it is correctly given and False otherwise
	*/
	bool validateRating(const std::string& rating_raw)
	{
		float rating;
		try
		{
			rating = stof(rating_raw);
		}
		catch (const std::exception&)
		{
			print(BOOK_RATING_ERROR_MSG);
			return false;
		}

		if (rating < 0.0f || rating > 10.0f)
		{
			print(BOOK_RATING_ERROR_MSG);
			return false;
		}

		return true;
	}

	/**
	Function for validating the correctness of the given title

	@param title String reference to the title given by the user
	@returns True if it is correctly given and False otherwise
	*/
	bool validateTitle(const std::string& title)
	{
		if (title.empty() || hasOnlySpaces(title))
		{
			print(BOOK_TITLE_ERROR_MSG);
			return false;
		}

		return true;
	}

	/**
	Function for validating the correctness of the given author

	@param author String reference to the author given by the user
	@returns True if it is correctly given and False otherwise
	*/
	bool validateAuthor(const std::string& author)
	{
		if (author.empty() || hasOnlySpaces(author))
		{
			print(BOOK_AUTHOR_ERROR_MSG);
			return false;
		}

		return true;
	}

	/**
	Function for validating the correctness of the given genre

	@param genre String reference to the genre given by the user
	@returns True if it is correctly given and False otherwise
	*/
	bool validateGenre(const std::string& genre)
	{
		if (genre.empty() || hasOnlySpaces(genre))
		{
			print(BOOK_GENRE_ERROR_MSG);
			return false;
		}

		return true;
	}

	/**
	Function for validating the correctness of the given keywords

	@param keywords String reference to the keywords given by the user
	@returns True if it is correctly given and False otherwise
	*/
	bool validateKeywords(const std::vector<std::string>& keywords)
	{
		if (keywords.empty())
		{
			print(BOOK_KEYWORDS_ERROR_MSG);
			return false;
		}

		return true;
	}

	/**
	Function for validating the correctness of the given description

	@param description String reference to the description given by the user
	@returns True if it is correctly given and False otherwise
	*/
	bool validateDescription(const std::string& description)
	{
		if (description.empty() || hasOnlySpaces(description))
		{
			print(BOOK_DESCRIPTION_ERROR_MSG);
			return false;
		}

		return true;
	}
};
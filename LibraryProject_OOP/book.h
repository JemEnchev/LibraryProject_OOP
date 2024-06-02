#pragma once
#include <string>
#include <vector>

/**
Class for the books in the library system

@brief This class contains and gives information about
the books in the library system, including their titles, 
authors, descriptions, ratings, release year, etc.
*/
class Book
{
public:
	Book(const std::string&, 
		 const std::string&, 
		 const std::string&, 
		 const std::string&, 
		 const std::vector<std::string>&, 
		 const int, 
		 const int, 
		 const float);

	const std::string& getTitle() const;
	const std::string& getAuthor() const;
	const std::string& getGenre() const;
	const std::string& getDescription() const;
	const std::vector<std::string>& getKeywords() const;
	int getId() const;
	int getYear() const;
	float getRating() const;

private:
	/**
	Book title
	*/
	std::string title;
	/**
	Book author
	*/
	std::string author;
	/**
	Book genre
	*/
	std::string genre;
	/**
	Book description
	*/
	std::string description;
	/**
	Book keywords
	*/
	std::vector<std::string> keywords;
	/**
	Book id
	*/
	int id;
	/**
	Book year
	*/
	int year;
	/**
	Book rating
	*/
	float rating;
};


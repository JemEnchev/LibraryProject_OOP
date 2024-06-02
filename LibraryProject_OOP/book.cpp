#include "book.h"

/// Constructor for the book class
/// @param _title Holds the book title
/// @param _author Holds the book author
/// @param _genre Holds the book genre
/// @param _description Holds the book description
/// @param _keywords Holds the book keywords
/// @param _id Holds the book id
/// @param _year Holds the book year
/// @param _rating Holds the book rating
Book::Book(const std::string& _title, 
		   const std::string& _author, 
	       const std::string& _genre, 
		   const std::string& _description, 
		   const std::vector<std::string>& _keywords, 
		   const int _id, 
		   const int _year, 
		   const float _rating)
	: title(_title), 
	  author(_author), 
	  genre(_genre), 
	  description(_description), 
	  keywords(_keywords),
	  id(_id),
	  year(_year),
	  rating(_rating)
{}

/// Getter for the book title
/// ~~~.cpp
/// const std::string& Book::getTitle() const
///{
///	return this->title;
///}
/// ~~~
/// @returns Returns a std::string reference to the book's title</returns>
const std::string& Book::getTitle() const
{
	return this->title;
}

/// Getter for the book author
///~~~.cpp
///const std::string& Book::getAuthor() const
///{
///	return this->author;
///}
///~~~
/// @returns Returns a std::string reference to the book's author</returns>
const std::string& Book::getAuthor() const
{
	return this->author;
}

/// Getter for the book genre
/// ~~~.cpp
/// const std::string& Book::getGenre() const
///{
///	return this->genre;
///}
/// ~~~
/// @returns Returns a std::string reference to the book's genre</returns>
const std::string& Book::getGenre() const
{
	return this->genre;
}

/// Book description getter
/// ~~~.cpp
/// const std::string& Book::getDescription() const
///{
///	return this->description;
///}
/// ~~~
/// @returns Returns a std::string reference to the book's description</returns>
const std::string& Book::getDescription() const
{
	return this->description;
}

/// Book keywords getter
/// ~~~.cpp
/// const std::vector<std::string>& Book::getKeywords() const
///{
///	return this->keywords;
///}
/// ~~~
/// @returns Returns a std::vector to the book's keywords</returns>
const std::vector<std::string>& Book::getKeywords() const
{
	return this->keywords;
}

/// Book id getter
/// ~~~.cpp
/// int Book::getId() const
///{
///	return this->id;
///}
/// ~~~
/// @returns Returns an integer which represents the book's id</returns>
int Book::getId() const
{
	return this->id;
}

/// Book year getter
/// ~~~.cpp
/// int Book::getYear() const
///{
///	return this->year;
///}
/// ~~~
/// @returns Returns an integer which represents the year in which the book was written</returns>
int Book::getYear() const
{
	return this->year;
}

/// Book rating getter
/// ~~~.cpp
/// float Book::getRating() const
///{
///	return this->rating;
///}
/// ~~~
/// @returns Returns a float value which represents the book's rating</returns>
float Book::getRating() const
{
	return this->rating;
}


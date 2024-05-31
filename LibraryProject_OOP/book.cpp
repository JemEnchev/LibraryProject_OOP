#include "book.h"

/// Конструктор на класа за книга
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

/// Селектор за заглавието на книгата
const std::string& Book::getTitle() const
{
	return this->title;
}

/// Селектор за автора на книгата
const std::string& Book::getAuthor() const
{
	return this->author;
}

const std::string& Book::getGenre() const
{
	return this->genre;
}

const std::string& Book::getDescription() const
{
	return this->description;
}

const std::vector<std::string>& Book::getKeywords() const
{
	return this->keywords;
}

int Book::getId() const
{
	return this->id;
}

int Book::getYear() const
{
	return this->year;
}

float Book::getRating() const
{
	return this->rating;
}


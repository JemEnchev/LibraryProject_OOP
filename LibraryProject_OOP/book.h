#pragma once
#include <string>
#include <vector>

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

	std::string getTitle() const;
	std::string getAuthor() const;
	std::string getGenre() const;
	std::string getDescription() const;
	std::vector<std::string> getKeywords() const;
	int getId() const;
	int getYear() const;
	float getRating() const;

private:
	std::string title;
	std::string author;
	std::string genre;
	std::string description;
	std::vector<std::string> keywords;
	int id;
	int year;
	float rating;
};


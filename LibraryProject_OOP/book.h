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

	const std::string& getTitle() const;
	const std::string& getAuthor() const;
	const std::string& getGenre() const;
	const std::string& getDescription() const;
	const std::vector<std::string>& getKeywords() const;
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


#include "helperFunctions.h"
#include "messages.h"
#include <iostream>

namespace HelperFunctions
{
	/**
	Function for dividing a given string into separate words

	@param command The command line from the user input
	@returns Returns vector containing the words
	*/
	std::vector<std::string> divideString(const std::string& command) 
	{
		// If there are whitespaces before the first word
		size_t start = 0;
		while (true)
		{
			if (command[start] != ' ') break;
			start++;
		}

		if (start == command.size())
		{
			print(CMD_DOESNT_EXIST_MSG);
			std::vector<std::string> empty = {};
			return empty;
		}

		std::vector<std::string> parts;
		std::string temp;

		for (size_t i = start; i < command.size(); i++)
		{
			// Checking if the word has ended
			if (command[i] != ' ')
			{
				temp.push_back(command[i]);

				// Checking if we are at the last symbol and pushing 
				// the gathered data into the vector
				// This way we do not lose the last word
				if (i + 1 == command.size())
				{
					parts.push_back(temp);
				}
				continue;
			}

			// Pushing the constructed word and clearing the 
			// temp variable for the next one
			parts.push_back(temp);
			temp.clear();
		}

		// Returning the vector
		return parts;
	}

	/**
	Function for checking if a given command matches a given size

	@param command The command line from the user input
	@param size The number of words that the command line should have
	@returns Returns True if the size is correct and False otherwise
	*/
	bool checkCommandSize(std::vector<std::string>& command, size_t size) 
	{
		if (command.size() == size) return true;

		print(CMD_DOESNT_EXIST_MSG);
		return false;
	}

	/**
	Function for removing the first element of a given vector

	@param vector The vector which first element we want to remove
	@returns Returns the first word of the vector
	*/
	std::string removeFirst(std::vector<std::string>& vector) 
	{
		if (vector.empty()) return "";

		std::string first = vector[0];
		vector.erase(vector.begin());

		return first;
	}

	/**
	Function for making all the letters in a given string lower case

	@param input Reference to the string which we want to make lower case
	@returns Returns string that is the same as the input but with lower case letters
	*/
	std::string toLower(const std::string& input) 
	{
		std::string result;

		for (size_t i = 0; i < input.size(); i++)
		{
			char current = input[i];

			if (current > 65 && current < 91)
			{
				current += 32;
			}

			result.push_back(current);
		}

		return result;
	}

	/**
	Function for printing a given string in the console

	@param message The string message we want to print
	*/
	void print(const std::string& message) 
	{
		std::cout << message;
	}

	/**
	Function that asks confirmational question and accepts a response

	@param question Reference to the string which represents the question
	we want to be asked in the confirmation
	@returns Returns True if the confirmation goes through and 
	False otherwise
	*/
	bool confirmation(const std::string& question) 
	{
		print(question);
		char input;
		std::cin >> input;

		while (input != 'y' && input != 'Y' &&
			input != 'n' && input != 'N')
		{
			print(CFM_WRONG_MSG);
			print(question);
			std::cin >> input;
		}

		if (input == 'y' || input == 'Y') return true;

		return false;
	}

	/**
	Function that checks if a given string has only whitespaces

	@param str Reference to the string which we want to check for whitespaces
	@returns Returns True if the string contains only whitespaces and
	False otherwise
	*/
	bool hasOnlySpaces(const std::string& str) 
	{
		for (size_t i = 0; i < str.size(); i++)
		{
			if (str[i] != ' ') return false;
		}

		return true;
	}

}
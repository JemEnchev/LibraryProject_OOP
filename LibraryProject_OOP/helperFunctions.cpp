#include "helperFunctions.h"
#include "messages.h"
#include <iostream>

namespace HelperFunctions
{

	std::vector<std::string> divideString(const std::string& command) 
	{
		// Ако преди командата има празни места
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
			// Проверяваме дали думата е свършила
			if (command[i] != ' ')
			{
				temp.push_back(command[i]);

				// Проверяваме дали сме до последния символ и вкарваме събраното дотук във вектора
				// По този начин не губим последната дума
				if (i + 1 == command.size())
				{
					parts.push_back(temp);
				}
				continue;
			}

			// Пъхаме сглобената дума във вектора и чистим временната
			parts.push_back(temp);
			temp.clear();
		}

		// Връщаме вектора
		return parts;
	}

	bool checkCommandSize(std::vector<std::string>& command, size_t size) 
	{
		if (command.size() == size) return true;

		print(CMD_DOESNT_EXIST_MSG);
		return false;
	}

	std::string removeFirst(std::vector<std::string>& vector) 
	{
		if (vector.empty()) return "";

		std::string first = vector[0];
		vector.erase(vector.begin());

		return first;
	}

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

	void print(const std::string& message) 
	{
		std::cout << message;
	}

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

	bool hasOnlySpaces(const std::string& str) 
	{
		for (size_t i = 0; i < str.size(); i++)
		{
			if (str[i] != ' ') return false;
		}

		return true;
	}

}
#include "doctest.h"
#include "helperFunctions.h"

using namespace HelperFunctions;

/**
Test for testing the functionality of the
divideString() function
*/
TEST_CASE("Testing divide string")
{
	SUBCASE("Does it return correct size vector")
	{
		std::string input = "one two three four";
		std::vector<std::string> vector = divideString(input);

		CHECK_EQ(vector.size(), 4);
	}

	SUBCASE("Does it return empty vector when given empty string")
	{
		std::string input = "";
		std::vector<std::string> vector = divideString(input);

		CHECK_EQ(vector.size(), 0);
	}

	SUBCASE("Does it return empty vector when given string with whitespaces")
	{
		std::string input = "    ";
		std::vector<std::string> vector = divideString(input);

		CHECK_EQ(vector.size(), 0);
	}
}

/**
Test for testing the functionality of the
checkCommandSize() function
*/
TEST_CASE("Testing command size")
{
	SUBCASE("Does it return true given the correct size")
	{
		std::vector<std::string> vector = { "one", "two", "three" };
		bool check = checkCommandSize(vector, 3);

		CHECK_EQ(check, 1);
	}

	SUBCASE("Does it return false given the wrong size")
	{
		std::vector<std::string> vector = { "one", "two", "three" };
		bool check = checkCommandSize(vector, 2);

		CHECK_EQ(check, 0);
	}

	SUBCASE("Does it return true given empty vector and correct size")
	{
		std::vector<std::string> vector = {};
		bool check = checkCommandSize(vector, 0);

		CHECK_EQ(check, 1);
	}

	SUBCASE("Does it return false given empty vector and wrong size")
	{
		std::vector<std::string> vector = {};
		bool check = checkCommandSize(vector, 2);

		CHECK_EQ(check, 0);
	}
}

/**
Test for testing the functionality of the
removeFirst() function
*/
TEST_CASE("Testing remove first")
{
	SUBCASE("Does it remove the first element")
	{
		std::vector<std::string> vector = { "first", "second", "third" };
		removeFirst(vector);

		CHECK_EQ(vector.size(), 2);
	}

	SUBCASE("Does it return the first element")
	{
		std::vector<std::string> vector = { "first", "second", "third" };
		std::string check = removeFirst(vector);

		CHECK_EQ(check, "first");
	}

	SUBCASE("Does it return empty string given empty vector")
	{
		std::vector<std::string> vector = {};
		std::string check = removeFirst(vector);

		CHECK_EQ(check, "");
	}
}

/**
Test for testing the functionality of the
toLower() function
*/
TEST_CASE("Testing to lower")
{
	SUBCASE("Does it return the correct string")
	{
		std::string str = "SoMethiNG";
		CHECK_EQ(toLower(str), "something");
	}

	SUBCASE("Does it return empty string")
	{
		std::string str = "";
		CHECK_EQ(toLower(str), "");
	}

	SUBCASE("Does it affect other symbols")
	{
		std::string str = "HeLLo!!!";
		CHECK_EQ(toLower(str), "hello!!!");
	}
}

/**
Test for testing the functionality of the
hasOnlySpaces() function
*/
TEST_CASE("Testing has only spaces")
{
	SUBCASE("Does it return true when given string with whitespaces")
	{
		bool check = hasOnlySpaces("   ");
		CHECK_EQ(check, 1);
	}

	SUBCASE("Does it return false when given non-empty string with symbols")
	{
		bool check = hasOnlySpaces("  sd  f ");
		CHECK_EQ(check, 0);
	}

	SUBCASE("Does it return true when given empty string")
	{
		bool check = hasOnlySpaces("");
		CHECK_EQ(check, 1);
	}
}
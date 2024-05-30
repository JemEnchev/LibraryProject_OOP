#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "bookValidation.h"

using namespace BookValidation;

TEST_CASE("id validation") 
{
	SUBCASE("Does it return true when parameters are correct")
	{
		bool check = validateId("3");
		CHECK_EQ(check, 1);
	}

	SUBCASE("Does it return false when parameters are not correct")
	{
		bool check = validateId("asd");
		CHECK_EQ(check, 0);
	}

	SUBCASE("Does it return false when parameters are empty")
	{
		bool check = validateId("");
		CHECK_EQ(check, 0);
	}
}

TEST_CASE("year validation")
{
	SUBCASE("Does it return true when parameters are correct")
	{
		bool check = validateYear("1987");
		CHECK_EQ(check, 1);
	}

	SUBCASE("Does it return false when parameters are not correct")
	{
		bool check = validateYear("uadf");
		CHECK_EQ(check, 0);
	}

	SUBCASE("Does it return true when the year is in the correct range")
	{
		bool check = validateYear("2024");
		CHECK_EQ(check, 1);
	}

	SUBCASE("Does it return false when the year is not in the correct range")
	{
		bool check = validateYear("2039");
		CHECK_EQ(check, 0);
	}

	SUBCASE("Does it return false when parameters are empty")
	{
		bool check = validateYear("");
		CHECK_EQ(check, 0);
	}
}

TEST_CASE("rating validation")
{
	SUBCASE("Does it return true when parameters are correct")
	{
		bool check = validateRating("3.7");
		CHECK_EQ(check, 1);
	}

	SUBCASE("Does it return false when parameters are not correct")
	{
		bool check = validateRating("klje");
		CHECK_EQ(check, 0);
	}

	SUBCASE("Does it return true when the rating is in the correct range")
	{
		bool check = validateRating("7.0");
		CHECK_EQ(check, 1);
	}

	SUBCASE("Does it return false when the rating is not in the correct range")
	{
		bool check = validateRating("14.8");
		CHECK_EQ(check, 0);
	}

	SUBCASE("Does it return false when parameters are empty")
	{
		bool check = validateRating("");
		CHECK_EQ(check, 0);
	}
}

TEST_CASE("title validation")
{
	SUBCASE("Does it return true when parameters are correct")
	{
		bool check = validateTitle("Some Cool Title");
		CHECK_EQ(check, 1);
	}

	SUBCASE("Does it return false when parameters are not correct")
	{
		bool check = validateTitle("    ");
		CHECK_EQ(check, 0);
	}

	SUBCASE("Does it return false when parameters are empty")
	{
		bool check = validateTitle("");
		CHECK_EQ(check, 0);
	}
}

TEST_CASE("author validation")
{
	SUBCASE("Does it return true when parameters are correct")
	{
		bool check = validateAuthor("Some Author Name");
		CHECK_EQ(check, 1);
	}

	SUBCASE("Does it return false when parameters are not correct")
	{
		bool check = validateAuthor("    ");
		CHECK_EQ(check, 0);
	}

	SUBCASE("Does it return false when parameters are empty")
	{
		bool check = validateAuthor("");
		CHECK_EQ(check, 0);
	}
}

TEST_CASE("genre validation")
{
	SUBCASE("Does it return true when parameters are correct")
	{
		bool check = validateGenre("Some Genre");
		CHECK_EQ(check, 1);
	}

	SUBCASE("Does it return false when parameters are not correct")
	{
		bool check = validateGenre("    ");
		CHECK_EQ(check, 0);
	}

	SUBCASE("Does it return false when parameters are empty")
	{
		bool check = validateGenre("");
		CHECK_EQ(check, 0);
	}
}

TEST_CASE("description validation")
{
	SUBCASE("Does it return true when parameters are correct")
	{
		bool check = validateDescription("Some Description");
		CHECK_EQ(check, 1);
	}

	SUBCASE("Does it return false when parameters are not correct")
	{
		bool check = validateDescription("    ");
		CHECK_EQ(check, 0);
	}

	SUBCASE("Does it return false when parameters are empty")
	{
		bool check = validateDescription("");
		CHECK_EQ(check, 0);
	}
}

TEST_CASE("keywords validation")
{
	SUBCASE("Does it return true when given correct parameters")
	{
		bool check = validateKeywords({"some", "keywords"});
		CHECK_EQ(check, 1);
	}

	SUBCASE("Does it return true when given wrong parameters")
	{
		bool check = validateKeywords({});
		CHECK_EQ(check, 0);
	}
}
#pragma once
/**
Header file with all the constants used in the project
*/

// Common
const std::string DIVIDER = "---------------------------------------------------------------------\n";
const std::string START_MSG = "===== Welcome to the Library System Project =====\n Type 'help' for more info...\n\n";
const std::string CMD_DOESNT_EXIST_MSG = "This command does not exist. Type help for more information.\n";
const std::string PASSWORD_SYMBOL = "*";

// Login
const std::string USER_ALREADY_LOGGED_MSG = "You are already logged in.\n";
const std::string USER_LOGGED_SUCCESSFULLY_MSG = "Welcome, ";
const std::string USER_LOGGED_FAILED_MSG = "Username and/or password are incorrect.\n";
const std::string LOGIN_USERNAME_MSG = "Username: ";
const std::string LOGIN_PASSWORD_MSG = "Password: ";

// Logout
const std::string USER_LOGOUT_MSG = "You logged out successfully.\n";
const std::string USER_NULL_LOGOUT_MSG = "You are not logged in.\n";

// User
const std::string USERS_FILE = "users.txt";
const std::string USER_FILE_FAILED_MSG = "Couldn't open the users file.\n";
const std::string USER_EXISTS_MSG = "User with this username already exists.\n";
const std::string USER_DOESNT_EXISTS_MSG = "User with this username does not exist.\n";
const std::string USER_REMOVED_SUCCESSFULLY_MSG = "User removed successfully!\n";
const std::string USER_ADDED_SUCCESSFULLY_MSG = "User added successfully!\n";
const std::string USER_ACCESS_DENIED_MSG = "Access denied.\n";
const std::string USER_NONUSER_ACCESS_DENIED_MSG = "You should login first.\n";

// Book
const std::string BOOK_ID_ERROR_MSG = "Id should be a number.\n";
const std::string BOOK_YEAR_ERROR_MSG = "Year should be a number in the range [0 - 2024].\n";
const std::string BOOK_RATING_ERROR_MSG = "Rating should be a number in the range [0.00 - 10.00].\n";
const std::string BOOK_TITLE_ERROR_MSG = "Title should not be empty.\n";
const std::string BOOK_AUTHOR_ERROR_MSG = "Author should not be empty.\n";
const std::string BOOK_GENRE_ERROR_MSG = "Genre should not be empty.\n";
const std::string BOOK_KEYWORDS_ERROR_MSG = "Keywords should not be empty.\n";
const std::string BOOK_DESCRIPTION_ERROR_MSG = "Description should not be empty.\n";
const std::string BOOK_DOESNT_EXISTS_MSG = "Book with this id doesn't exist.\n";
const std::string BOOK_REMOVED_SUCCESSFULLY_MSG = "Book removed successfully!\n";
const std::string BOOK_ADD_ID_MSG = "Id: ";
const std::string BOOK_ADD_TITLE_MSG = "Title: ";
const std::string BOOK_ADD_AUTHOR_MSG = "Author: ";
const std::string BOOK_ADD_GENRE_MSG = "Genre: ";
const std::string BOOK_ADD_DESCRIPTION_MSG = "Description: ";
const std::string BOOK_ADD_YEAR_MSG = "Year: ";
const std::string BOOK_ADD_RATING_MSG = "Rating: ";
const std::string BOOK_ADD_KEYWORDS_MSG = "Keywords: ";
const std::string BOOK_ADDED_SUCCESSFULLY_MSG = "Book added succesfully!\n";
const std::string BOOK_EXISTS_MSG = "Book with this id already exists.\n";
const std::string BOOK_TITLE_PRINT_MSG       = "      [Title]: ";
const std::string BOOK_AUTHOR_PRINT_MSG      = "     [Author]: ";
const std::string BOOK_GENRE_PRINT_MSG       = "      [Genre]: ";
const std::string BOOK_YEAR_PRINT_MSG        = "       [Year]: ";
const std::string BOOK_RATING_PRINT_MSG      = "     [Rating]: ";
const std::string BOOK_KEYWORDS_PRINT_MSG    = "   [Keywords]: ";
const std::string BOOK_DESCRIPTION_PRINT_MSG = "[Description]: ";
const std::string BOOK_SORTED_MSG = "Books sorted.\n";
const std::string BOOK_FIND_COUNTER_MSG = "Books found: ";

// File
const std::string FILE_NOT_LOADED_MSG       = "There is no opened book file.\n";
const std::string FILE_LOADED_COUNT_MSG     = "Total books loaded: ";
const std::string FILE_FAILED_MSG           = "Couldn't open the book file.\n";
const std::string FILE_NOTHING_TO_CLOSE_MSG = "There is no loaded file to close.\n";
const std::string FILE_NOTHING_TO_SAVE_MSG  = "There is no loaded file to save.\n";
const std::string FILE_DOESNT_EXIST_MSG     = "File with this name does not exist.\n";
const std::string FILE_ALREADY_EXISTS_MSG   = "File with this name already exists.\n";
const std::string FILE_OPENED_MSG		   = "File opened.\n";
const std::string FILE_CLOSED_MSG		   = "File closed.\n";
const std::string FILE_SAVED_MSG			   = "File saved.\n";

// Confirmations
const std::string CFM_WRONG_MSG       = "Use 'y' or 'Y' for 'Yes' and 'n' or 'N' for 'No'.\n";
const std::string CFM_EXIT_MSG        = "Are you sure you want to exit ? [y/n]: ";
const std::string CFM_USER_REMOVE_MSG = "Are you sure you want to remove this user ? [y/n]: ";
const std::string CFM_BOOK_REMOVE_MSG = "Are you sure you want to remove this book ? [y/n]: ";
const std::string CFM_FILE_CLOSE_MSG  = "Are you sure you want to close this file ? [y/n]: ";
const std::string CFM_BOOK_SAVE_MSG   = "Are you sure you want to save this file ? [y/n]: ";

// Help menu (non-admins)
const std::string HELP_MENU_MSG       = "=== Help Menu ===\n";
const std::string HELP_DISCL_1_MSG    = "Parameters enclosed with brackets [] are optional.\n";
const std::string HELP_DISCL_2_MSG    = "Parameters enclosed with angle brackets <> are user entered values.\n";
const std::string HELP_DISCL_3_MSG    = "Do not include the [] or <> in the command.\n";
const std::string HELP_LOGIN_MSG      = "	login                          - Used for logging in the library system.\n";
const std::string HELP_LOGOUT_MSG     = "	logout                         - Used for logging out from the library system.\n";
const std::string HELP_OPEN_MSG       = "	open <name>                    - Used for loading a file into the memory.\n";
const std::string HELP_CLOSE_MSG      = "	close                          - Usef for clearing the memory without saving the changes.\n";
const std::string HELP_SAVE_MSG       = "	save                           - Used for saving the changes in the file you opened.\n";
const std::string HELP_SAVEAS_MSG     = "	saveas <name>                  - Used for saving the changes in a new file.\n";
const std::string HELP_EXIT_MSG       = "	exit                           - Used for exiting the program.\n";
const std::string HELP_BOOKS_VIEW_MSG = "	books view                     - Used for viewing all the books by names.\n";
const std::string HELP_BOOKS_ALL_MSG  = "	books all                      - Used for viewing all the books with all their information.\n";
const std::string HELP_BOOKS_FIND_MSG = "	books find <option> <string>   - Used for finding a book by given criteria (Title, Author, Genre).\n";
const std::string HELP_BOOKS_SORT_MSG = "	books sort <option> [asc|desc] - Used for sorting the books by given criteria.\n";
const std::string HELP_BOOK_INFO_MSG  = "	book info <id>                 - Used for finding a book by its system id.\n";
const std::string HELP_HELP_MSG       = "	help                           - Opens this menu.\n";

// Help menu (admins)
const std::string HELP_USER_ADD_MSG   = "	user add <username> <password> <isAdmin> : Admin -> 1, Non-admin -> 0\n";
const std::string HELP_USER_RMV_MSG   = "	user remove <username>\n";
const std::string HELP_BOOK_ADD_MSG   = "	book add <Id> <Title> <Author> <Genre> <Description> <Year> <Rating> [Keywords]\n";
const std::string HELP_BOOK_RMV_MSG   = "	book remove <id>\n";



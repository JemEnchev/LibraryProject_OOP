#pragma once
using std::string;

const string USERS_FILE = "users.txt";
const string USER_FILE_FAILED_MSG = "Couldn't open the users file.\n";

const string START_MSG = "===== Welcome to the Library System Project =====\n Type 'help' for more info...\n\n";
const string CMD_DOESNT_EXIST_MSG = "This command does not exist. Type help for more information.\n";

// Login
const string USER_ALREADY_LOGGED_MSG = "You are already logged in.\n";
const string USER_LOGGED_SUCCESSFULLY_MSG = "Welcome, ";
const string USER_LOGGED_FAILED_MSG = "Username and/or password are incorrect.\n";
const string LOGIN_USERNAME_MSG = "Username: ";
const string LOGIN_PASSWORD_MSG = "Password: ";

// Logout
const string USER_LOGOUT_MSG = "You logged out successfully.\n";
const string USER_NULL_LOGOUT_MSG = "You are not logged in.\n";

// User
const string USER_EXISTS_MSG = "User with this username already exists.\n";
const string USER_DOESNT_EXISTS_MSG = "User with this username does not exist.\n";
const string USER_REMOVED_SUCCESSFULLY_MSG = "User removed successfully!\n";
const string USER_ADDED_SUCCESSFULLY_MSG = "User added successfully!\n";
const string USER_ACCESS_DENIED_MSG = "Access denied.\n";

// Book
const string BOOK_FILE_FAILED_MSG = "Couldn't open the book file.\n";
const string BOOK_ID_ERROR_MSG = "Id should be a number.\n";
const string BOOK_YEAR_ERROR_MSG = "Year should be a number in the range [0 - 2024].\n";
const string BOOK_RATING_ERROR_MSG = "Rating should be a number in the range [0.00 - 10.00].\n";
const string BOOK_TITLE_ERROR_MSG = "Title should not be empty.\n";
const string BOOK_AUTHOR_ERROR_MSG = "Author should not be empty.\n";
const string BOOK_GENRE_ERROR_MSG = "Genre should not be empty.\n";
const string BOOK_DESCRIPTION_ERROR_MSG = "Description should not be empty.\n";
const string BOOK_DOESNT_EXISTS_MSG = "Book with this id doesn't exist.\n";
const string BOOK_REMOVED_SUCCESSFULLY_MSG = "Book removed successfully!\n";
const string BOOK_ADD_ID_MSG = "Id: ";
const string BOOK_ADD_TITLE_MSG = "Title: ";
const string BOOK_ADD_AUTHOR_MSG = "Author: ";
const string BOOK_ADD_GENRE_MSG = "Genre: ";
const string BOOK_ADD_DESCRIPTION_MSG = "Description: ";
const string BOOK_ADD_YEAR_MSG = "Year: ";
const string BOOK_ADD_RATING_MSG = "Rating: ";
const string BOOK_ADD_KEYWORDS_MSG = "Keywords (optional): ";
const string BOOK_ADDED_SUCCESSFULLY_MSG = "Book added succesfully!\n";
const string BOOK_EXISTS_MSG = "Book with this id already exists.\n";
const string BOOK_TITLE_PRINT_MSG       = "      [Title]: ";
const string BOOK_AUTHOR_PRINT_MSG      = "     [Author]: ";
const string BOOK_GENRE_PRINT_MSG       = "      [Genre]: ";
const string BOOK_YEAR_PRINT_MSG        = "       [Year]: ";
const string BOOK_RATING_PRINT_MSG      = "     [Rating]: ";
const string BOOK_KEYWORDS_PRINT_MSG    = "   [Keywords]: ";
const string BOOK_DESCRIPTION_PRINT_MSG = "[Description]: ";

// Confirmations
const string CFM_WRONG_MSG = "Use 'y' or 'Y' for 'Yes' and 'n' or 'N' for 'No'.\n";
const string CFM_EXIT_MSG = "Are you sure you want to exit ? [y/n]: ";
const string CFM_USER_REMOVE_MSG = "Are you sure you want to remove this user ? [y/n]: ";
const string CFM_BOOK_REMOVE_MSG = "Are you sure you want to remove this book ? [y/n]: ";

// Help menu (non-admins)
const string HELP_MENU_MSG       = "=== Help Menu ===\n";
const string HELP_DISCL_1_MSG    = "Parameters enclosed with brackets [] are optional.\n";
const string HELP_DISCL_2_MSG    = "Parameters enclosed with angle brackets <> are user entered values.\n";
const string HELP_DISCL_3_MSG    = "Do not include the [] or <> in the command.\n";
const string HELP_LOGIN_MSG      = "	login                          - Used for logging in the library system.\n";
const string HELP_LOGOUT_MSG     = "	logout                         - Used for logging out from the library system.\n";
const string HELP_OPEN_MSG       = "	open <name>                    - Used for loading a file into the memory.\n";
const string HELP_CLOSE_MSG      = "	close                          - Usef for clearing the memory without saving the changes.\n";
const string HELP_SAVE_MSG       = "	save                           - Used for saving the changes in the file you opened.\n";
const string HELP_SAVEAS_MSG     = "	saveas <name>                  - Used for saving the changes in a new file.\n";
const string HELP_EXIT_MSG       = "	exit                           - Used for exiting the program.\n";
const string HELP_BOOKS_VIEW_MSG = "	books view                     - Used for viewing all the books by names.\n";
const string HELP_BOOKS_ALL_MSG  = "	books all                      - Used for viewing all the books with all their information.\n";
const string HELP_BOOKS_FIND_MSG = "	books find <option> <string>   - Used for finding a book by given criteria.\n";
const string HELP_BOOKS_SORT_MSG = "	books sort <option> [asc|desc] - Used for sorting the books by given criteria.\n";
const string HELP_BOOK_INFO_MSG  = "	book info <id>                 - Used for finding a book by its system id.\n";
const string HELP_HELP_MSG       = "	help                           - Opens this menu.\n";

// Help menu (admins)
const string HELP_USER_ADD_MSG   = "	user add <username> <password> <isAdmin> : Admin -> 1, Non-admin -> 0\n";
const string HELP_USER_RMV_MSG   = "	user remove <username>\n";
const string HELP_BOOK_ADD_MSG   = "	book add <Id> <Title> <Author> <Genre> <Description> <Year> <Rating> [Keywords]\n";
const string HELP_BOOK_RMV_MSG   = "	book remove <id>\n";



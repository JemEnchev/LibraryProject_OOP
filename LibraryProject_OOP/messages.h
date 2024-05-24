#pragma once
using std::string;

const string USERS_FILE = "users.txt";

const string START_MSG = "===== Welcome to the Library System Project =====\n Type 'help' for more info...\n";
const string CMD_DOESNT_EXIST_MSG = "This command does not exist. Type help for more information.\n";

// Login
const string USER_ALREADY_LOGGED_MSG = "You are already logged in.\n";
const string USER_LOGGED_SUCCESSFULLY_MSG = "Welcome, ";
const string USER_LOGGED_FAILED_MSG = "Your username and/or password are incorrect.\n";
const string LOGIN_USERNAME_MSG = "Username: ";
const string LOGIN_PASSWORD_MSG = "Password: ";

// User
const string USER_LOGOUT_MSG = "You logged out successfully.\n";
const string USER_FILE_FAILED_MSG = "Couldn't open the users file.\n";
const string USER_EXISTS_MSG = "User with this username already exists!\n";

// Confirmations
const string CFM_WRONG_MSG = "Use 'y' or 'Y' for 'Yes' and 'n' or 'N' for 'No'.\n";
const string CFM_EXIT_MSG = "Are you sure you want to exit ? [y/n]: ";

// Help menu (non-admins)
const string HELP_MENU_MSG       = "=== Help Menu ===\n";
const string HELP_DISCL_1_MSG    = "Parameters enclosed with brackets [] are optional.\n";
const string HELP_DISCL_2_MSG    = "Parameters enclosed with angle brackets <> are user entered values.\n";
const string HELP_DISCL_3_MSG    = "Do not include the [] or <> in the command.\n";
const string HELP_LOGIN_MSG      = "login                          - Used for logging in the library system.\n";
const string HELP_LOGOUT_MSG     = "logout                         - Used for logging out from the library system.\n";
const string HELP_OPEN_MSG       = "open <name>                    - Used for loading a file into the memory.\n";
const string HELP_CLOSE_MSG      = "close                          - Usef for clearing the memory without saving the changes.\n";
const string HELP_SAVE_MSG       = "save                           - Used for saving the changes in the file you opened.\n";
const string HELP_SAVEAS_MSG     = "saveas <name>                  - Used for saving the changes in a new file.\n";
const string HELP_EXIT_MSG       = "exit                           - Used for exiting the program.\n";
const string HELP_BOOKS_VIEW_MSG = "books view                     - Used for viewing all the books by names.\n";
const string HELP_BOOKS_ALL_MSG  = "books all                      - Used for viewing all the books with all their information.\n";
const string HELP_BOOKS_FIND_MSG = "books find <option> <string>   - Used for finding a book by given criteria.\n";
const string HELP_BOOKS_SORT_MSG = "books sort <option> [asc|desc] - Used for sorting the books by given criteria.\n";
const string HELP_BOOK_INFO_MSG  = "book info <id>                 - Used for finding a book by its system id.\n";
const string HELP_HELP_MSG       = "help                           - Opens this menu.\n";

// Help menu (admins)
const string HELP_BOOK_ADD_MSG   = "book add <id> <Title> <Author> <Genre> <Description> <Year> <Rating> <Keywords>\n";
const string HELP_BOOK_RMV_MSG   = "book remove <id>\n";
const string HELP_USER_ADD_MSG   = "user add <username> <password> <isAdmin> : Admin -> 1, Non-admin -> 0\n";
const string HELP_USER_RMV_MSG   = "user remove <username>\n";


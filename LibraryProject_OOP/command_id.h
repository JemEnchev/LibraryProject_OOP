#pragma once
/// Enumeration for hashing the first word of the user input
enum Command_ID
{					//___
	open,			//   |
	close,			//   |
	save,			//   |
	saveas,			//   |
	help,			//   |
	login,			//   | For library system
	logout,			//   |
	quit,			//   |
	books,			//   |
	users,			//   |
	error,			//___|
	user_all,		//   |
	user_add,		//   | For user manager
	user_remove,	//___|
	book_all,		//   |
	book_view,		//   |
	book_find,		//   |
	book_add,		//   | For book manager
	book_remove,	//   |
	book_sort,		//   |
	book_info		//___|
};
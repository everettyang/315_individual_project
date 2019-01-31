#include "controller.h"

Controller::Controller() {
	function_code["B"] = B; 
	function_code["D"] = D; 
	function_code["M"] = M; 
	function_code["C"] = C; 
	function_code["A"] = A; 
	function_code["GC"] = GC; 
	function_code["GS"] = GS; 
	function_code["GB"] = GB; 
	function_code["PB"] = PB; 
	function_code["PC"] = PC; 
	function_code["PY"] = PY; 
	function_code["PD"] = PD; 
	function_code["PM"] = PM; 
}

void Controller::bFunction() {
	//takes a 13 digit ISBN and
	//stores a new book object
	//with given title and ISBN
	string string_key = split_command[1];
	if (!isISBN(string_key)) {
		cout << "Not valid ISBN (B Function" << endl;
		return;
	}
	ISBN id = strtoull(string_key.c_str(), NULL, 10); //convert string to 
								//unsigned long long (typedef to ISBN)
	string title;
	title = split_command[2];
	for (int i = 3; i < split_command.size(); ++i)
		title += " " + split_command[i];

	Book b(id, title);
	books[id] = b;
}

void Controller::dFunction() {
	//define some characteristic of book
	string string_key = split_command[1];
	if (!isISBN(string_key))
		cout << "Not valid ISBN (D Function)" << endl;
	ISBN key = strtoull(string_key.c_str(), NULL, 10);
	std::string val;
	val = split_command[3];
	for (int i = 4; i < split_command.size(); ++i)
		val += " " + split_command[i];
	books[key].defineAttribute(val, split_command[2].c_str());
}

void Controller::mFunction() {
	//defines a cost for a certain version of a given book
	string string_key = split_command[1];
	if (!isISBN(string_key)) {
		cout << "Invalid ISBN! (M function)" << endl;
		return;
	}
	ISBN key = strtoull(string_key.c_str(), NULL, 10);
	string cost = split_command[2];
	if (!isCost(cost)) {
		cout << "Invalid price! (M Function)" << endl;
		return;
	}
	string book_type = split_command[3];
	books[key].setCost(stod(cost), book_type.c_str());
}

void Controller::cFunction() {
	
	//given course info, create new
	//course object and stores it in map
	//with all other defined courses
	string course_code = split_command[1];
	int course_num = stoi(split_command[2]);
	string course_title = split_command[3];

	if (checkCourse(course_code, split_command[2])) {

		for (int i = 4; i < split_command.size(); ++i)
			course_title += " " + split_command[i];
		Course c(course_code, course_num, course_title);
		courses[course_code][course_num] = c; //add to map of all courses
	}
}

void Controller::aFunction() {
	//assigns a course to a book

	//course info
	string course_code = split_command[2];
	int course_num = stoi(split_command[3]);
	int section = stoi(split_command[4]);

	//book info
	if (checkCourse(course_code, split_command[3], split_command[4])) {
		string string_key = split_command[1];
		if (!isISBN(string_key)) {
			cout << "Invalid ISBN (A function)" << endl;
			return;
		}
		ISBN key = strtoull(string_key.c_str(), NULL, 10);
		string required = split_command[5];

		try {
			courses.at(course_code).at(course_num).assignBook(section, books.at(key), required);
		}
		catch (const out_of_range& err) {
			cout << "Either ISBN or Course is not valid! (A function)\n" << endl;
		}
	}
}

void Controller::gcFunction() {
	//print all books for all section of a course
	string course_code = split_command[1];
	if (checkCourse(course_code, split_command[2])) {
		int course_num = stoi(split_command[2]);
		cout << "BOOKS FOR " << course_code << " " <<  course_num <<
				"\n------------------------------" << endl;
		try {
			courses.at(course_code).at(course_num).getAllBooks(true); //prints the books
		}
		catch (const out_of_range& err) {
			cout << "Course is not defined! (GC function)\n" << endl;
		}
		cout << "\n------------------------------" << endl;
	}
}

void Controller::gsFunction() {
	//print all books for a given section
	string course_code = split_command[1];
	if (checkCourse(course_code, split_command[2], split_command[3])) {
		int course_num = stoi(split_command[2]);
		int section = stoi(split_command[3]);
		cout << "BOOKS FOR " << course_code << " " << course_num << " SECTION " << section 
				<< " \n(selected using GS command):\n" <<
				"------------------------------" << endl;
		try {
			courses.at(course_code).at(course_num).printBookForSection(section); //prints the books for a section
		}
		catch (const out_of_range& err) {
			cout << "Course is not defined! (GC function)\n" << endl;
		}
		cout << "\n------------------------------" << endl;
	}
}

void Controller::gbFunction() {
	//print all member variable of a selected book (all its information)
	string string_key = split_command[1];
	if (!isISBN(string_key)) {
		cout << "Invalid ISBN (GB Function)" << endl;
		return;
	}
	ISBN key = strtoull(string_key.c_str(), NULL, 10);
	cout << "SELECTED BOOK (" << key << "):\n" <<
			"------------------------------" << endl;
	map<ISBN, Book>::iterator it = books.find(key); 
	if (it == books.end())
		cout << "Book not found!\n" << endl;
	else {
		Book b = it->second;
		b.printAll();
	}
}

void Controller::pbFunction() {
	//list all books defined
	cout << "ALL BOOKS DEFINED:\n" 
		"------------------------------" << endl;
	for (map<ISBN, Book>::iterator it = books.begin();
		it != books.end(); ++it) {
		it->second.printAll();
	}

	cout << "------------------------------\n" << endl;
}

void Controller::pcFunction() {
	//list all courses defined
	cout << "ALL COURSES DEFINED:\n" 
		"------------------------------"<< endl;
	for (map<string, map<int, Course> >::iterator it = courses.begin();
		it != courses.end(); ++it) {
		for (map<int, Course>::iterator it1 = it->second.begin();
			it1 != it->second.end(); ++it1) {
				it1->second.printAll();
		}
	}

	cout << "------------------------------\n" << endl;
}

void Controller::pyFunction() {
	//prints all books that are
	//same age or newer than given date
	vector<string> split_date;
	string date = split_command[1];
	if (!isDate(date)) {
		cout << "Invalid date (PY function)" << endl;
		return;
	}
	split_date = split_str(date, '/');
	int month = stoi(split_date[0]);
	int year = stoi(split_date[1]);


	cout << "ALL BOOKS NEWER THAN " << date << ":\n" <<
		"------------------------------" << endl;
	for (map<ISBN, Book>::iterator it = books.begin();
		it != books.end(); ++it) {

		vector<string> book_split_date;
		string book_date = it->second.getDate();
		if (book_date == "") {
			cout << "No date defined for " << it->second.getTitle() << 
				'\n' << endl;
			continue;
		}
		book_split_date = split_str(book_date, '/');
		int book_month = stoi(book_split_date[0]);
		int book_year = stoi(book_split_date[1]);

		if (((book_month >= month) && (book_year >= year)) ||
			(book_year > year)) {
			it->second.printAll();
		}
	}
	cout << "------------------------------\n" << endl;
}

void Controller::pdFunction() {
	//print all books in a certain department
	string dept_code = split_command[1];
	if (!checkCourse(dept_code)) return;
	//vector<Book> books_in_department = books;
	if (courses.find(dept_code) == courses.end()) {
		cout << dept_code << " department does not exist (PD function)\n" << endl;
		return;
	}
	cout << "ALL BOOKS USED IN " << dept_code << 
		"\n------------------------------" << endl;
	for (map<int, Course>::iterator it = courses[dept_code].begin();
		it != courses[dept_code].end(); ++it) {
		vector<Book> all_books = it->second.getListOfAllBooks(); //first arg false because dont 
									  //want to print by section TODO: define a new function
		for (int i = 0; i < all_books.size(); ++i) {
			all_books[i].printAll();
		}
	}
	cout << "------------------------------\n" << endl;
}

void Controller::pmFunction() {
	/*prints the average maximum and average minimum cost
	 * of all books in the department
	 * Formula being used here:
	 * For minimum -
	 * sum of all instances of required books prices (the cheapest version) of all books in
	 * the department divided by number of sections that have required books.
	 * For maximum -
	 * sum of all book prices (the most expensive version) divided
	 * by the number of sections that have books assigned. */
	string dept_code = split_command[1];
	if (!checkCourse(dept_code)) return;
	if (courses.find(dept_code) == courses.end()) {
		cout << dept_code << " department does not exist (PM function)\n" << endl;
		return;
	}
	double total_cost_max = COST_UNDEFINED;
	double total_cost_min = COST_UNDEFINED;
	int total_sections = 0; //total section with books (required and optional)
	int total_required_sections = 0; //total sections that require books

	for (map<int, Course>::iterator it = courses[dept_code].begin();
		it != courses[dept_code].end(); ++it) {
		vector<pair<vector<Book>, vector<Book> > > books_for_all_sections = it->second.getAllBooks(false); //get a vector of pairs that 
															//contain a pair (required, optional) for that section. Each element is a section
		total_sections += books_for_all_sections.size(); //each element in the vector means
								//that a section was assigned at least one book
								//(either required or optional vector is non-zero

		cout << "Total Sections: " << total_sections << endl;
		for (int i = 0; i < books_for_all_sections.size(); ++i) {
			vector<Book> required_books = books_for_all_sections[i].first;
			vector<Book> optional_books = books_for_all_sections[i].second;
			vector<Book> all_books = required_books;
			all_books.insert(all_books.end(), optional_books.begin(), optional_books.end());

			if (required_books.size() > 0) {
				total_required_sections += 1;
			}

			for (int i = 0; i < all_books.size(); ++i) {
				double max_cost = all_books[i].getMaxCost();
				//make sure cost is defined for current book
				if (max_cost != COST_UNDEFINED) { 
					if (total_cost_max != COST_UNDEFINED)
						total_cost_max += max_cost;
					else
						total_cost_max = max_cost;
				}
			}
			for (int i = 0; i < required_books.size(); ++i) {
				double min_cost = required_books[i].getMinCost();
				if (min_cost != COST_UNDEFINED) {
					if (total_cost_min != COST_UNDEFINED)
						total_cost_min += min_cost;
					else
						total_cost_min = min_cost;
				}
			}
		}
	}
	
	//if there is no book with defined cost
	cout << "Total Required sections: " << total_required_sections << endl;
	if (total_sections > 0 && total_cost_max != COST_UNDEFINED) { //make sure we have books to compute with
		cout << "Total Max Cost " << total_cost_max << endl;
		cout << "AVERAGE MAXIMUM COST OF BOOKS PER SECTION IN " << dept_code << ":" << '\n'<<
			total_cost_max / total_sections << '\n' << endl;
		if (total_required_sections > 0 && total_cost_min != COST_UNDEFINED) {
			cout << "AVERAGE MINIMUM COST OF BOOKS PER SECTION IN " << dept_code << ":" << '\n'<<
				total_cost_min / total_required_sections << '\n' << endl;
		}
		else
			cout << "CANNOT COMPUTE AVERAGE MINIMUM BECAUSE NO COST FOUND FOR REQUIRED BOOKS\n" << endl;
		return;
	}

	cout << "CANNOT COMPUTE AVERAGE MAXIMUM OR MINIMUM BECAUSE NO COST FOUND\n" << endl;
}

void Controller::parseUserInput(string& _command) {
	//remove newline from end of command string
	_command.erase(_command.size() - 1);
	split_command = split_str(_command, ' ');
}

void Controller::run() {
	//gets user input
	//line by line and feed into appropriate function
	string command;
	while (getline(cin, command)) {
		parseUserInput(command);
		string input_code = split_command[0];
		if (function_code.find(input_code) == function_code.end()) {
			cout << input_code << " is not a valid command" << endl;	
			continue;
		}
		switch (function_code[split_command[0]]) {
			case B: {
				bFunction();
				break;
			}
			case D: {
				dFunction();
				break;
			}
			case M: {
				mFunction();
				break;
			}
			case C: {
				cFunction();
				break;
			}
			case A: {
				aFunction();
				break;
			}
			case GC: {
				gcFunction();
				break;
			}
			case GS: {
				gsFunction();
				break;
			}
			case GB: {
				gbFunction();
				break;
			}
			case PB: {
				pbFunction();
				break;
			}
			case PC: {
				pcFunction();
				break;
			}
			case PY: {
				pyFunction();
				break;
			}
			case PD: {
				pdFunction();
				break;
			}
			case PM: {
				pmFunction();
				break;
			}
		}
	}
}

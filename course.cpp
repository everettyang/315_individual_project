#include "course.h"

Course::Course() {}
Course::Course(string _code, int _num, string _title) : course_code(_code), 
							course_number(_num), 
							course_name(_title) {}

void Course::printAll() {
	cout << this->course_code << " "
		<< this->course_number << " "
		<< this->course_name << "\n" << endl;
}

void Course::printBookForSection(int _section) {
	//goes into a certain section and prints all books
	try {
		pair<vector<Book>, vector<Book> > bookListing = sections.at(_section);	
		for (int i = 0; i < bookListing.first.size(); ++i) {
			cout << "(Required)" << endl;
			bookListing.first[i].printAll();
		}
		for (int i = 0; i < bookListing.second.size(); ++i) {
			cout << "(Optional)" << endl;
			bookListing.second[i].printAll();
		}
	}
	catch (const out_of_range& err) {
		cout << "Section is not defined! (Printing Books for a section)\n" << endl;
		return;
	}
}

void Course::setCourseNumber(int _val) {
	this->course_number = _val;
}
void Course::setCourseName(string _val) {
	this->course_name = _val;
}
void Course::setCourseCode(string _val) {
	this->course_code = _val;
}
void Course::assignBook(int _section, Book _b, string _required) {
	if (_required == "R")	
		this->sections[_section].first.push_back(_b);
	else if (_required == "O")
		this->sections[_section].second.push_back(_b);
	else {
		cout << "Invalid requirement value" << endl;
		return;
	}

	if (find(list_of_all_books.begin(), 
		list_of_all_books.end(), _b) 
		== list_of_all_books.end()) //if never seen this book before
		list_of_all_books.push_back(_b);	
}
vector<pair<vector<Book>, vector<Book> > > Course::getAllBooks(bool _print) {
	/*
	 * this function serves two purposes:
	 * 1. print all books for all sections
	 * 2. return all books for this course, separated by section
	*/
	//loop through all sections
	vector<pair<vector<Book>, vector<Book> > > all_books_by_section;
	for (map<int, pair<vector<Book>, vector<Book> > >::iterator it = this->sections.begin();
		it != this->sections.end(); ++it) {

		vector<Book> required_books = it->second.first;
		vector<Book> optional_books = it->second.second;
		if (_print) {
			cout << "SECTION " << it->first << ":\n" << endl;
			for (int i = 0; i < required_books.size(); ++i) {
				cout << "(Required)" << endl;
				required_books[i].printAll();
			}
			for (int i = 0; i < optional_books.size(); ++i) {
				cout << "(Optional)" << endl;
				optional_books[i].printAll();
			}
		}
		all_books_by_section.push_back(pair(required_books, optional_books));
	}
	return all_books_by_section;
}

vector<Book> Course::getListOfAllBooks() { return list_of_all_books; }

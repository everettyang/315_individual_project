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
	this->sections[_section].push_back(pair(_b, _required));
}
pair<vector<Book>, vector<Book> > Course::getAllBooks(bool _section_label, bool _print) {
	vector<Book> all_optional_books; //stores books from all sections of this course
	vector<Book> all_required_books;
	for (map<int, vector<pair<Book, string> > >::iterator it = this->sections.begin();
		it != this->sections.end(); ++it) {
		if (_section_label)
			cout << "SECTION " << it->first << ":\n" << endl;
		for (int i = 0; i < it->second.size(); ++i) {
			if (_print){
				it->second[i].second == "R" ? cout << "(Required)" << endl :
								cout << "(Optional)" << endl;
				it->second[i].first.printAll();
				cout << endl;
			}
			if (it->second[i].second == "R")
				all_required_books.push_back(it->second[i].first);	
			else
				all_optional_books.push_back(it->second[i].first);	
		}
	}
	return pair(all_required_books, all_optional_books);	
}
void Course::printBookForSection(int _section) {
	vector<pair<Book, string> > bookListing = sections[_section];	
	for (int i = 0; i < bookListing.size(); ++i) {
		bookListing[i].second == "R" ? cout << "(Required)" << endl :
						cout << "(Optional)" << endl;
		bookListing[i].first.printAll();
		cout << endl;
	}
}

#include "course.h"

Course::Course() {}
Course::Course(string _code, int _num, string _title) : course_code(_code), 
							course_number(_num), 
							course_name(_title) {}

void Course::printAll() {
	cout << "Course number: " << this->course_number << endl;
	cout << "Course code: " << this->course_code << endl;
	cout << "Course name: " << this->course_name << endl;
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
void Course::printAllBooks() {
	for (map<int, vector<pair<Book, string> > >::iterator it = this->sections.begin();
		it != this->sections.end(); ++it) {
		cout << "Section " << it->first << ":" << endl;
		for (int i = 0; i < it->second.size(); ++i) {
			it->second[i].second == "R" ? cout << "(Required)" << endl :
							cout << "(Optional)" << endl;
			it->second[i].first.printAll();
		}
	}
}
void Course::printBookForSection(int _section) {
	vector<pair<Book, string> > bookListing = sections[_section];	
	for (int i = 0; i < bookListing.size(); ++i)
		bookListing[i].first.printAll();
}

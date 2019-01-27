#include "book.h"

typedef unsigned long long ISBN;

Book::Book() {}
Book::Book(ISBN _id, string _title) : id(_id), title(_title), edition{0} { }

void Book::setTitle(string _title) {
	this->title = _title;
}

string Book::getTitle() {
	return this->title;
}

void Book::setID(ISBN _id) {
	this->id = _id;
}

ISBN Book::getID() {
	return this->id;
}

void Book::printAll() {
	cout << "ID: " << this->id << endl;
	cout << "Title: " << this->title << endl;
	cout << "Author: " << this->author << endl;
	this->edition == 0 ?  
		cout << "Edition: edition not defined" << endl :
		cout << "Edition: " << this->edition << endl;
	cout << "Date: " << this->date << endl;

	cout << "Cost for different versions: " << endl;
	for (map<string, double>::iterator it = this->cost.begin();
		it != this->cost.end(); ++it)
		cout << '\t' << it->first << " --> " << it->second << endl;
}

void Book::setCost(double _value, const char* a) {
	switch (*a) {
		case 'N':
			cost["New"] = _value;
			break;
		case 'U':
			cost["Used"] = _value;
			break;
		case 'R':
			cost["Refurbished"] = _value;
			break;
		case 'E':
			cost["Electronic"] = _value;
			break;
	}
}

void Book::defineAttribute(string _value, const char* a) {
	switch (*a) {
		case 'A':
			this->author = _value;
			break;
		case 'E':
			this->edition = stoi(_value);
			break;
		case 'D':
			this->date = _value;
			break;
	}
}

#include "book.h"

typedef unsigned long long ISBN;


Book::Book() {}
Book::Book(ISBN _id, string _title) : id(_id), title(_title), edition{0} { }

bool Book::operator==(const Book &other) const {
	return (this->id == other.id);
}
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
	//prints all information known about
	//this book
	cout << "ISBN: " << this->id << endl;
	cout << "Title: " << this->title << endl;
	cout << "Author: " << this->author << endl;
	this->edition == 0 ?  
		cout << "Edition: " << endl :
		cout << "Edition: " << this->edition << endl;
	cout << "Date Published: " << this->date << endl;

	cout << "Cost for different versions: " << endl;
	for (unordered_map<string, double>::iterator it = this->cost.begin();
		it != this->cost.end(); ++it)
		cout << '\t' << it->first << " --> " 
				<< it->second << endl;
	cout << endl;
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
		default:
			cout << "Invalid book type" << endl;
	}
}

void Book::defineAttribute(string _value, const char* a) {
	switch (*a) {
		case 'A':
			this->author = _value;
			break;
		case 'E':
			if (isEdition(_value))
				this->edition = stoi(_value);
			else
				cout << "Invalid edition (Defining attribute)" << endl;
			break;
		case 'D':
			if (isDate(_value))
				this->date = _value;
			else
				cout << "Invalid date (Defining attribute)" << endl;
			break;
		default:
			cout << "Invalid book attribute" << endl;
	}
}

double Book::getMinCost() {
	if (this->cost.size() == 0)
		return COST_UNDEFINED;
	double min = numeric_limits<double>::max();
	for (unordered_map<string, double>::iterator it = this->cost.begin(); 
						it != this->cost.end(); ++it) {
		if (it->second < min)
			min = it->second;
	}
	return min;
}

double Book::getMaxCost() {
	if (this->cost.size() == 0)
		return COST_UNDEFINED;
	double max = 0;
	for (unordered_map<string, double>::iterator it = this->cost.begin(); 
						it != this->cost.end(); ++it) {
		if (it->second > max)
			max = it->second;
	}
	return max;
}

string Book::getDate() {
	return this->date;
}

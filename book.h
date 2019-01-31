#ifndef BOOK_H
#define BOOK_H

#include <sstream>
#include <string> 
#include <vector> 
#include <iostream> 
#include <unordered_map> 
#include <algorithm>
#include "utilities.h" //global function(s)

#define COST_UNDEFINED -1

using namespace std;

typedef unsigned long long ISBN;

 /* this class defines what a book is
 * along with functions that query or
 * modify its attributes
 * all other classes uses this class
 */
class Book {
	ISBN id;
	string title;
	string author;
	string date;
	unordered_map<string, double> cost;
	unsigned int edition;
	
	public:
		Book();
		Book(ISBN _id, string _title);
		bool operator==(const Book &other) const; //checks if one book is equal to another

		void setTitle(string _title);
		
		string getTitle();
		string getDate();

		void setID(ISBN _id);
		void defineAttribute(string, const char* a); //set date, cost, or author
		void setCost(double _value, const char* a);

		double getMaxCost(); //finds lowest cost version of this book
		double getMinCost(); //finds highest cost version of this book
		
		ISBN getID();

		void printAll();
};

#endif //BOOK_H

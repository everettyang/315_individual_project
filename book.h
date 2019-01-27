#include <string> 
#include <vector> 
#include <iostream> 
#include <map> 

using namespace std;

class Book {
	typedef unsigned long long ISBN;
	ISBN id;
	string title;
	string author;
	string date;
	map<string, double> cost;
	unsigned int edition;
	
	public:
		Book();
		Book(ISBN _id, string _title);

		void setTitle(string _title);
		
		string getTitle();

		void setID(ISBN _id);
		void defineAttribute(string, const char* a);
		void setCost(double _value, const char* a);
		
		ISBN getID();

		void printAll();
};

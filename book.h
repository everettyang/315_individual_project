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
		string getDate();

		void setID(ISBN _id);
		void defineAttribute(string, const char* a);
		void setCost(double _value, const char* a);

		double getMaxCost();
		double getMinCost();
		
		ISBN getID();

		void printAll();
};

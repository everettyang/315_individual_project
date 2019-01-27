#include "book.h"

class Course {
	string course_code;
	string course_name;
	int course_number;
	map<int, vector<pair<Book, string> > > sections;
	
	public:
		Course();
		Course(string _code, int _num, string _title);
		void setCourseCode(string _val);
		void setCourseName(string _val);
		void setCourseNumber(int _val);
		void assignBook(int _section, Book _b, string _required);
		void printAllBooks();
		void printBookForSection(int _section);
		void printAll();
};

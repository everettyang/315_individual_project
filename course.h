#include "book.h"

class Course {
	string course_code;
	string course_name;
	int course_number;
	map<int, vector<pair<Book, string> > > sections;
	
	public:
		Course();
		Course(string _code, int _num, string _title);
		map<int, vector<pair<Book, string> > > getSections();
		void setCourseCode(string _val);
		void setCourseName(string _val);
		void setCourseNumber(int _val);
		void assignBook(int _section, Book _b, string _required);
		pair<vector<Book>, vector<Book> > getAllBooks(bool _section_label, bool _print); //retrieves all books for course object
		void printBookForSection(int _section);
		void printAll();
};

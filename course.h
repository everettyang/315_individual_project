#ifndef COURSE_H
#define COURSE_H

#include "book.h"

/*
 * defines what a course is
 * and what you can do with thhem
 */
class Course {
	string course_code; //ex: CSCE
	string course_name; //ex: Programming Studio
	int course_number; //ex: 313
	vector<Book> list_of_all_books; //contains all books used in this course (no duplicates)
					//(this is only used so that PD command does not contain duplicates)
	unordered_map<int, pair<vector<Book>, vector<Book> > > sections; //unordered_maps a section number to a section, 
							//which is a pair of Books (required, optional)
	public:
		//constructors
		Course();
		Course(string _code, int _num, string _title);

		//setters
		void setCourseCode(string _val);
		void setCourseName(string _val);
		void setCourseNumber(int _val);
		void assignBook(int _section, Book _b, string _required); //adds given book to given section

		//getters
		unordered_map<int, vector<pair<Book, string> > > getSections();
		vector<pair<vector<Book>, vector<Book> > > getAllBooks(bool _print); //retrieves all books for course object
		vector<Book> getListOfAllBooks();

		//printers
		void printBookForSection(int _section);
		void printAll();
};

#endif //COURSE_H

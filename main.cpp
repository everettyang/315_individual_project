#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include "course.h" 


//define all commands
using namespace std;

enum Command { 
	B, D, M, C, A,
	GC, GS, GB, PB, PC, PY,
	PD, PM
};

vector<string> split_str(string str, char delim) {
	  vector<string> internal;
	  stringstream ss(str); // Turn the string into a stream.
	  string tok;
 
	  while(getline(ss, tok, delim)) {
	    internal.push_back(tok);
	  }
 
	  return internal;
}

int main () {

	typedef unsigned long long ISBN;
	map<string, Command> commands;
	/*this is necessary as we require a way
	to map strings (user input) to commands (what the program is suppose to do */
	commands["B"] = B; 
	commands["D"] = D; 
	commands["M"] = M; 
	commands["C"] = C; 
	commands["A"] = A; 
	commands["GC"] = GC; 
	commands["GS"] = GS; 
	commands["GB"] = GB; 
	commands["PB"] = PB; 
	commands["PC"] = PC; 
	commands["PY"] = PY; 
	commands["PD"] = PD; 
	commands["PM"] = PM; 

	map<ISBN, Book> books;
	map<string, map<int, Course> > courses;

	string command;
	vector<string> split_command;

	while (getline(cin, command)) {
		split_command = split_str(command, ' ');
		string* last_elem = &split_command[split_command.size() - 1];
		last_elem->erase(last_elem->size() - 1);
		switch (commands[split_command[0]]) {

			case B: { 
				//define a book
				if (split_command[1].length() != 13)
					cout << "Not valid ISBN" << endl;
				else {
					ISBN id = strtoull(split_command[1].c_str(), NULL, 10);
					string title;
					title = split_command[2];
					for (int i = 3; i < split_command.size(); ++i)
						title += " " + split_command[i];

					Book b(id, title);
					books[id] = b;
				}
				break;
			}
			case D: {
				ISBN key = strtoull(split_command[1].c_str(), NULL, 10);
				std::string val;
				val = split_command[3];
				for (int i = 4; i < split_command.size(); ++i)
					val += " " + split_command[i];
				books[key].defineAttribute(val, split_command[2].c_str());
				break;
			}
			case M: {
				ISBN key = strtoull(split_command[1].c_str(), NULL, 10);
				books[key].setCost(stod(split_command[2]), split_command[3].c_str());
				break;
			}

			case C: {
				string code = split_command[1];
				int course_num = stoi(split_command[2]);
				string title = split_command[3];
				for (int i = 4; i < split_command.size(); ++i)
					title += " " + split_command[i];
				Course c(code, course_num, title);
				courses[code][course_num] = c;
				break;
			}

			case A: {
				ISBN key = strtoull(split_command[1].c_str(), NULL, 10);
				string code = split_command[2];
				int course_num = stoi(split_command[3]);
				int section = stoi(split_command[4]);
				string required = split_command[5];
				courses[code][course_num].assignBook(section, books[key], required);
				break;
			}

			case GC: {
				string code = split_command[1];
				int course_num = stoi(split_command[2]);
				cout << "BOOKS FOR " << code << " " <<  course_num <<
						"\n------------------------------" << endl;
				courses[code][course_num].getAllBooks(true, true);
				break;
			}

			case GS: {
				string code = split_command[1];
				int course_num = stoi(split_command[2]);
				int section = stoi(split_command[3]);
				cout << "BOOKS FOR " << code << " " << course_num << " SECTION " << section 
						<< " (selected using GS command):\n" <<
						"------------------------------" << endl;
				courses[code][course_num].printBookForSection(section);
				break;
			}

			case GB: { 
				//print everything about a book given isbn
				ISBN key = strtoull(split_command[1].c_str(), NULL, 10);
				cout << "SELECTED BOOK (" << key << "):\n" <<
						"------------------------------" << endl;
				map<ISBN, Book>::iterator it = books.find(key); 
				Book b = it->second;
				if (it == books.end())
					cout << "Book not found!" << endl;
				else
					b.printAll();
				break;
			}
			case PB: {
				cout << "ALL BOOKS DEFINED:\n" 
					"------------------------------" << endl;
				for (map<ISBN, Book>::iterator it = books.begin();
					it != books.end(); ++it) {
					it->second.printAll();
					cout << endl;
				}

				cout << "------------------------------\n" << endl;
				break;
			}
			case PC: {
				cout << "ALL COURSES DEFINED:\n" 
					"------------------------------"<< endl;
				for (map<string, map<int, Course> >::iterator it = courses.begin();
					it != courses.end(); ++it) {
					for (map<int, Course>::iterator it1 = it->second.begin();
						it1 != it->second.end(); ++it1) {
							it1->second.printAll();
					}
				}

				cout << "------------------------------\n" << endl;
				break;
			}
			case PY: {
				vector<string> split_date;
				string date = split_command[1];
				split_date = split_str(date, '/');
				int month = stoi(split_date[0]);
				int year = stoi(split_date[1]);


				cout << "ALL BOOKS NEWER THAN " << date << ":\n" <<
					"------------------------------" << endl;
				for (map<ISBN, Book>::iterator it = books.begin();
					it != books.end(); ++it) {

					vector<string> book_split_date;
					string book_date = it->second.getDate();
					book_split_date = split_str(book_date, '/');
					int book_month = stoi(book_split_date[0]);
					int book_year = stoi(book_split_date[1]);
					if (((book_month >= month) && (book_year >= year)) ||
						(book_year > year)) {
						it->second.printAll();
						cout << endl;
					}
				}
				cout << "------------------------------\n" << endl;
				break;
			}
			case PD: {
				string dept_code = split_command[1];
				cout << "ALL BOOKS USED IN " << dept_code << 
					"\n------------------------------" << endl;
				for (map<int, Course>::iterator it = courses[dept_code].begin();
					it != courses[dept_code].end(); ++it) {
					it->second.getAllBooks(false, true); //first arg false because dont want to print by section
				}
				cout << "------------------------------\n" << endl;
				break;
			}
			case PM: {
				string dept_code = split_command[1];
				double total_cost_max = 0;
				double total_cost_min = 0;
				int total_books = 0;
				int total_required_books = 0;

				for (map<int, Course>::iterator it = courses[dept_code].begin();
					it != courses[dept_code].end(); ++it) {
					pair<vector<Book>, vector<Book> > pair_books = it->second.getAllBooks(false, false); //get a pair (required books, optional books) for each course 
					vector<Book> all_books = pair_books.first; //add required books first
					all_books.insert(all_books.end(), pair_books.second.begin(), pair_books.second.end());

					total_books += all_books.size();
					total_required_books += pair_books.first.size();

					for (int i = 0; i < all_books.size(); ++i) {
						total_cost_max += all_books[i].getMaxCost();
					}
					for (int i = 0; i < pair_books.first.size(); ++i) {
						total_cost_min += pair_books.first[i].getMinCost();
					}
				}
				
				cout << "AVERAGE MAXIMUM COST OF BOOKS IN " << dept_code << ":" << '\n'<<
					total_cost_max / total_books << '\n' << endl;
				
				cout << "AVERAGE MINIMUM COST OF BOOKS IN " << dept_code << ":" << '\n'<<
					total_cost_min / total_required_books << '\n' << endl;
				break;
			}
		}
	}
}

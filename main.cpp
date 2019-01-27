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

vector<string> split_str(string str) {
	  vector<string> internal;
	  stringstream ss(str); // Turn the string into a stream.
	  string tok;
 
	  while(getline(ss, tok, ' ')) {
	    internal.push_back(tok);
	  }
 
	  return internal;
}

int main () {

	typedef unsigned long long ISBN;
	//stores all defined books
	map<string, Command> commands;

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
		split_command = split_str(command);
		switch (commands[split_command[0]]) {

			case B: { 
				//define a book
				ISBN id = strtoull(split_command[1].c_str(), NULL, 10);
				string title;
				title = split_command[2];
				for (int i = 3; i < split_command.size(); ++i)
					title += " " + split_command[i];

				Book b(id, title);
				books[id] = b;
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
				courses[code][course_num].printAllBooks();
				break;
			}

			case GS: {
				string code = split_command[1];
				int course_num = stoi(split_command[2]);
				int section = stoi(split_command[3]);
				courses[code][course_num].printBookForSection(section);
				break;
			}

			case GB:{ 
				//print everything about a book given isbn
				ISBN key = strtoull(split_command[1].c_str(), NULL, 10);
				books[key].printAll();
				break;
			}
		}
	}
}

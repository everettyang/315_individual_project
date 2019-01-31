#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "course.h"
#include "utilities.h"

/* this is a high level class that manages
 * books and courses and their relationship
 * with each other.
 */
class Controller {

	enum Function_code { 
		B, D, M, C, A,
		GC, GS, GB, PB, PC, PY,
		PD, PM
	};

	//Validity_checker vc;
	unordered_map<ISBN, Book> books; //all books defined
	unordered_map<string, unordered_map<int, Course> > courses; //all courses defined

	unordered_map<string, Function_code> function_code; //given the first token, 
						 //unordered_map to function code for later use
	vector<string> split_command; //stores each token of the command 
					//as separate elements in vector

	void parseUserInput(string& _command);

	/* functions for each possible user command.
	 * every function is basically the same in that
	 * it parses split_command elements and runs the
	 * correct member function in the correct class 
	 * (Book or Course) 
	 * the following functions are all void because they simply
	 * modify member variables and are not
	 * used by other functions as return value
	 */
	void bFunction();
	void dFunction();
	void mFunction();
	void cFunction();
	void aFunction();
	void gcFunction();
	void gsFunction();
	void gbFunction();
	void pbFunction();
	void pcFunction();
	void pyFunction();
	void pdFunction();
	void pmFunction();

	public:
		Controller();
		void run(); //runs the entire program
};

#endif //CONTROLLER_H

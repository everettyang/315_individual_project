#include "utilities.h"
#include <algorithm>
#include <cctype>

typedef unsigned long long ISBN;

//-----------Helper functons and classes-------------
//checks if a string contains one type of characters

bool non_numeric::operator()(char c) { return !std::isdigit(c); }
bool non_alpha::operator()(char c) { return !std::isalpha(c); }

vector<string> split_str(string str, char delim) {
	  vector<string> internal;
	  stringstream ss(str); //convert string to a workable stringstream
	  string tok;
 
	  while(getline(ss, tok, delim)) {
	    internal.push_back(tok);
	  }
 
	  return internal;
}


bool containsNonAlpha(string _value) {
	bool contains_non_alpha
	    = std::find_if(_value.begin(), 
				_value.end(), 
				non_alpha()) != _value.end();
	return contains_non_alpha;
}

bool containsNonNumeric(string _value) {
	bool contains_non_numeric
	    = std::find_if(_value.begin(), 
				_value.end(), 
				non_numeric()) != _value.end();
	return contains_non_numeric;
}

//---------------------- Validity Checker------------------------
//takes the user input and checks if it in the correct format

bool isDepartmentCode(string _dept_code) {
	bool contains_non_alpha = containsNonAlpha(_dept_code);
	return (_dept_code.length() == 4) &&
	!contains_non_alpha;
}
bool isThreeDigitNumber(string _course_number) {
	bool contains_non_numeric = 
	containsNonNumeric(_course_number);
	return (_course_number.length() == 3) &&
	!contains_non_numeric;
}
bool isSingleCharacter(string _char) {
	return (_char.length() == 1);
}
bool isISBN(string _ISBN) {
	bool contains_non_numeric =
	containsNonNumeric(_ISBN);
	return (_ISBN.length() == 13) &&
	!contains_non_numeric;
}
bool isEdition(string _edition) {
	bool contains_non_numeric = 
	containsNonNumeric(_edition);
	return !contains_non_numeric && 
		(_edition[0] != '-');
}
bool isCost(string _cost) {
	vector<string> split_cost = split_str(_cost, '.');
	
	return (split_cost.size() == 2) &&
	(!containsNonNumeric(split_cost[0])) &&
	(split_cost[1].length() == 2) &&
	(!containsNonNumeric(split_cost[1]));
}

bool isDate(string _date){
	vector<string> split_date = split_str(_date, '/');
	
	return (split_date.size() == 2) &&
	(!containsNonNumeric(split_date[0])) &&
	(split_date[1].length() == 4) &&
	(!containsNonNumeric(split_date[1]));
}

bool checkCourse(string _course_code, 
			string _course_num, 
			string _section) {
	//this function checks if the course
	//code and number given are valid
	//by making use of above functions
	if (!isDepartmentCode(_course_code)) {
		cout << "INVALID COURSE CODE" << endl;
		return false;
	}
	if (!isThreeDigitNumber(_course_num) && (_course_num != "")) {
		cout << "INVALID COURSE NUMBER" << endl;
		return false;
	}
	if (!isThreeDigitNumber(_section) && (_section != "")) {
		cout << "INVALID SECTION NUMBER" << endl;
		return false;
	}
	return true;
}

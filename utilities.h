#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

std::vector<string> split_str(string str, char delim); //split a string by delimiter

struct non_alpha { bool operator()(char _c); };
struct non_numeric { bool operator()(char _c); };


bool containsNonNumeric(string _value);
bool containsNonAlpha(string _value);

//global checking functions
bool isDepartmentCode(string _dept_code);
bool isThreeDigitNumber(string _course_number);
bool isISBN(string _ISBN);
bool isEdition(string _edition);
bool isCost(string _cost);
bool checkCourse(string _course_code, 
			string _course_num = "", 
			string _section = "");
bool isDate(string _date);

#endif

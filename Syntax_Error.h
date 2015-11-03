#ifndef SYNTAX_ERROR_H
#define SYNTAX_ERROR_H

#include <string>
#include <iostream>
using namespace std;
class Syntax_Error{
public:
	Syntax_Error() {};
	Syntax_Error(string msg) { error = msg; index = getIndex(); };
	void ErrorMsg() { cout << error << " at location " << index << endl; };
private:
	string error;
	int index;
	int getIndex() { return index; };
};
#endif

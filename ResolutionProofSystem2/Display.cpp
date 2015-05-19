#include "Display.h"

void print_vector_string(vector<string> inp){
	for (vector<string>::const_iterator i = inp.begin(); i != inp.end(); ++i)
		cout << *i << endl;
}
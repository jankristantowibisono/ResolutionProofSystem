#include "FileReader.h"

//read file and return vector string
vector<string> read_as_vector_string(string inp){
	ifstream myfile(inp);
	string line;
	vector<string> result; 
	// read by line
	if (myfile.is_open()){
		while (getline(myfile, line)){
			result.push_back(line);
		}
		myfile.close();
	}
	else cout << "Unable to open file";
	return result;
}
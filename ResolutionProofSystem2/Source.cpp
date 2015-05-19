#include <iostream>
#include "FileReader.h"
#include "Display.h"
#include "ParserAI.h"
#include "BoolExpre.h"
#include "Cnf.h"
#include "FileWriter.h"
using namespace std;

ofstream outputFile;
//Change filename to try another case
const string testcase = "Compare"; 

void check_expression(vector<string> inp){
	struct MyExp *h = new MyExp;
	//cout << "=================" << "Your KB : " << "=================" << endl;
	outputFile << "=================" << "Your KB : " << "=================" << endl;
	for (std::vector<string>::size_type i = 0; i != inp.size(); i++) {
		h = myparse(inp.at(i));
		//cout << "KB  : "; print_expression(h); 
		outputFile << "KB  : "; file_print_expression(h, 0, testcase);
		
		convert_cnf(&h);
		//cout << "CNF : "; print_expression(h, 1); 
		outputFile << "CNF : "; file_print_expression(h, 1, testcase);
	}
	outputFile << "============================================" << endl;
	//cout << "============================================" << endl;
}

void print_query(vector<string> inp){
	struct MyExp *h = new MyExp;
	//cout << "===============" << "Your Query : " << "================" << endl;
	outputFile << "===============" << "Your Query : " << "================" << endl;
	for (std::vector<string>::size_type i = 0; i != inp.size(); i++) {
		h = myparse(inp.at(i));
		//cout << "query : "; print_expression(h); 
		outputFile << "query : "; file_print_expression(h, 0, testcase);
		convert_cnf(&h);
		//print_expression(h, 1);
		outputFile << "CNF   : "; 
		file_print_expression(h, 1, testcase);
	}
	//cout << "============================================" << endl;
	outputFile << "============================================" << endl;
}

int main(){
	outputFile.open(testcase+".Result");
	vector<string> fromfile = read_as_vector_string(testcase+".KB");
	//print_vector_string(fromfile);
	//print_vector_string(get_KB(fromfile));
	vector<string> kb = get_KB(fromfile); 
	check_expression(kb);
	
	vector<string> queryfile = read_as_vector_string(testcase+".Query");
	vector<string> q = get_Query(queryfile);
	print_query(q);
	/*struct MyExp *h = myparse(kb.at(1));
	convert_cnf(&h);*/
	//cout << h->ori << endl;
	//check_expression(kb);

	outputFile << endl;
	outputFile.close();
	return 0; 
}
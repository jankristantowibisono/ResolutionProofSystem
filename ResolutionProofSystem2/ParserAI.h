#ifndef ParserAI_H
#define ParserAI_H


#include "BoolExpre.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

vector<string> get_KB(vector<string> inp);
vector<string> get_Query(vector<string> inp);
vector<string> split_by(string inp, char delimiter);
int check_quantifiers(string inp);
string get_forall_var(string inp);
string get_exist_var(string inp);
struct MyExp *myparse(string inp);
string trim(string str,char x);
string ltrim(string str,char x);
string rtrim(string str);
bool check_biimplication(string inp);
bool check_implication(string inp);
bool check_and(string inp);
bool check_or(string inp);
bool check_not(string inp);
bool check_predicate(string inp);
bool check_var(string inp);

#endif
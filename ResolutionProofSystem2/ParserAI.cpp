#include "ParserAI.h"
#include "BoolExpre.h"
#include "display.h"
#include <sstream>

vector<string> get_KB(vector<string> inp){
	bool start = false;
	vector<string> result;
	for (vector<string>::const_iterator i = inp.begin(); i != inp.end(); i++){
		if (*i == "FOL end") start = false;
		if (start) result.push_back(*i);
		if (*i == "FOL start") start = true;
	}
	return result;
}

vector<string> get_Query(vector<string> inp){
	vector<string> result;
	for (vector<string>::const_iterator i = inp.begin(); i != inp.end(); i++){
		result.push_back(*i);
	}
	return result;
}
vector<string> split_by(string inp, char delimiter){
	vector<string> result; 
	stringstream ss(inp); // Turn the string into a stream.
	string tok;

	while (getline(ss, tok, delimiter)) {
		result.push_back(tok);
	}
	return result;
}
string get_first_by(string inp, char delimiter){
	vector<string> result = split_by(inp, delimiter);
	return result.at(0);
}
int check_quantifiers(string inp){
	// check forall return 1
	int result = 0; 
	size_t pos = 0;
	while ((pos = inp.find("Forall")) != string::npos) {
		//token = inp.substr(0, pos);
		//std::cout << token << std::endl;
		inp.erase(0, pos + 6+2);
		result = 1;
		return result;
	}

	// check exist return 2
	pos = 0;
	while ((pos = inp.find("Exist")) != string::npos) {
		//token = inp.substr(0, pos);
		//std::cout << token << std::endl;
		inp.erase(0, pos + 5+2);
		result = 2;
		return result;
	}
	return result;
}

bool check_biimplication(string inp){
	// check implication
	bool result = false;
	size_t pos = 0;

	while ((pos = inp.find("<=>")) != string::npos) {
		//token = inp.substr(0, pos);
		//std::cout << token << std::endl;
		inp.erase(0, pos + 6 + 3);
		result = true;
	}
	return result;
}

bool check_implication(string inp){
	// check implication
	bool result = false;
	size_t pos = 0;
	
	while ((pos = inp.find("=>")) != string::npos) {
		//token = inp.substr(0, pos);
		//std::cout << token << std::endl;
		inp.erase(0, pos + 6 + 2);
		result = true;
	}
	return result;
}
string ltrim(string str,char x){
	string result; 
	str = trim(str, ' ');
	result = str.substr(0, str.length());
	if (str.at(0) == x){
		result = str.erase(0,1);
	}
	return result;
}
string trim(string str,char x){
	size_t first = str.find_first_not_of(x);
	size_t last = str.find_last_not_of(x);
	return str.substr(first, (last - first + 1));
}
string get_forall_var(string inp){
	string result; 
	// first is forall
	size_t pos = 0;
	while ((pos = inp.find_first_of("Forall ")) != string::npos) {
		//token = inp.substr(0, pos);
		//std::cout << token << std::endl;
		inp.erase(0, pos + 6 + 1);
		
		break;
	}
	//cout << inp << endl;
	vector<string> tmp = split_by(inp,' ');
	result = tmp.at(0);
	return result;
}

string get_exist_var(string inp){
	string result;
	// first is forall
	size_t pos = 0;
	while ((pos = inp.find_first_of("Exist")) != string::npos) {
		//token = inp.substr(0, pos);
		//std::cout << token << std::endl;
		inp.erase(0, pos + 5 + 1);
		break;
	}
	vector<string> tmp = split_by(inp, ' ');
	result = tmp.at(0);
	return result;
}

bool check_and(string inp){
	// check and
	bool result = false;
	size_t pos = 0;

	while ((pos = inp.find("&")) != string::npos) {
		//token = inp.substr(0, pos);
		//std::cout << token << std::endl;
		inp.erase(0, pos + 1);
		result = true;
	}
	return result;
}
bool check_or(string inp){
	// check or
	bool result = false;
	size_t pos = 0;

	while ((pos = inp.find("|")) != string::npos) {
		//token = inp.substr(0, pos);
		//std::cout << token << std::endl;
		inp.erase(0, pos + 1);
		result = true;
	}
	return result;
}
bool check_not(string inp){
	bool result = false;
	size_t pos = 0;

	while ((pos = inp.find("!")) != string::npos) {
		//token = inp.substr(0, pos);
		//std::cout << token << std::endl;
		inp.erase(0, pos + 1);
		result = true;
	}
	return result;

}
bool check_predicate(string inp){
	bool result = false;
	size_t pos = 0;

	while ((pos = inp.find("(")) != string::npos) {
		//token = inp.substr(0, pos);
		//std::cout << token << std::endl;
		inp.erase(0, pos + 1);
		result = true;
	}
	return result;
}

bool check_var(string inp){
	int n = inp.find("\"");
	int m = inp.find(",");
	//cout << n << endl;
	if (m!=-1 || n != -1 || inp.length() == 1) return true;
	else return false;
}
struct MyExp *myparse(string inp){
	struct MyExp *result = nullptr;
	
	//cout << inp << endl;
	//check quantifiers
	int q = check_quantifiers(inp);
	if (q > 0){
		if (q == 1){
			string v = get_forall_var(inp);
			string temp = "Forall " + v;
			string r = inp.substr(temp.length()+1, inp.length() - temp.length()-1);
			result = create_forall(inp,v);
			result->ch = myparse(r); // recursive
			result->ch->pr = result;
			inp = temp;
			
		}
		if (q == 2){
			string v = get_exist_var(inp);
			string temp = "Exist " + v;
			string r = inp.substr(temp.length() + 1, inp.length() - temp.length() - 1);
			result = create_exist(inp, v);
			//cout << r;
			result->ch = myparse(r); // recursive
			result->ch->pr = result;
			inp = temp;
			//cout << result->et << endl; exit;
		}
	}

	// check biimplication 
	if (check_biimplication(inp)){
		size_t pos = 0;
		string ori = inp;
		string first;
		string second;

		while ((pos = inp.find("<=>")) != string::npos) {
			first = inp.substr(0, pos);
			//std::cout << token << std::endl;
			inp.erase(0, pos + 4);
		}
		//cout << first << endl;
		second = trim(inp, ' ');
		result = create_biimplication(ori);
		result->ch = myparse(first);
		result->ch->pr = result;
		result->fr = myparse(second);
		result->fr->pr = result;
		inp = "";
	}
	//cout << inp;
	// check implication 
	if (check_implication(inp)){
		size_t pos = 0;
		string ori = inp;
		string first;
		string second;
		
		while ((pos = inp.find("=>")) != string::npos) {
			first = inp.substr(0, pos);
			//std::cout << token << std::endl;
			inp.erase(0,pos+3);
		}
		//cout << first << endl;
		second = trim(inp,' ');
		result = create_implication(ori);
		result->ch = myparse(first);
		result->ch->pr = result;
		result->fr = myparse(second);
		result->fr->pr = result;
		inp = "";
	}
	// if AND
	if (check_and(inp)){
		size_t pos = 0;
		string ori = inp;
		string first;
		string second;
		while ((pos = inp.find("&")) != string::npos) {
			first = inp.substr(0, pos);
			
			inp.erase(0, pos+1);
		}
		second = inp;
		result = create_and(ori);
		//cout << first <<second<< endl;
		result->ch = myparse(first);
		result->ch->pr = result;
		result->fr = myparse(second);
		result->fr->pr = result;
		inp = "";
	}

	//if OR
	if (check_or(inp)){
		size_t pos = 0;
		string ori = inp;
		string first;
		string second;
		while ((pos = inp.find("|")) != string::npos) {
			first = inp.substr(0, pos);
			inp.erase(0, pos + 1);
		}
		second = inp;
		result = create_or(ori);
		//cout << first <<second<< endl;
		result->ch = myparse(first);
		result->ch->pr = result;
		result->fr = myparse(second);
		result->fr->pr = result;
		inp = "";
	}

	//if not
	if (check_not(inp)){
		size_t pos = 0;
		string ori = inp;
		string first;
		string second;
		while ((pos = inp.find("!")) != string::npos) {
			first = inp.substr(0, pos);

			inp.erase(0, pos + 1);
		}
		result = create_not(ori);
		result->ch = myparse(inp);
		result->ch->pr = result;
		inp = "";
	}
	// predicate
	if (check_predicate(inp)){
		size_t pos = 0;
		string ori = inp;
		string pred;
		inp = trim(inp,' ');
		while ((pos = inp.find("(")) != string::npos) {
			pred = ltrim(inp.substr(0, pos),'[');
			
			inp.erase(0, pos + 1);
		}
		//cout << pred << endl;
		result = create_pred(ori, pred);
		int first = ori.find("(");
		int batas = 0;
		batas = ori.find_last_of(")");
		string vari = ori.substr(first + 1, batas - first - 1);
		//cout << ori << endl;
		//string f = get_first_by(vari, ',');
		//string remain = vari.erase(0,f.length()+1);
		result->ch = myparse(vari);
		
		//cout << vari << endl;
		//result->ch = myparse(vari);
		//cout << first <<second<< endl;
		//result->ch = myparse(first);
		//result->fr = myparse(second);
		inp = "";
	}

	// var
	if (check_var(inp)){
		string f = get_first_by(inp, ',');
		string remain = inp.erase(0,f.length()+1);
		int n = f.find("\"");
		if (n == -1){
			result = create_var(f);
		}else{
			result = create_con(f);
		}
		result->fr = myparse(remain);
		
	}

	return result;
}
#include "BoolExpre.h"
#include "parserAI.h"
#include "display.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

struct MyExp *create_forall(string ori,string v) {
	struct MyExp *result = new MyExp;
	//struct MyExp *c = new MyExp;
	//c->ori = remain;
	result->fr = nullptr;
	result->ch = nullptr;
	result->pr = nullptr;
	result->et = oper;
	result->ot = all;
	result->ori = ori;
	result->name = "Forall "+v;
	
	//cout << result->et << endl; exit;
	return result;
}
struct MyExp *create_biimplication(string ori){
	struct MyExp *result = new MyExp;
	//struct MyExp *c = new MyExp;
	//c->ori = remain;
	result->fr = nullptr;
	result->ch = nullptr;
	result->pr = nullptr;
	result->et = oper;
	result->ot = biimp;
	result->ori = ori;
	//result->ch = c;
	//cout << result->et << endl; exit;
	return result;
}
struct MyExp *create_implication(string ori){
	struct MyExp *result = new MyExp;
	//struct MyExp *c = new MyExp;
	//c->ori = remain;
	result->fr = nullptr;
	result->ch = nullptr;
	result->pr = nullptr;
	result->et = oper;
	result->ot = imp;
	result->ori = ori;
	//result->ch = c;
	//cout << result->et << endl; exit;
	return result;
}
struct MyExp *create_and(string ori){
	struct MyExp *result = new MyExp;
	//struct MyExp *c = new MyExp;
	//c->ori = remain;
	result->fr = nullptr;
	result->ch = nullptr;
	result->pr = nullptr;
	result->et = oper;
	result->ot = and;
	result->ori = ori;
	//result->ch = c;
	//cout << result->et << endl; exit;
	return result;
}
struct MyExp *create_or(string ori){
	struct MyExp *result = new MyExp;
	//struct MyExp *c = new MyExp;
	//c->ori = remain;
	result->fr = nullptr;
	result->ch = nullptr;
	result->pr = nullptr;
	result->et = oper;
	result->ot = or;
	result->ori = ori;
	//result->ch = c;
	//cout << result->et << endl; exit;
	return result;
}
struct MyExp *create_not(string ori){
	struct MyExp *result = new MyExp;
	//struct MyExp *c = new MyExp;
	//c->ori = remain;
	result->fr = nullptr;
	result->ch = nullptr;
	result->pr = nullptr;
	result->et = oper;
	result->ot = not;
	result->ori = ori;
	//result->ch = c;
	//cout << result->et << endl; exit;
	return result;
}
struct MyExp *create_exist(string ori, string v){
	struct MyExp *result = new MyExp;
	//struct MyExp *c = new MyExp;
	//c->ori = remain;
	result->fr = nullptr;
	result->ch = nullptr;
	result->pr = nullptr;
	result->et = oper;
	result->ot = exist;
	result->ori = ori;
	result->name = "Exist "+v;
	//result->ch = c;
	//cout << result->et << endl; exit;
	return result;
}

struct MyExp *create_pred(string ori,string name){
	struct MyExp *result = new MyExp;
	//struct MyExp *c = new MyExp;
	//c->ori = remain;
	result->fr = nullptr;
	result->ch = nullptr;
	result->pr = nullptr;
	result->et = pred;
	result->ot = p;
	result->ori = ori;
	result->name = name;
	//result->ch = c;
	//cout << result->et << endl; exit;
	return result;
}

struct MyExp *create_var(string name){
	struct MyExp *result = new MyExp;
	
	result->fr = nullptr;
	result->ch = nullptr;
	result->pr = nullptr;
	result->name = name;
	result->et = var;
	result->ot = v;
	return result;
}
struct MyExp *create_con(string name){
	struct MyExp *result = new MyExp;

	result->fr = nullptr;
	result->ch = nullptr;
	result->pr = nullptr;
	result->name = name;
	result->et = con;
	result->ot = c;
	return result;
}


void print_var(MyExp *inp){
	if (inp != nullptr){
		if (inp->et == var){
			cout << inp->name<<",";
			print_var(inp->fr);
		}
		if (inp->et == con){
			cout << inp->name << ",";
			print_var(inp->fr);
		}
	}
}

void print_pred(MyExp *inp){
	if (inp != nullptr){
		if (inp->et == pred){
			cout << inp->name << "(";
			print_var(inp->ch);
			cout << ")";
		}
	}
}
void print(MyExp *inp,int n){
	if (inp != nullptr){
		if (inp->et == oper){
			if (inp->ot == all){
				if (n == 0){
					cout << inp->name << "[";
					if (inp->ch->et == pred)print_pred(inp->ch);
					if (inp->ch->et == oper)print(inp->ch);
					cout << "]";
				}else{
					if (inp->ch->et == pred)print_pred(inp->ch);
					if (inp->ch->et == oper)print(inp->ch);
				}
			}
			if (inp->ot == exist){
				if (n == 0){
					cout << inp->name << "[";
					if (inp->ch->et == pred)print_pred(inp->ch);
					if (inp->ch->et == oper)print(inp->ch);
					cout << "]";
				}
				else{
					if (inp->ch->et == pred)print_pred(inp->ch);
					if (inp->ch->et == oper)print(inp->ch);
				}
			}
			if (inp->ot == imp){
				if (inp->ch->et == pred)print_pred(inp->ch);
				if (inp->ch->et == oper)print(inp->ch);
				cout << "=>" << " ";
				if (inp->fr->et == pred)print_pred(inp->fr);
				if (inp->fr->et == oper)print(inp->fr);
			}
			if (inp->ot == biimp){
				if (inp->ch->et == pred)print_pred(inp->ch);
				if (inp->ch->et == oper)print(inp->ch);
				cout << "<=>" << " ";
				if (inp->fr->et == pred)print_pred(inp->fr);
				if (inp->fr->et == oper)print(inp->fr);
			}
			if (inp->ot == not){
				cout << "!" << " ";
				if (inp->ch->et == pred)print_pred(inp->ch);
			}
			if (inp->ot == and){
				if (inp->ch->et == pred)print_pred(inp->ch);
				if (inp->ch->et == oper)print(inp->ch);
				cout << "&" << " ";
				if (inp->fr->et == pred)print_pred(inp->fr);
				if (inp->fr->et == oper)print(inp->fr);
			}
			if (inp->ot == or){
				if (inp->ch->et == pred)print_pred(inp->ch);
				if (inp->ch->et == oper)print(inp->ch);
				cout <<" "<< "|" << " ";
				if (inp->fr->et == pred)print_pred(inp->fr);
				if (inp->fr->et == oper)print(inp->fr);
			}
		}
	}
	

}
void print_expression(MyExp *inp,int n){
	if (inp != NULL) {
		if (inp->et == oper)print(inp,n);
		if (inp->et == pred)print_pred(inp);
		/*if (inp->ch) print_expression(inp->ch);
		if (inp->fr) print_expression(inp->fr);*/
		cout << endl;
	}
}
struct MyExp *search_expre(struct MyExp *inp,ExType iet, OpType iot){
	struct MyExp *result = new MyExp;
	if (inp == NULL) return inp;
	if (inp->et == iet && inp->ot == iot){
		return inp;
	}else{
		if (inp->fr) return search_expre(inp->fr,iet,iot);
		if (inp->ch) return search_expre(inp->ch, iet, iot);
	}
}
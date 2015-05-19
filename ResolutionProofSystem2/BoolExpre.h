#ifndef BoolExpre_H
#define BoolExpre_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;
enum ExType {
	con,pred,oper,var,
};
enum OpType {
	all,exist,imp,biimp,not,and,or,p,v,c
};
typedef struct MyExp {
	struct MyExp *fr;
	struct MyExp *ch;
	struct MyExp *pr;
	string ori;
	string name;
	enum ExType et;
	enum OpType ot;
};

struct MyExp *create_forall(string ori, string v);
struct MyExp *create_exist(string ori, string v);
struct MyExp *create_and(string ori);
struct MyExp *create_or(string ori);
struct MyExp *create_not(string ori);
struct MyExp *create_biimplication(string ori);
struct MyExp *create_implication(string ori);
struct MyExp *create_pred(string ori,string name);
struct MyExp *create_var(string name);
struct MyExp *create_con(string name);
struct MyExp *search_expre(struct MyExp *inp,ExType et, OpType ot);
void print_expression(MyExp *inp,int n=0);
void print(MyExp *inp,int n=0);
void print_var(MyExp *inp);
void print_pred(MyExp *inp);
#endif
#ifndef FileWriter_H
#define FileWriter_H
#include "BoolExpre.h"
#include "parserAI.h"
#include "display.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;


void file_print_expression(MyExp *inp, int n = 0,string name="result");
void file_print(MyExp *inp, int n = 0);
void file_print_var(MyExp *inp);
void file_print_pred(MyExp *inp);

#endif
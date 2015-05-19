
#include "FileWriter.h"

extern ofstream outputFile;
void file_print_var(MyExp *inp){
	if (inp != nullptr){
		if (inp->et == var){
			outputFile << inp->name << ",";
			file_print_var(inp->fr);
		}
		if (inp->et == con){
			outputFile << inp->name << ",";
			file_print_var(inp->fr);
		}
	}
}

void file_print_pred(MyExp *inp){
	if (inp != nullptr){
		if (inp->et == pred){
			outputFile << inp->name << "(";
			file_print_var(inp->ch);
			outputFile << ")";
		}
	}
}
void file_print(MyExp *inp, int n){
	if (inp != nullptr){
		if (inp->et == oper){
			if (inp->ot == all){
				if (n == 0){
					outputFile << inp->name << "[";
					if (inp->ch->et == pred)file_print_pred(inp->ch);
					if (inp->ch->et == oper)file_print(inp->ch);
					outputFile << "]";
				}
				else{
					if (inp->ch->et == pred)file_print_pred(inp->ch);
					if (inp->ch->et == oper)file_print(inp->ch);
				}
			}
			if (inp->ot == exist){
				if (n == 0){
					outputFile << inp->name << "[";
					if (inp->ch->et == pred)file_print_pred(inp->ch);
					if (inp->ch->et == oper)file_print(inp->ch);
					outputFile << "]";
				}
				else{
					if (inp->ch->et == pred)file_print_pred(inp->ch);
					if (inp->ch->et == oper)file_print(inp->ch);
				}
			}
			if (inp->ot == imp){
				if (inp->ch->et == pred)file_print_pred(inp->ch);
				if (inp->ch->et == oper)file_print(inp->ch);
				outputFile << "=>" << " ";
				if (inp->fr->et == pred)file_print_pred(inp->fr);
				if (inp->fr->et == oper)file_print(inp->fr);
			}
			if (inp->ot == biimp){
				if (inp->ch->et == pred)file_print_pred(inp->ch);
				if (inp->ch->et == oper)file_print(inp->ch);
				outputFile << "<=>" << " ";
				if (inp->fr->et == pred)file_print_pred(inp->fr);
				if (inp->fr->et == oper)file_print(inp->fr);
			}
			if (inp->ot == not){
				outputFile << "!" << " ";
				if (inp->ch->et == pred)file_print_pred(inp->ch);
			}
			if (inp->ot == and){
				if (inp->ch->et == pred)file_print_pred(inp->ch);
				if (inp->ch->et == oper)file_print(inp->ch);
				outputFile << "&" << " ";
				if (inp->fr->et == pred)file_print_pred(inp->fr);
				if (inp->fr->et == oper)file_print(inp->fr);
			}
			if (inp->ot == or){
				if (inp->ch->et == pred)file_print_pred(inp->ch);
				if (inp->ch->et == oper)file_print(inp->ch);
				outputFile << " " << "|" << " ";
				if (inp->fr->et == pred)file_print_pred(inp->fr);
				if (inp->fr->et == oper)file_print(inp->fr);
			}
		}
	}


}
void file_print_expression(MyExp *inp, int n,string name){
	if (inp != NULL) {
		
		if (inp->et == oper)file_print(inp, n);
		if (inp->et == pred)file_print_pred(inp);
		outputFile << endl;
		/*if (inp->ch) print_expression(inp->ch);
		if (inp->fr) print_expression(inp->fr);*/
		
	}
}
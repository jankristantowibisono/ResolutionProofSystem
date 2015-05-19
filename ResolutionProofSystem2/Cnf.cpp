#include "Cnf.h"
#include "BoolExpre.h"

void convert_cnf(struct MyExp **inp){
	struct MyExp *result = new MyExp;
	//1.biimplication and implication
	eliminate_arrows(*inp);
	//2. drive negation 
	drive_negation(*inp);
	//3. drop quantifiers
	double_negation(*inp);
	remove_quantifiers(*inp);
}

void remove_quantifiers(struct MyExp *inp){
	if (inp->et == oper && (inp->ot == all || inp->ch->ot == exist)){
		if (inp->pr == nullptr){
			inp->name = "";
			if (inp->ch)remove_quantifiers(inp->ch);
			if (inp->fr)remove_quantifiers(inp->fr);
		}else{
			inp->pr->ch = inp->ch;
			inp->ch->pr = inp->pr;
			delete inp;
		}
	}else{
		if (inp->ch)remove_quantifiers(inp->ch);
		if (inp->fr)remove_quantifiers(inp->fr);
	}
}

void double_negation(struct MyExp *inp){
	//! ! a = a
	
	if (inp->et == oper && inp->ot == not && inp->ch->et == oper && inp->ch->ot == not){
		inp->pr->ch = inp->ch;
		inp->ch->pr = inp->pr;
		delete inp;
	}
}

void eliminate_arrows(struct MyExp *inp){
	if (inp->et == oper && inp->ot == imp){
		struct MyExp *n = create_not("not");
		// a => b === !a OR b
		n->ch = inp->ch;
		inp->ch->pr = n;
		n->pr = inp;
		inp->ch = n;

		inp->ot = or;
	}else{
		if (inp->et == oper && inp->ot == biimp){
			// a <=> b === p => q & q => p
			// a <=> b === (a OR !b) & (!a OR b)
			struct MyExp *n_or = create_or("or");
			struct MyExp *n_or2 = create_or("or");
			struct MyExp *n1 = create_not("not");
			struct MyExp *n2 = create_not("not");
			struct MyExp *newA = new MyExp;
			struct MyExp *newB = new MyExp;

			inp->ot = and;

		}else{
			if (inp->fr) eliminate_arrows(inp->fr);
			if (inp->ch) eliminate_arrows(inp->ch);
		}
	}
}

void drive_negation(struct MyExp *inp){
	if (inp->et == oper && inp->ot == not){
		
		// a => b === !a OR b
		if (inp->ch->et == oper && inp->ch->ot == and){
			struct MyExp *not_a = create_not("not");
			struct MyExp *not_b = create_not("not");
			// n = inp->ch
			inp->ch->ot = or;
			
			not_a->ch = inp->ch->ch;
			inp->ch->ch->pr = not_a;
			not_a->pr = inp->ch;
			inp->ch->ch = not_a;

			not_b->ch = inp->ch->fr;
			inp->ch->fr->pr = not_b;
			not_b->pr = inp->ch;
			inp->ch->fr = not_b;

			inp->ch->pr = inp->pr;
			inp->pr->ch = inp->ch;
		}
		
	}
	else{
		
		if (inp->fr) drive_negation(inp->fr);
		if (inp->ch) drive_negation(inp->ch);
	}
}
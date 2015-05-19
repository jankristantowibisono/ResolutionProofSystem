#ifndef Cnf_H
#define Cnf_H

void convert_cnf(struct MyExp **inp);
void eliminate_arrows(struct MyExp *inp);
void drive_negation(struct MyExp *inp);
void double_negation(struct MyExp *inp);
void remove_quantifiers(struct MyExp *inp);

#endif
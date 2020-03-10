#pragma once

//Returns a pointer to a new form of the length 'length' with values of double type, filled with elements of 'values' array 
struct Form* createLinearForm(int length, double* values);

//Gets a pointer with index 'index' in dynamic array '*a', casted to (struct form *)
struct Form* getForm(struct DynamicArray* a, int index);

//Gets a pointer on element with index 'index' from form '*a', casted to (double *)
double* getNumbericElement(struct Form* a, int index);

//Prints a form '*form', assuming all of its elements are of the type (double)
void printLinearForm(struct Form* form);

//Prints all elements of dynamic array '*a', assuming its elements are (struct Form *) and all of their elements are of the type (double)
void printForms(struct DynamicArray* a);

//Returns a sum of forms '*a' and '*b,' assuming all of their elements are of the type (double)
struct Form* sum(struct Form* a, struct Form* b);

//Returns a form '*a', multiplied by the number 'num', assuming all of its elements are of the type (double)
struct Form* multiply(struct Form* a, double num);

//Returns a numberic value of a form '*a' if its variables are '*args', assuming all of its elements are of the type (double)
double calculate(struct Form* a, double* args);

//Returns a difference of forms '*a' and '*b,' assuming all of their elements are of the type (double)
struct Form* subtract(struct Form* a, struct Form* b);

int compareElements(struct Form* a, struct Form* b);

void crossMultiply(struct Form* a, struct Form* b);
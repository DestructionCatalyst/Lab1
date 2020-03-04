#include "FormWrapper.h"
#include "Form.h"
#include "DynamicArray.h"
#include <stdio.h>
#define abs(a) a>0?a:(-1)*a

//Returns a pointer to a new form of the length 'length' with values of double type, filled with elements of 'values' array 
struct Form* createLinearForm(int length, double* values) {

	//The value of the array elements before filling it with '*values'
	double zero = 0;
	struct Form* form = Create(length, sizeof(double), &zero);
	//Filling it with '*values'
	for (int i = 0; i < GetElementCount(form); i++) {
		SetElement(form, i, values + i, form->element_size);
	}
	return form;
}

//Gets a pointer with index 'index' in dynamic array '*a', casted to (struct form *)
struct Form* getForm(struct DynamicArray* a, int index) {

	return (struct Form*)getArray(a, index);
}

//Gets a pointer on element with index 'index' from form '*a', casted to (double *)
double* getNumbericElement(struct Form* a, int index) {

	return (double*)GetElement(a, index);
}

//Prints a form '*form', assuming all of its elements are of the type (double)
void PrintLinearForm(struct Form* form) {

	double tmp = 0;//The element that is processing right now
	for (int i = 0; i < GetElementCount(form); i++) {
		tmp = *getNumbericElement(form, i);
		if (tmp) {//If current element is not 0
			if (i == 0)
				printf("%lg", tmp);//If it has no x, print it like it is
			else {
				//Print the sign of element
				if (tmp > 0)
					printf(" + ");
				else
					printf(" - ");
				//Printing the element and the variable
				printf("%lg*x%d", abs(tmp), i); 
			}
			
		}
	}
	printf("\n");
}

//Prints all elements of dynamic array '*a', assuming its elements are (struct Form *) and all of their elements are of the type (double)
void PrintForms(struct DynamicArray* a) {

	//Printing all the forms in '*a' with their numbers
	for (int i = 0; i < getArrayCount(a); i++) {
		printf("%d. ", i + 1);
		PrintLinearForm(getForm(a, i));
	}
}

//Returns a sum of forms '*a' and '*b,' assuming all of their elements are of the type (double)
struct Form* Sum(struct Form* a, struct Form* b) {

	struct Form* c;//Buffer form
	//If the form '*a' is longer, switch pointers, so we always add shorter form to longer one to make sure we are staying in
	//the allocated memory and not causing memory access errors
	if (GetElementCount(a) < GetElementCount(b)) {
		c = a;
		a = b;
		b = c;
	}
	//Copying longer form to 'c'
	c = createLinearForm(GetElementCount(a), getNumbericElement(a, 0));
	//Adding another form element-to-element
	for (int i = 0; i < GetElementCount(b); i++) {
		*getNumbericElement(c, i) += *getNumbericElement(b, i);
	}
	return c;
}

//Returns a form '*a', multiplied by the number 'num', assuming all of its elements are of the type (double)
struct Form* Multiply(struct Form* a, double num) {

	//Copying longer form to 'c' (buffer form)
	struct Form* c = createLinearForm(GetElementCount(a), getNumbericElement(a, 0));
	//Multiplying all the elements
	for (int i = 0; i < GetElementCount(a); i++) {
		*getNumbericElement(c, i) = *getNumbericElement(c, i) * num;
	}
	return c;
}

//Returns a numberic value of a form '*a' if its variables are '*args', assuming all of its elements are of the type (double)
double Calculate(struct Form* a, double* args) {

	//Result will be element without any x at first
	double rez = *getNumbericElement(a, 0);
	//Adding terms values ro 'rez'
	for (int i = 1; i < GetElementCount(a); i++) {
		rez += *getNumbericElement(a, i) * args[i - 1];
	}
	return rez;
}

//Returns a difference of forms '*a' and '*b,' assuming all of their elements are of the type (double)
struct Form* Subtract(struct Form* a, struct Form* b) {
	//Getting the negative of the form 'b'
	struct Form* c = Multiply(b, -1);
	//Adding it to a form 'a'
	return Sum(a, c);
}

int compareElements(struct Form* a, struct Form* b) {
	int flag = 0;
	if (GetElementCount(a) != GetElementCount(b)) {
		return 1;
	}
	else {
		for (int i = 0; i < GetElementCount(a); i++) {
			//printf("Comparing %lg with %lg\n", *((double*)GetElement(a, i)), *((double*)GetElement(b, i)));
			if (*((double*)GetElement(a, i)) != *((double*)GetElement(b, i))) {
				flag = 1;
			}
		}
	}
	return flag;
}
#include "FormWrapper.h"
#include "Form.h"
#include "DynamicArray.h"
#include <stdio.h>
#include <string.h>
#define abs(m) m>0?m:(-1)*m
#define min(m,n) m<n?m:n

//Returns a pointer to a new form of the length 'length' with values of double type, filled with elements of 'values' array 
struct Form* createLinearForm(int length, double* values) {
	
	//The value of the array elements before filling it with '*values'
	double zero = 0;
	struct Form* form = create(length, sizeof(double), &zero);
	//Filling it with '*values'
	for (int i = 0; i < getElementCount(form); i++) {
		setElement(form, i, values + i, form->element_size);
	}
	return form;
}

//Gets a pointer with index 'index' in dynamic array '*a', casted to (struct form *)
struct Form* getForm(struct DynamicArray* a, int index) {

	return (struct Form*)getArray(a, index);
}

//Gets a pointer on element with index 'index' from form '*a', casted to (double *)
double* getNumbericElement(struct Form* a, int index) {

	return (double*)getElement(a, index);
}

//Prints a form '*form', assuming all of its elements are of the type (double)
void printLinearForm(struct Form* form) {

	double tmp = 0;//The element that is processing right now
	for (int i = 0; i < getElementCount(form); i++) {
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
void printForms(struct DynamicArray* a) {

	//Printing all the forms in '*a' with their numbers
	for (int i = 0; i < getArrayCount(a); i++) {
		printf("%d. ", i + 1);
		printLinearForm(getForm(a, i));
	}
}

//Returns a sum of forms '*a' and '*b,' assuming all of their elements are of the type (double)
struct Form* sum(struct Form* a, struct Form* b) {

	struct Form* c;//Buffer form
	//If the form '*a' is longer, switch pointers, so we always add shorter form to longer one to make sure we are staying in
	//the allocated memory and not causing memory access errors
	if (getElementCount(a) < getElementCount(b)) {
		c = a;
		a = b;
		b = c;
	}
	//Copying longer form to 'c'
	c = createLinearForm(getElementCount(a), getNumbericElement(a, 0));
	//Adding another form element-to-element
	for (int i = 0; i < getElementCount(b); i++) {
		*getNumbericElement(c, i) += *getNumbericElement(b, i);
	}
	return c;
}

//Returns a form '*a', multiplied by the number 'num', assuming all of its elements are of the type (double)
struct Form* multiply(struct Form* a, double num) {

	//Copying longer form to 'c' (buffer form)
	struct Form* c = createLinearForm(getElementCount(a), getNumbericElement(a, 0));
	//Multiplying all the elements
	for (int i = 0; i < getElementCount(a); i++) {
		*getNumbericElement(c, i) = *getNumbericElement(c, i) * num;
	}
	return c;
}

//Returns a numberic value of a form '*a' if its variables are '*args', assuming all of its elements are of the type (double)
double calculate(struct Form* a, double* args) {

	//Result will be element without any x at first
	double rez = *getNumbericElement(a, 0);
	//Adding terms values ro 'rez'
	for (int i = 1; i < getElementCount(a); i++) {
		rez += *getNumbericElement(a, i) * args[i - 1];
	}
	return rez;
}

//Returns a difference of forms '*a' and '*b,' assuming all of their elements are of the type (double)
struct Form* subtract(struct Form* a, struct Form* b) {
	//Getting the negative of the form 'b'
	struct Form* c = multiply(b, -1);
	//Adding it to a form 'a'
	return sum(a, c);
}

int compareElements(struct Form* a, struct Form* b) {
	int flag = 0;
	if (getElementCount(a) != getElementCount(b)) {
		return 1;
	}
	else {
		for (int i = 0; i < getElementCount(a); i++) {
			if (*((double*)getElement(a, i)) != *((double*)getElement(b, i))) {
				flag = 1;
			}
		}
	}
	return flag;
}

void crossMultiply(struct Form* a, struct Form* b) {

	struct Form* c;
	//If the form '*a' is longer, switch pointers, so we always multiply shorter form on longer one to make sure we are staying in
	//the allocated memory and not causing memory access errors
	if (getElementCount(a) < getElementCount(b)) {
		c = a;
		a = b;
		b = c;
	}

	double tmp = 0;//The element that is processing right now
	char* str = malloc(sizeof(char)*50);//Postfix after the number containing smth like *x1*x2

	int cap;//A limit value of 'j' in the second loop

	for (int i = 0; i < getElementCount(a); i++) {

		//limiting j, so we don't repeat terms with the same x, but in different order, we will take them into count later
		cap = min(i, getElementCount(b)-1);
		for (int j = 0; j <= cap; j++) {

			tmp = (*getNumbericElement(a, i)) * (*getNumbericElement(b, j));
			//Adding terms with the same set of x, but in different order 
			if ((i != j)&&(i < getElementCount(b)))
				tmp += (*getNumbericElement(a, j)) * (*getNumbericElement(b, i));

			if (tmp) {//If current element is not 0
				if ((i == 0) && (j == 0))//Term without x
					sprintf(str, "");
				else {
					//Choosing the right format
					if (i == 0)
						sprintf(str, "*x%d", j);
					else if (j == 0)
						sprintf(str, "*x%d", i);
					else if(i == j) 
						sprintf(str, "*x%d^2", i);
					else 
						sprintf(str, "*x%d*x%d", j, i);
					
					//Choosing and printing the sign
					if (tmp > 0)
						printf(" + ");
					else
						printf(" - ");

					
				}
				//printing number and postfix
				printf("%lg%s", abs(tmp), str);
			}
		}
	}
	
}
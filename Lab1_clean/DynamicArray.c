#include "DynamicArray.h"
#include <stdlib.h>
#include <stdio.h>

//Creates a dynamic array with capacity 'BaseCapacity' and elements of size 'el_size' and returns a pointer on it
struct DynamicArray* createDynamicArray(int BaseCapacity, int el_size) {

	//Allocating memory for a dynamic array
	struct DynamicArray* a = (struct DynamicArray*)malloc(sizeof(struct DynamicArray));
	//Setting parametres of the dynamic array
	a->capacity = BaseCapacity;
	a->el_size = el_size;
	a->count = 0;
	//Allocating memory for the elements of the dynamic array (pointers)
	a->elem = (void**)malloc(a->capacity * a->el_size);
	return a;
}

//Gets a pointer with index 'index' in dynamic array '*a'
void* getArray(struct DynamicArray* a, int index) {
	
	//Can get an element like in normal array because the pointers have fixed length
	return a->elem[index];
}

//Gets a number of arrays in dynamic array '*a'
int getArrayCount(struct DynamicArray* a) {

	return a->count;
}

//Sets a pointer in dynamic array '*a' with index 'index' to 'value'
void setArray(struct DynamicArray* a, int index, void* value) {

	//Can get an element like in normal array because the pointers have fixed length
	a->elem[index] = value;
}

//Adds a new pointer 'new' to dynamic array '*a' on the place 'index'
void add(struct DynamicArray* a, void* new, int index) {

	if (a->el_size == sizeof(new)) {//If the element is of the right type (it is never violated, checking just for safety) 
		if (a->capacity <= a->count) {//If it is needed to extend the array
			//Doubling the capacity
			a->capacity = a->capacity * 2;
			//Reallocating the memory
			void** b;
			b = (void**)realloc(a->elem, a->capacity * a->el_size);
			if (b != NULL)
				a->elem = b;
			else {//If it is not enough memory, swear and stop the program
				printf("Not enough RAM! The program will be stopped!");
				exit(1);
			}
		}
		//Moving all the previous arrays towards the end of the array
		for (int i = getArrayCount(a)-1; i > index; i--) {
			setArray(a, i + 1, getArray(a, i));
		}
		//Setting the needed element and increasing number of elements
		setArray(a, index, new);
		a->count++;
	};
}

//Deletes a pointer with index 'index' in a dynamic array '*a''
void del(struct DynamicArray* a, int index) {

	//Moving all the following arrays towards the beginning of the array
	for (int i = index; i < getArrayCount(a)-1; i++) {
		setArray(a, i, getArray(a, i + 1));
	}
	//Deleting the last arrray and decreasing the count 
	free(getArray(a, getArrayCount(a)-1));
	a->count--;
}

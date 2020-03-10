#pragma once

struct DynamicArray
{
	//Array of pointers
	void** elem;
	//Size of pointer (4 bytes in x86, 8 bytes in x64)
	int el_size;
	//How much elements can an array fit before it needs to be extended
	int capacity;
	//How much elements are in array now
	int count;
};

//Creates a dynamic array with capacity 'BaseCapacity' and elements of size 'el_size' and returns a pointer on it
struct DynamicArray* createDynamicArray(int BaseCapacity, int el_size);

//Gets a pointer with index 'index' in dynamic array '*a'
void* getArray(struct DynamicArray* a, int index);

//Sets a pointer in dynamic array '*a' with index 'index' to 'value'
void setArray(struct DynamicArray* a, int index, void* value);

//Gets a number of arrays in dynamic array '*a'
int getArrayCount(struct DynamicArray* a);

//Adds a new pointer 'new' to dynamic array '*a' on the place 'index'
void add(struct DynamicArray* a, void* new, int index);

//Deletes a pointer with index 'index' in a dynamic array '*a''
void del(struct DynamicArray* a, int index);

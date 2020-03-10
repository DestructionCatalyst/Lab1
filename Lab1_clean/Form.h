#pragma once



struct Form
{
	//A pointer on the first element
	void* buffer;
	//How much elements are in the form
	int count;
	//Size (in bytes) of 1 form element
	int element_size;
};

//Sets an element of size 'size' with a index 'index' to '*value' in form '*a'
void setElement(struct Form* a, int index, void* value, int size);

//Gets a pointer on element with index 'index' from form '*a'
void* getElement(struct Form* a, int index);

//Creates a form of with 'count' elements of size 'element_size', filled with '*default_el' aand returns a pointer on it
struct Form* create(int count, int element_size, void* default_el);

//Gets a number of elements in form '*a'
int getElementCount(struct Form* a);




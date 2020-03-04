#include "Form.h"
#include <string.h>

//Gets a pointer on element with index 'index' from form '*a'
void* GetElement(struct Form* a, int index) {

	//Counting the position of needed element in memery, assuming (char) type is 1 byte long
	return (void*)(((char*)a->buffer) + index * (a->element_size));
}

//Sets an element of size 'size' with a index 'index' to '*value' in form '*a'
void SetElement(struct Form* a, int index, void* value, int size) {

	//Geting a pointer on the needed element
	void* p = GetElement(a,index);
	//Copying the content of the memory
	memcpy(p, value, size);
}

//Creates a form of with 'count' elements of size 'element_size', filled with '*default_el' aand returns a pointer on it
struct Form* Create(int count, int element_size, void* default_el) {

	//Allocating memory for a form
	struct Form* a = malloc(sizeof(struct Form));
	//Setting parametres of the form
	a->count = count;
	a->element_size = element_size;
	//Allocating memory for the elements
	a->buffer = malloc(count * element_size);
	//Fills a form with 'default_el'
	for (int i = 0;i < count;i++) 
		SetElement(a, i, default_el, a->element_size);
	return a;
}

//Gets a number of elements in form '*a'
int GetElementCount(struct Form* a) {
	
	return a->count;
}

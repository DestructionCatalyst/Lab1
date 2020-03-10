#include "Test.h"
#include "FormWrapper.h"
#include "DynamicArray.h"
#include <stdlib.h>


void testSumInt() {

	struct DynamicArray* arr = createDynamicArray(4, sizeof(struct Form*));

	double val1[4] = { 1, -3, 5, 7 };
	double val2[5] = { 0, -2, 4, -6, 8 };
	double etalon[5] = { 1, -5, 9, 1, 8 };

	add(arr, createLinearForm(4, val1), 0);
	add(arr, createLinearForm(5, val2), 1);
	add(arr, createLinearForm(5, etalon), 2);

	add(arr, sum(getArray(arr, 0), getArray(arr, 1)), 3);

	int rez = compareElements(getArray(arr, 3), getArray(arr, 2));

	printf("Program answer: ");
	printLinearForm(getArray(arr, 3));

	printf("Right answer: ");
	printLinearForm(getArray(arr,2));

	if (!rez) 
		printf("Addition completed successfully!\n");
	else 
		printf("Error in addition!\n");
	for (int i = 3; i >= 0; i--) {
		del(arr, i);
	}
	free(arr);
}

void testSumDouble() {

	struct DynamicArray* arr = createDynamicArray(4, sizeof(struct Form*));

	double val1[4] = { 1.5, 0.25, 7, 0.375 };
	double val2[5] = { 1.25, 2, 0.125, 0.125, 8.0625 };
	double etalon[5] = { 2.75, 2.25, 7.125, 0.5, 8.0625 };

	add(arr, createLinearForm(4, val1), 0);
	add(arr, createLinearForm(5, val2), 1);
	add(arr, createLinearForm(5, etalon), 2);

	add(arr, sum(getArray(arr, 0), getArray(arr, 1)), 3);

	int rez = compareElements(getArray(arr, 3), getArray(arr, 2));

	printf("Program answer: ");
	printLinearForm(getArray(arr, 3));

	printf("Right answer: ");
	printLinearForm(getArray(arr, 2));

	if (!rez)
		printf("Addition completed successfully!\n");
	else
		printf("Error in addition!\n");

	for (int i = 3; i >= 0; i--) {
		del(arr, i);
	}
	free(arr);
}

void testMultInt() {

	struct DynamicArray* arr = createDynamicArray(4, sizeof(struct Form*));

	double val1[4] = { 1, 3, 3, 7 };
	double value = 5;
	double etalon[4] = { 5, 15, 15, 35 };

	add(arr, createLinearForm(4, val1), 0);
	add(arr, createLinearForm(4, etalon), 1);

	add(arr, multiply(getArray(arr, 0), value), 2);

	printf("Program answer: ");
	printLinearForm(getArray(arr, 2));

	printf("Right answer: ");
	printLinearForm(getArray(arr, 1));

	int rez = compareElements(getArray(arr, 2), getArray(arr, 1));

	if (!rez)
		printf("Multiplication completed successfully!\n");
	else
		printf("Error in multiplication!\n");

	for (int i = 2; i >= 0; i--) {
		del(arr, i);
	}
	free(arr);
}

void testMultDouble() {

	struct DynamicArray* arr = createDynamicArray(4, sizeof(struct Form*));

	double val1[4] = { 1.5, 5, 8, 6.5 };
	double value = 1.5;
	double etalon[4] = { 2.25, 7.5, 12, 9.75 };

	add(arr, createLinearForm(4, val1), 0);
	add(arr, createLinearForm(4, etalon), 1);

	add(arr, multiply(getArray(arr, 0), value), 2);

	printf("Program answer: ");
	printLinearForm(getArray(arr, 2));

	printf("Right answer: ");
	printLinearForm(getArray(arr, 1));

	int rez = compareElements(getArray(arr, 2), getArray(arr, 1));

	if (!rez)
		printf("Multiplication completed successfully!\n");
	else
		printf("Error in multiplication!\n");

	for (int i = 2; i >= 0; i--) {
		del(arr, i);
	}
	free(arr);
}

void testCountInt() {

	struct DynamicArray* arr = createDynamicArray(4, sizeof(struct Form*));

	double val1[4] = { 5, 6, 0, 2 };
	double values[3] = { 3, 311, 10 };
	double etalon = 43;

	add(arr, createLinearForm(4, val1), 0);

	double res = calculate(getForm(arr, 0), values);

	printf("Program answer: %lg\n", res);

	printf("Right answer: %lg\n", etalon);

	int rez = (res != etalon);

	if (!rez)
		printf("Calculation completed successfully!\n");
	else
		printf("Error in calculation!\n");

	del(arr, 0);
	free(arr);
}

void testCountDouble() {

	struct DynamicArray* arr = createDynamicArray(4, sizeof(struct Form*));

	double val1[3] = { 3, 0.25, 4.5 };
	double values[2] = { 6, 2.5 };
	double etalon = 15.75;

	add(arr, createLinearForm(3, val1), 0);

	double res = calculate(getForm(arr, 0), values);

	printf("Program answer: %lg\n", res);

	printf("Right answer: %lg\n", etalon);

	int rez = (res != etalon);

	if (!rez)
		printf("Calculation completed successfully!\n");
	else
		printf("Error in calculation!\n");

	del(arr, 0);
	free(arr);
}

void testCrossMult() {

	struct DynamicArray* arr = createDynamicArray(4, sizeof(struct Form*));

	double val1[4] = { 1.5, 0, 4, 3 };
	double val2[5] = { 2, 2, 0, 5, 8 };
	//double etalon[5] = { 2.75, 2.25, 7.125, 0.5, 8.0625 };

	add(arr, createLinearForm(4, val1), 0);
	add(arr, createLinearForm(5, val2), 1);

	crossMultiply(getArray(arr, 0), getArray(arr, 1));
	//add(arr, createLinearForm(5, etalon), 2);

	/*
	add(arr, sum(getArray(arr, 0), getArray(arr, 1)), 3);

	int rez = compareElements(getArray(arr, 3), getArray(arr, 2));

	printf("Program answer: ");
	printLinearForm(getArray(arr, 3));

	printf("Right answer: ");
	printLinearForm(getArray(arr, 2));

	if (!rez)
		printf("Addition completed successfully!\n");
	else
		printf("Error in addition!\n");

		*/
	for (int i = 1; i >= 0; i--) {
		del(arr, i);
	}
	free(arr);
}
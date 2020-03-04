#include "Test.h"
#include "FormWrapper.h"
#include "DynamicArray.h"
#include <stdlib.h>


void TestSumInt() {

	struct DynamicArray* arr = CreateDynamicArray(4, sizeof(struct Form*));

	double val1[4] = { 1, -3, 5, 7 };
	double val2[5] = { 0, -2, 4, -6, 8 };
	double etalon[5] = { 1, -5, 9, 1, 8 };

	Add(arr, createLinearForm(4, val1), 0);
	Add(arr, createLinearForm(5, val2), 1);
	Add(arr, createLinearForm(5, etalon), 2);

	Add(arr, Sum(getArray(arr, 0), getArray(arr, 1)), 3);

	int rez = compareElements(getArray(arr, 3), getArray(arr, 2));

	printf("Program answer: ");
	PrintLinearForm(getArray(arr, 3));

	printf("Right answer: ");
	PrintLinearForm(getArray(arr,2));

	if (!rez) 
		printf("Addition completed successfully!\n");
	else 
		printf("Error in addition!\n");
	for (int i = 3; i >= 0; i--) {
		Delete(arr, i);
	}
	free(arr);
}

void TestSumDouble() {

	struct DynamicArray* arr = CreateDynamicArray(4, sizeof(struct Form*));

	double val1[4] = { 1.5, 0.25, 7, 0.375 };
	double val2[5] = { 1.25, 2, 0.125, 0.125, 8.0625 };
	double etalon[5] = { 2.75, 2.25, 7.125, 0.5, 8.0625 };

	Add(arr, createLinearForm(4, val1), 0);
	Add(arr, createLinearForm(5, val2), 1);
	Add(arr, createLinearForm(5, etalon), 2);

	Add(arr, Sum(getArray(arr, 0), getArray(arr, 1)), 3);

	int rez = compareElements(getArray(arr, 3), getArray(arr, 2));

	printf("Program answer: ");
	PrintLinearForm(getArray(arr, 3));

	printf("Right answer: ");
	PrintLinearForm(getArray(arr, 2));

	if (!rez)
		printf("Addition completed successfully!\n");
	else
		printf("Error in addition!\n");

	for (int i = 3; i >= 0; i--) {
		Delete(arr, i);
	}
	free(arr);
}

void TestMultInt() {

	struct DynamicArray* arr = CreateDynamicArray(4, sizeof(struct Form*));

	double val1[4] = { 1, 3, 3, 7 };
	double value = 5;
	double etalon[4] = { 5, 15, 15, 35 };

	Add(arr, createLinearForm(4, val1), 0);
	Add(arr, createLinearForm(4, etalon), 1);

	Add(arr, Multiply(getArray(arr, 0), value), 2);

	printf("Program answer: ");
	PrintLinearForm(getArray(arr, 2));

	printf("Right answer: ");
	PrintLinearForm(getArray(arr, 1));

	int rez = compareElements(getArray(arr, 2), getArray(arr, 1));

	if (!rez)
		printf("Multiplication completed successfully!\n");
	else
		printf("Error in multiplication!\n");

	for (int i = 2; i >= 0; i--) {
		Delete(arr, i);
	}
	free(arr);
}

void TestMultDouble() {

	struct DynamicArray* arr = CreateDynamicArray(4, sizeof(struct Form*));

	double val1[4] = { 1.5, 5, 8, 6.5 };
	double value = 1.5;
	double etalon[4] = { 2.25, 7.5, 12, 9.75 };

	Add(arr, createLinearForm(4, val1), 0);
	Add(arr, createLinearForm(4, etalon), 1);

	Add(arr, Multiply(getArray(arr, 0), value), 2);

	printf("Program answer: ");
	PrintLinearForm(getArray(arr, 2));

	printf("Right answer: ");
	PrintLinearForm(getArray(arr, 1));

	int rez = compareElements(getArray(arr, 2), getArray(arr, 1));

	if (!rez)
		printf("Multiplication completed successfully!\n");
	else
		printf("Error in multiplication!\n");

	for (int i = 2; i >= 0; i--) {
		Delete(arr, i);
	}
	free(arr);
}

void TestCountInt() {

	struct DynamicArray* arr = CreateDynamicArray(4, sizeof(struct Form*));

	double val1[4] = { 5, 6, 0, 2 };
	double values[3] = { 3, 311, 10 };
	double etalon = 43;

	Add(arr, createLinearForm(4, val1), 0);

	double res = Calculate(getForm(arr, 0), values);

	printf("Program answer: %lg\n", res);

	printf("Right answer: %lg\n", etalon);

	int rez = (res != etalon);

	if (!rez)
		printf("Calculation completed successfully!\n");
	else
		printf("Error in calculation!\n");

	Delete(arr, 0);
	free(arr);
}

void TestCountDouble() {

	struct DynamicArray* arr = CreateDynamicArray(4, sizeof(struct Form*));

	double val1[3] = { 3, 0.25, 4.5 };
	double values[2] = { 6, 2.5 };
	double etalon = 15.75;

	Add(arr, createLinearForm(3, val1), 0);

	double res = Calculate(getForm(arr, 0), values);

	printf("Program answer: %lg\n", res);

	printf("Right answer: %lg\n", etalon);

	int rez = (res != etalon);

	if (!rez)
		printf("Calculation completed successfully!\n");
	else
		printf("Error in calculation!\n");

	Delete(arr, 0);
	free(arr);
}
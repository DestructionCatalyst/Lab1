#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "Form.h"
#include "DynamicArray.h"
#include "FormWrapper.h"
#include "Test.h"



int main() {

	char* locale = setlocale(LC_ALL, "");

	char* command = (char*)malloc(255 * sizeof(char));

	int count;

	//Creating a new array of forms
	struct DynamicArray* arr = createDynamicArray(4, sizeof(struct Form*));

	printf("Welcome to LinearForm console application! To see the list of commands, please type 'help'.\n");

	while (1) {
	
		printf("Enter command\n");
		scanf("%s", command);
		count = getArrayCount(arr);

		if (strcmp(command, "create") == 0) {
			int len = 0;
			scanf("%d", &len);
			if (len >= 0) {
				//There will be more coefficients than variables because there is always one term without any x
				len++;
				double* values;
				values = (double*)malloc(len * sizeof(double));
				printf("Enter %d coefficients, split them using space\n", len);
				for (int i = 0; i < len; i++) {
					scanf("%lf", values + i);
				}
				//Creating a new form and adding it to the array
				struct Form* a = createLinearForm(len, values);
				add(arr, a, getArrayCount(arr));
			}
		}
		else if (strcmp(command, "print") == 0) {
			//Check Help to see how the command works
			int n = 0;
			scanf("%d", &n);
			if ((n <= 0)||(n>count)) printForms(arr);
			else printLinearForm(getForm(arr, n-1));
		}
		else if (strcmp(command, "add") == 0) {
			int arg2 = 0, arg3 = 0;
			scanf("%d %d", &arg2, &arg3);
			if ((arg2 > 0) && (arg3 > 0) && (arg2 <= count) && (arg3 <= count)) {
				//Decrementing form numbers because they actually start with zero
				arg2--;
				arg3--;
				setArray(arr, arg2, sum(getArray(arr, arg2), getArray(arr, arg3)));
			}
			else
				printf("A number of target form(s) must be positive and not greater than number of forms!");
		}
		else if (strcmp(command, "sum") == 0) {
			int arg2 = 0, arg3 = 0;
			scanf("%d %d", &arg2, &arg3);
			//Decrementing form numbers because they actually start with zero
			if ((arg2 > 0) && (arg3 > 0) && (arg2 <= count) && (arg3 <= count)) {
				arg2--;
				arg3--;
				add(arr, sum(getArray(arr, arg2), getArray(arr, arg3)), getArrayCount(arr));
			}
			else
				printf("A number of target form(s) must be positive and not greater than number of forms!");
		}
		else if (strcmp(command, "sub") == 0) {
			int arg2 = 0, arg3 = 0;
			scanf("%d %d", &arg2, &arg3);
			if ((arg2 > 0) && (arg3 > 0) && (arg2 <= count) && (arg3 <= count)) {
				//Decrementing form numbers because they actually start with zero
				arg2--;
				arg3--;
				setArray(arr, arg2, subtract(getArray(arr, arg2), getArray(arr, arg3)));
			}
			else
				printf("A number of target form(s) must be positive and not greater than number of forms!");
		}
		else if (strcmp(command, "dif") == 0) {
			int arg2 = 0, arg3 = 0;
			scanf("%d %d", &arg2, &arg3);
			if ((arg2 > 0) && (arg3 > 0) && (arg2 <= count) && (arg3 <= count)) {
				//Decrementing form numbers because they actually start with zero
				arg2--;
				arg3--;
				add(arr, subtract(getArray(arr, arg2), getArray(arr, arg3)), getArrayCount(arr));
			}
			else
				printf("A number of target form(s) must be positive and not greater than number of forms!");
		}
		else if (strcmp(command, "mult") == 0) {
			int arg2 = 0;
			double arg3 = 0;
			scanf("%d %lf", &arg2, &arg3);
			if ((arg2 > 0) && (arg2 <= count)) {
				//Decrementing form numbers because they actually start with zero
				arg2--;
				setArray(arr, arg2, multiply(getArray(arr, arg2), arg3));
			}
			else
				printf("A number of target form(s) must be positive and not greater than number of forms!");
			
		}
		else if (strcmp(command, "prod") == 0) {
			int arg2 = 0;
			double arg3 = 0;
			scanf("%d %lf", &arg2, &arg3);
			if ((arg2 > 0) && (arg2 <= count)) {
				//Decrementing form numbers because they actually start with zero
				arg2--;
				add(arr, multiply(getArray(arr, arg2), arg3), getArrayCount(arr));
			}
			else
				printf("A number of target form(s) must be positive and not greater than number of forms!");
		}
		else if (strcmp(command, "calc") == 0) {
			int arg2 = 0;
			scanf("%d", &arg2);
			double* values;
			if ((arg2 > 0) && (arg2 <= count)) {
				//Decrementing form numbers because they actually start with zero
				arg2--;
				//Entering a number for each variable in the form
				int count = getElementCount(getArray(arr, arg2)) - 1;
				values = (double*)malloc(count * sizeof(double));
				printf("Enter %d variable value(s), split them using space\n", count);
				for (int i = 0; i < count; i++) {
					scanf("%lf", values + i);
				}
				printf("%lg\n", calculate(getArray(arr, arg2), values));
			}
			else
				printf("A number of target form(s) must be positive and not greater than number of forms!");
		}
		else if (strcmp(command, "cmul") == 0) {
		int arg2 = 0, arg3 = 0;
		scanf("%d %d", &arg2, &arg3);
		if ((arg2 > 0) && (arg3 > 0) && (arg2 <= count) && (arg3 <= count)) {
			//Decrementing form numbers because they actually start with zero
			arg2--;
			arg3--;
			crossMultiply(getArray(arr, arg2), getArray(arr, arg3));
		}
		else
			printf("A number of target form(s) must be positive and not greater than number of forms!");
		}
		else if (strcmp(command, "del") == 0) {
			int arg2 = 0;
			scanf("%d", &arg2);
			if ((arg2 > 0) && (arg2 <= count)) {
				//Decrementing form numbers because they actually start with zero
				arg2--;
				del(arr, arg2);
			}
			else
				printf("A number of target form(s) must be positive and not greater than number of forms!");
		}
		else if (strcmp(command, "test") == 0) {
			int arg2 = 0;
			scanf("%d", &arg2);
			switch (arg2) {
				case 1:
					testSumInt();
					break;
				case 2:
					testSumDouble();
					break;
				case 3:
					testMultInt();
					break;
				case 4:
					testMultDouble();
					break;
				case 5:
					testCountInt();
					break;
				case 6:
					testCountDouble();
					break;
				case 7:
					testCrossMult();
					break;
				default:
					printf("test 1 - adding forms with integer elements\n");
					printf("test 2 - adding forms with float elements\n");
					printf("test 3 - multiplying form with integer elements on integer number\n");
					printf("test 4 - multiplying form with float elements on float number\n");
					printf("test 5 - calculating the value of the form with integer elements on integer number\n");
					printf("test 6 - calculating the value of the form with float elements on float number\n");
					printf("test 7 - cross-multiplying forms\n");
					break;
			}	
		}
		else if (strcmp(command, "help") == 0) {
			printf("The list of commands:\n");
			printf("create n\tCreates a linear form with n variables. You must enter n+1 coefficients after pressing Enter.\n");
			printf("print n \tPrints a linear form with number n, if n equals 0, prints all existing foims and their numbers.\n");
			printf("add a b \tFinds a sum of linear forms a and b and puts it on the place of a.\n");
			printf("sum a b \tFinds a sum of linear forms a and b and adds it to the array of existing forms.\n");
			printf("sub a b \tFinds a difference of linear forms a and b and puts it on the place of a.\n");
			printf("dif a b \tFinds a difference of linear forms a and b and adds it to the array of existing forms.\n");
			printf("mult a m\tFinds a product of linear form a and number m and puts it on the place of a.\n");
			printf("prod a m\tFinds a product of linear form a and number m and adds it to the array of existing forms.\n");
			printf("cmul a b\tFinds a product of linear form a and b and displays it on the screen.\n");
			printf("calc n  \tFinds a value of linear form n with known values of variables and displays it on the screen. \nYou must enter all variable values after pressing Enter.\n");
			printf("del n   \tDeletes a form with number a.\n");
			printf("help    \tDisplays help\n");
			printf("test    \tAn interface for testing the program. Type in 'test 0' to see the list of tests\n");
			printf("exit    \tFinishes the work of the application\n");
			printf("quit    \tFinishes the work of the application\n");
		}
		else if ((strcmp(command, "exit") && strcmp(command, "quit")) == 0) {
			//Add memory cleaning
			for (int i = count - 1; i >= 0; i--) {
				del(arr, i);
			}
			free(arr);
			return 0;
		}
		printf("\n");
	}
	return 0;
}
//Multiply linear forms
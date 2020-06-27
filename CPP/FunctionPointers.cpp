#include <stdio.h>
#include <iostream>

void add(int a, int b)
{
	printf("Addition is %d\n", a + b);
}

void subtract(int a, int b)
{
	printf("Subtraction is %d\n", a - b);
}

void multiply(int a, int b)
{
	printf("Multiplication is %d\n", a * b);
}

void randomFun(int x, int y)
{
	printf("I am random function I do nothing with %d and %d \n", x, y);
}

int main0()
{
	// fun_ptr_arr is an array of function pointers 
	void (*fun_ptr_arr[])(int, int) = { add, subtract, multiply, randomFun };
	unsigned int ch, a = 15, b = 10;

	printf("Enter Choice: 0 for add, 1 for subtract and 2 "
		"for multiply\n");
	scanf("%d", &ch);

	if (ch > 3) return 0;

	(*fun_ptr_arr[ch])(a, b);

	return 0;
}

void DoMyOperation(void (*funPtr)(int, int))
{
	int a = 100;
	int b = 10;

	std::cout << "Enter two numbers of your choice" << std::endl;

	std::cin >> a;
	std::cin >> b;

	(*funPtr) (a, b);
}

int main()
{
	std::string option = "";

	while (true)
	{
		std::cin >> option;

		if (option == "Add")
			DoMyOperation(add);
		else if (option == "Subtract")
			DoMyOperation(subtract);
		else if (option == "Multiply")
			DoMyOperation(multiply);
		else
			break;
	}

	return 0;
}

void DoMyOperation2(void (*funPtr)(int, int), int a, int b)
{
	(*funPtr) (a, b);
}

int main2()
{
	std::string option = "";

	int a = 100;
	int b = 10;

	std::cout << "Enter two numbers of your choice" << std::endl;

	std::cin >> a;
	std::cin >> b;

	while (true)
	{
		std::cin >> option;

		if (option == "Add")
			DoMyOperation2(add, a, b);
		else if (option == "Subtract")
			DoMyOperation2(subtract, a, b);
		else if (option == "Multiply")
			DoMyOperation2(multiply, a, b);
		else
			break;
	}

	return 0;
}


int add2(int a, int b)
{
	printf("Addition is %d\n", a + b);
	return a + b;
}

int subtract2(int a, int b)
{
	printf("Subtraction is %d\n", a - b);
	return a - b;
}

int multiply2(int a, int b)
{
	printf("Multiplication is %d\n", a * b);
	return a * b;
}

void DoMyOperation3(int (*funPtr)(int, int), int (*funPtr2)(int, int), int (*funPtr3)(int, int), int a, int b)
{
	(*funPtr) (funPtr2(a,b), funPtr3(b,a));
}

int main3()
{
	std::string option = "";

	int a = 100;
	int b = 10;

	std::cout << "Enter two numbers of your choice" << std::endl;

	std::cin >> a;
	std::cin >> b;

	DoMyOperation3(add2, add2, add2, a, b);

	DoMyOperation3(subtract2, subtract2, subtract2, a, b);

	DoMyOperation3(add2, subtract2, multiply2, a, b);

	return 0;
}

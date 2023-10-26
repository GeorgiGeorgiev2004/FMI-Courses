
#include <iostream>
using namespace std;
int sum(const int, const int);
bool isEven(const int a);
int min(int a, int b);
double Abs(const int num);
int Trunc(const double num);
int ascii(const char symbol);
int pow(const int num, const unsigned N);
int calculate(const int a, const int b, char action);
void askUser(const int from, const int to);
void printAllNumbersWithRepeatingDigits(int digit_one, int digit_two);
bool doesTheNumberHaveRepeatingDigits(int num);
int how_many_numbers_have_this_digit(int n);
int main()
{
	int a = 2;
	int c = 4;
	int res = how_many_numbers_have_this_digit(5);
	cout << "result : " << res;
}

//1 zad
int sum(const int a, const int b)
{
	return a + b;
}

//2 zad
bool isEven(const int a)
{
	if (a % 2 == 0)
	{
		return true;
	}
	else return false;
}

//3 zad
int min(int a, int b)
{
	if (a < b)
	{
		return a;
	}
	else return b;
}

//4 zad
double Abs(const int num)
{
	if (num < 0)
	{
		return num * -1;
	}
	else return num;
}

//5 zad
int Trunc(const double num)
{
	return (int)num;
}

//6 zad 
int ascii(const char symbol)
{
	return (int)symbol;
}

//7 zad
int pow(const int num, const unsigned N)
{
	int result = 1;
	for (size_t i = 0; i < N; i++)
	{
		result *= num;
	} return result;
}
//8 zad
int calculate(const int a, const int b, char action)
{
	int result = a + b;
	switch (action)
	{
	case'-':
		result = a - b;
		break;
	case'/':
		result = a / b;
		break;
	case'*':
		result = a * b;
		break;
	case'%':
		result = a % b;
		break;
	default:
		break;
	}
	return result;
}

//9 zad
void askUser(const int from, const int to) 
{
	int input_number = 0;
	cout << "Enter your number: ";
	cin >> input_number;
	while (input_number<from || input_number>to)
	{
		cout << "Invalid input\n" << "Enter your number: ";
		cin >> input_number;
	}
}

//11 zad
void printAllNumbersWithRepeatingDigits(int digit_one, int digit_two) 
{
	for (size_t i = digit_one; i < digit_two; i++)
	{
		if (doesTheNumberHaveRepeatingDigits(i))
		{
			cout << i<<" ";
		}
	}
}
//11.1
bool doesTheNumberHaveRepeatingDigits(int num) 
{
	int last_digit = num % 10;
	num=num / 10;
	while (num!=0)
	{
		int current_digit = num % 10;
		num = num / 10;
		if (last_digit==current_digit)
		{
			return true;
		}
		last_digit = current_digit;
	}
	return false;
}
//13 zad 
int how_many_numbers_have_this_digit(int n) 
{
	int count = 0;
	int input =0;
	cin >> input;
	while (input>0)
	{
		while (input!=0)
		{
			if (input%10==n)
			{
				count++;
				break;
			}
			input = input / 10;
		}
		cin >> input;
	}
	return count;
}
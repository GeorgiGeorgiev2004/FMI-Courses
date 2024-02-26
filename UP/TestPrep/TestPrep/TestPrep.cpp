#include <iostream>

long ConvertNumber(long& lng) 
{
	int ctr = 0;
	long ln = lng;
	while (ln > 0)
	{
		ctr++;
		ln /= 10;
	}
	long result = 0;
	for (size_t i = 0; i < ctr; i++)
	{
		int n = 1;
		for (size_t j = 1; j < ctr-i; j++)
		{
			n *= 10;
		}
		result += (lng%10) * n;
		lng /= 10;
	}
	
	return result;
}

bool date(char arr[]) 
{
	int day = (arr[0] - '0') * 10 + (arr[1] - '0');
	int month = (arr[3] - '0') * 10 + (arr[4] - '0');
	switch (month)
	{
	case 1:
		if (day >= 1 && day <= 31)
		{
			return true;
		}
		else return false;
		break;
	case 2:
		if (day >= 1 && day <= 28)
		{
			return true;
		}
		else return false;
		break;
	case 3:
		if (day >= 1 && day <= 31)
		{
			return true;
		}
		else return false;
		break;
	case 4:
		if (day >= 1 && day <= 30)
		{
			return true;
		}
		else return false;
		break;
	case 5:
		if (day >= 1 && day <= 31)
		{
			return true;
		}
		else return false;
		break;
	case 6:
		if (day >= 1 && day <= 30)
		{
			return true;
		}
		else return false;
		break;
	case 7:
		if (day >= 1 && day <= 31)
		{
			return true;
		}
		else return false;
		break;
	case 8:
		if (day >= 1 && day <= 30)
		{
			return true;
		}
		else return false;
		break;
	case 9:
		if (day >= 1 && day <= 31)
		{
			return true;
		}
		else return false;
		break;
	case 10:
		if (day >= 1 && day <= 30)
		{
			return true;
		}
		else return false;
		break;
	case 11:
		if (day >= 1 && day <= 31)
		{
			return true;
		}
		else return false;
		break;
	case 12:
		if (day >= 1 && day <= 30)
		{
			return true;
		}
		else return false;
		break;
	default:
		return false;
		break;
	}
	return false;
}

void Revert(char arr[])
{
	int i = 0;
	while (arr[i]!='\0')
	{
		if (arr[i]>='a' && arr[i] <= 'z')
		{
			arr[i] = arr[i]-32;
		}	
		else if (arr[i] >= 'A' && arr[i] <= 'Z')
		{
			arr[i] = arr[i]+32;
		}
		i++;
	}
}

int main()
{
	//Task 1
	/*int array1[3] = { 0 };
	int ctor1 = 0;
	for (int i : array1)
	{
		std::cin >> array1[ctor1];
		ctor1++;
	}
	int array2[3] = { 0 };
	int ctor2 = 0;
	for (int i : array1)
	{
		std::cin >> array2[ctor2];
		ctor2++;
	}
	const int const size = ctor1 + ctor2;
	int* array3 = new int[size];
	int i = 0;
	int counter = 0;
	for (int el : array1)
	{
		array3[i] = array1[counter];
		counter++;
		i++;
	}
	counter = 0;
	for (int el : array2)
	{
		array3[i] = array2[counter];
		counter++;
		i++;
	}
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (array3[i]<array3[j])
			{
				int temp = array3[i];
				array3[i] = array3[j];
				array3[j] = temp;
			}
		}
	}
	for (size_t i = 0; i < size; i++)
	{
		std::cout << array3[i] << " ";
	}	
	delete[] array3;*/

	//Task 2

	
	char ch[] = "20.02";
	long ln = 234876;
	long res = ConvertNumber(ln);
	std::cout << res;
}

#define _USE_MATH_DEFINES

#include <iostream>
#include<iomanip>
#include<cmath>
using namespace std;
int main()
{
    int choice = 0;
    cout << "Choose which task to target : ";
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        int number_one = 0;
        int number_two = 0;
        cout << "Enter your first number: "; cin >> number_one;
        cout << "Enter your second number: "; cin >> number_two;
        cout << "Result of their deduction: " << number_one - number_two << endl;
        break;
    }
    case 2:
        //I know declaring PI is rather easy but i preffer working with predetermined constants handpicked 
        //by microsoft
    {
        int side = 0;
        cout << "Enter your side: "; cin >> side;
        cout << fixed << setprecision(2);
        cout << "square: p=" << side * 4 << " s=" << side * side;
        cout << "\ncircle: p=" << 2 * M_PI * (float)side;
        cout << "\ntriangle : p=" << 3 * side << " s= " << ((side * side) * 1.0) * sqrt(3) / 4 << endl;
        break; }
    case 3:
    {
        const double currency_course = 0.511306792;
        double euro = 0.0;
        cout << fixed << setprecision(9);
        cout << "Input your euro: ";
        cin >> euro;
        cout << "Your leva: " << euro * currency_course; }
    break;
    case 4:
    {
        float number_one = 0;
        float number_two = 0;
        float number_three = 0;
        cout << "Enter a: ";
        cin >> number_one;
        cout << "Enter b: ";
        cin >> number_two;
        cout << "Enter x: ";
        cin >> number_three;
        if (number_three > number_one && number_three < number_two)
        {
            cout << "1";
        }
        else cout << "0";
    }
    break;
    case 5:
    {
        float number_one = 0;
        float number_two = 0;
        cout << "Insert first number: "; cin >> number_one;
        cout << "Insert second number: "; cin >> number_two;
        double result = (number_one * number_one * number_one) + (number_two * number_two * number_two) + 3 * number_one * number_two * (number_one + number_two);
        cout << "Result: " << result;
    }
    break;
    case 6:
    {
        short number = 0;
        cout << "Enter the number: "; cin >> number;
        short reversed_number = 0;
        reversed_number += 1000 * (number % 10);
        number /= 10;
        reversed_number += 100 * (number % 10);
        number /= 10;
        reversed_number += 10 * (number % 10);
        number /= 10;
        reversed_number += number % 10;
        cout << "Reversed number: " << reversed_number;
    }
    break;
    case 7: {
        short number = 0;
        cout << "Enter the number: "; cin >> number;
        short digit_4 = number % 10;
        number /= 10;
        short digit_3 = number % 10;
        number /= 10;
        short digit_2 = number % 10;
        number /= 10;
        short digit_1 = number % 10;
        cout << "sum = " << (digit_1 + digit_2 + digit_3 + digit_4) << " p=" << digit_1 * digit_2 * digit_3 * digit_4 << " avr = " << (digit_1 + digit_2 + digit_3 + digit_4) / 4.0;
    } break;
    case 8:
    {
        int number_one = 0;
        int number_two = 0;
        cout << "Enter number one : "; cin >> number_one;
        cout << "Enter number two : "; cin >> number_two;
        //Try 1 
        {
            int temp = number_one;
            number_one = number_two;
            number_two = temp;
        }
        //Try 2 
        {
            number_one = number_one + number_two;
            number_two = number_one - number_two;
            number_one = number_one - number_two;
        }
        //Try 3
        {
            number_one = number_one * number_two;
            number_two = number_one / number_two;
            number_one = number_one / number_two;
        }
        cout << "number one:" << number_one << " number two: " << number_two;
    }
    break;
    case 9:
    {
        int number_one = 0;
        int number_two = 0;
        int number_three = 0;
        int min = INT32_MAX;
        int mid = 0;
        int max = 0;
        cout << "Enter number one : "; cin >> number_one;
        cout << "Enter number two : "; cin >> number_two;
        cout << "Enter number three : "; cin >> number_three;
        if (min > number_one)
        {
            min = number_one;
        }if (min > number_two)
        {
            min = number_two;
        }
        if (min > number_three)
        {
            min = number_three;
        }
        if (max < number_one)
        {
            max = number_one;
        }if (max < number_two)
        {
            max = number_two;
        }
        if (max < number_three)
        {
            max = number_three;
        }
        if (number_one != min && number_one != max)
        {
            mid = number_one;
        }
        if (number_two != min && number_two != max)
        {
            mid = number_two;
        }
        if (number_three != min && number_three != max)
        {
            mid = number_three;
        }
        cout << "Min= " << min << " Mid = " << mid << " Max= " << max;
    }
    break;
    case 11:
    {
        int number_one = 0;
        int number_two = 0;
        int number_three = 0;
        cout << "Enter number one : "; cin >> number_one;
        cout << "Enter number two : "; cin >> number_two;
        cout << "Enter number three : "; cin >> number_three;
        int D = number_two * number_two - (number_one * 4 * number_three);
        int x1 = (-number_two + D) / (number_one*2);
        int x2 = (-number_two - D) / (number_one*2);
        cout << "x1= " << x1 << " x2= " << x2;
    }
    break;
    case 12:
    {
        int number_one = 0;
        int number_two = 0;
        cout << "Enter number one : "; cin >> number_one;
        cout << "Enter number two : "; cin >> number_two;
        //Way one
        {
            int bigger_temp = number_one > number_two ? number_one : number_two;
            cout << "Bigger number is: " << bigger_temp;
        }
        //Way two (works 50% of the times)
        {
            cout << "Bigger number is: " << number_two;
        }
    }
        break;
    case 13:
    {
        int number_one = 0;
        int number_two = 0;
        int number_three = 0;
        cout << "Enter number one : "; cin >> number_one;
        cout << "Enter number two : "; cin >> number_two;
        cout << "Enter number three : "; cin >> number_three;
        if (number_three<number_one)
        {
            cout << "1";
        } if (number_three == number_one)
        {
            cout << "2";
        }
        if (number_three > number_one && number_three<number_two)
        {
            cout << "3";
        }
        if (number_three = number_two)
        {
            cout << "4";
        }
        if (number_three > number_two)
        {
            cout << "5";
        }
    }
    break;
    case 14:
    {
        int number = 0;
        int remainder = 0;
        string a_f = "ABCDEF";
        cout << "Enter the number"; cin >> number;
        string output="";
        while(number>0)
        {
            remainder = number%16;
            number = number / 16;
            if (remainder > 9)
            {
                remainder -= 9;
                output = a_f[remainder-1]+output;
            }
            else
            {
                string remainder_stringified = "";
                remainder_stringified = remainder + '0';
                output  =remainder_stringified+output;
            }
        }
        cout << output;
    }break;
    default:
        break;
    }
}
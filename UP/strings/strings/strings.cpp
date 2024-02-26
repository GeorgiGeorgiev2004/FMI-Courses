#include <iostream>

int find_lenght(std::string word)
{
    int i = 0, count = 0;
    while (word[i] != '\0') {
        count++;
        i++;
    }
    return count;
}
int main()
{
    //Task 1
    /*std::string word = "";
    std::cin >> word;
    int ctr = find_lenght(word);
    char* start = &word[0];
    char* end = &word[ctr - 1];
    for (size_t i = 0; i < ctr/2; i++)
    {
        if (*start!=*end)
        {
            std::cout << "Your word is not a palindromial";
            return 1;
        }
    }
    std::cout << "Your word is a palindromial";*/

    //Task 2
   /* std::string word = "";
    std::cin >> word;
    int ctr = find_lenght(word); int result = 0;
    for (size_t i = 0; i < ctr; i++)
    {
        if (word[i]=='?'|| word[i] == ','|| word[i] == '!')
        {
            result++;
        }
    }
    std::cout << "In your word charachters ->?<-,->,<-,->!<- : " << result << " times!";*/


    //Task 4
    /*std::string word = "";
    std::cin >> word;
    std::string result = word;
    int ctr = find_lenght(word);
    for (size_t i = 0; i < ctr; i++)
    {
        result[i] = (char)((int)word[i] + 32);
    }
    std::cout << result;*/

    //Task5
    /*std::string S1 = "";
    std::cin >> S1;
    std::string S2 = "";
    std::cin >> S2;
    for (size_t i = 0; i < find_lenght(S1); i++)
    {
        if ((int)S1[i]>=97||(int)S1[i]<=122)
        {
            bool found_match = false;
            for (size_t j = 0; j < find_lenght(S2); j++)
            {
                if (S1[i]==S2[j])
                {
                    found_match = true;
                    S2[j] -= 32;
                    break;
                }
            }
            if (found_match)
            {
                std::cout << S1[i] << " ";
            }
        }
    }*/

    //Task 6

    std::string word = "";
    std::cin >> word;
    int ctr = find_lenght(word);
    char* ptr = &word[0];
    bool result = false;
    for (size_t i = 0; i < ctr; i++)
    {
        for (size_t j = i + 1; j < ctr; j++)
        {
            if (word[i] ==word[j])
            {
                result = true;
                break;
            };
        }
    }
    if (result)
    {
        std::cout << "Your word is not built from unique chars";
    }
    else std::cout << "Your word is built from unique chars";
}
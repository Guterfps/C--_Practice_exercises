
#include <iostream>
#include <string>

void PrintMinNumberForPattern(const std::string& strPattern);

int main()
{
    std::string inputs[] = {"IDID","D", "I", "DD", "II", "DIDI", "IIDDD", 
                            "DDIDDIID"};

    for (auto input : inputs)
    {
        std::cout << "input string: " << input << " -> ";
        std::cout << "output string: ";
        PrintMinNumberForPattern(input);
    }

    return 0;
}

void PrintMinNumberForPattern(const std::string& strPattern)
{
    if (strPattern.length() >= 9)
    {
        throw std::invalid_argument("Invalid input");
    }
    
    std::string res("");

    std::size_t i = 0;
    int curr = 1;
    int dCount = 0;

    while (i < strPattern.length())
    {
        char ch = strPattern[i];
        if ((0 == i) && ('I' == ch))
        {
            res += std::to_string(curr);
            ++curr;
        }

        if ('D' == ch)
        {
            ++dCount;
        }

        std::size_t j = i + 1;
        while ((j < strPattern.length()) && ('D' == strPattern[j]))
        {
            ++dCount;
            ++j;
        }

        int temp = dCount;
        while (dCount >= 0)
        {
            res += std::to_string(curr + dCount);
            --dCount;
        }

        curr += temp + 1;
        i = j;
        dCount = 0;
    }

    std::cout << res << std::endl;
}
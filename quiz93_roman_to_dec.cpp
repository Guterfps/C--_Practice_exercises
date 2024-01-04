
#include <iostream>
#include <string>
#include <unordered_map>

int RomanToDecimal(const std::string& num);

int main()
{
    std::string num1("MCMXCIV");
    std::string num2("MMXIV");
    std::string num3("MCMIV");
    std::string num4("MMXIII");
    std::string num5("IL");
    std::string num6("XLIX");

    std::cout << "Roman number: " << num1 << " is " 
    << RomanToDecimal(num1) << " in decimal, ";
    (1994 == RomanToDecimal(num1)) ?
    std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";

    std::cout << "Roman number: " << num2 << " is " 
    << RomanToDecimal(num2) << " in decimal, ";
    (2014 == RomanToDecimal(num2)) ?
    std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";

    std::cout << "Roman number: " << num3 << " is " 
    << RomanToDecimal(num3) << " in decimal, ";
    (1904 == RomanToDecimal(num3)) ?
    std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";

    std::cout << "Roman number: " << num4 << " is " 
    << RomanToDecimal(num4) << " in decimal, ";
    (2013 == RomanToDecimal(num4)) ?
    std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";

    std::cout << "Roman number: " << num5 << " is " 
    << RomanToDecimal(num5) << " in decimal, ";
    (49 == RomanToDecimal(num5)) ?
    std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";

    std::cout << "Roman number: " << num6 << " is " 
    << RomanToDecimal(num6) << " in decimal, ";
    (49 == RomanToDecimal(num6)) ?
    std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";

    return 0;
}

int RomanToDecimal(const std::string& num)
{
    std::unordered_map<char, int> map = {{'I', 1}, {'V', 5}, {'X', 10}, 
                                        {'L', 50}, {'C', 100}, {'D', 500}, 
                                        {'M', 1000}};
    int result = 0;

    for (std::size_t i = 0; i < num.size(); ++i)
    {
        if (((i + 1) < num.size()) && (map[num[i]] < map[num[i + 1]]))
        {
            result -= map[num[i]];
        }
        else
        {
            result += map[num[i]];
        }
    }

    return result;
}
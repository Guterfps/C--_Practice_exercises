
#include <iostream>
#include <string>
#include <vector>

std::size_t CountWaysToDecodeStr(const std::string& str);

int main()
{
    std::string strings[] = {"111", "1234", "121", "12", "1020",
    "123", "1212", "226", "06", "1212121212"};

    for (auto str : strings)
    {
        std::cout << "num of ways to decode '" << str << "' : ";
        std::cout << CountWaysToDecodeStr(str) << std::endl;
    }

    return 0;
}

std::size_t CountWaysToDecodeStr(const std::string& str)
{
    std::vector<std::size_t> counters(str.size() + 1, 0);
    counters[0] = 1;
    counters[1] = 1;

    if ('0' == str[0])
    {
        return 0;
    }

    for (std::size_t i = 2; i <= str.size(); ++i)
    {
        counters[i] = 0;
        if (str[i - 1] > '0')
        {
            counters[i] = counters[i - 1];
        }

        if (('1' == str[i - 2]) || 
            (('2' == str[i - 2]) && (str[i - 1] <= '6')))
        {
            counters[i] += counters[i - 2];
        }
    }

    return counters[str.size()];
}
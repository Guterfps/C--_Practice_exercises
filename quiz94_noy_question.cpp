
#include <iostream>
#include <string>
#include <vector>

std::string CountAndSay(const std::string& curr);
std::string CountAndSay(std::size_t n);

int main()
{
    std::string test1 = "1";
    std::string test2 = "11";
    std::string test3 = "21";
    std::string test4 = "1211";
    std::string test5 = "111221";

    std::string res1 = CountAndSay(test1);
    std::cout << "test: " << test1 << " -> " << res1;
    (res1 == test2) ? std::cout << " SUCCESS ✅\n" : std::cout << " FAIL ❌\n";

    std::string res2 = CountAndSay(test2);
    std::cout << "test: " << test2 << " -> " << res2;
    (res2 == test3) ? std::cout << " SUCCESS ✅\n" : std::cout << " FAIL ❌\n";
    
    std::string res3 = CountAndSay(test3);
    std::cout << "test: " << test3 << " -> " << res3;
    (res3 == test4) ? std::cout << " SUCCESS ✅\n" : std::cout << " FAIL ❌\n";
    
    std::string res4 = CountAndSay(test4);
    std::cout << "test: " << test4 << " -> " << res4;
    (res4 == test5) ? std::cout << " SUCCESS ✅\n" : std::cout << " FAIL ❌\n";

    std::string res5 = CountAndSay(test5);
    std::cout << "test: " << test5 << " -> " << res5;
    (res5 == "312211") ? std::cout << " SUCCESS ✅\n" : std::cout << " FAIL ❌\n";

    std::string results[] = {test1, test2, test3, test4, test5, 
                                    "312211", "13112221", "1113213211", 
                                    "31131211131221", "13211311123113112211"};
    
    std::cout << "test original problem: \n";
    bool status = true;
    for (std::size_t i = 1; (i <= 10) && status; ++i)
    {
        status = (CountAndSay(i) == results[i - 1]);
        std::cout << CountAndSay(i) << "\n";
    }

    status ? std::cout << " SUCCESS ✅\n" : std::cout << " FAIL ❌\n";

    return 0;
}

std::string CountAndSay(const std::string& curr)
{
    std::string result;

    for (std::size_t i = 0; i < curr.size();)
    {
        std::size_t count = 0;
        char temp = curr[i];
        while ((i < curr.size()) && (temp == curr[i]))
        {
            ++count;
            ++i;
        }
        result.append(std::to_string(count));
        result.push_back(temp);
    }

    return result;
}

std::string CountAndSay(std::size_t n)
{
    static std::vector<std::string> cache(1, "1");

    if (n > cache.size())
    {
        for (std::size_t i = cache.size(); i < n; ++i)
        {
            cache.push_back(CountAndSay(cache[i - 1]));
        }
    }

    return cache[n - 1];
}
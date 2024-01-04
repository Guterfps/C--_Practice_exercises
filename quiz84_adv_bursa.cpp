
#include <iostream>
#include <vector>

std::size_t MaxProfit(std::vector<std::size_t> &prices);

int main()
{
    std::vector<std::size_t> prices{1, 2, 3, 4, 5};
    std::cout << "test1: \n";
    std::size_t res = MaxProfit(prices);
    std::cout << res << ", ";
    (4 == res) ? std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";

    std::vector<std::size_t> prices2{5, 4, 3, 2, 1};
    std::cout << "test2: \n";
    std::size_t res2 = MaxProfit(prices2);
    std::cout << res2 << ", ";
    (0 == res2) ? 
    std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";

    std::vector<std::size_t> prices3{8,2,6,2,6,3,7};
    std::cout << "test3: \n";
    std::size_t res3 = MaxProfit(prices3);
    std::cout << res3 << ", ";
    (8 == res3) ? 
    std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";

    std::vector<std::size_t> prices4{8,2,6,1,20,3,7};
    std::cout << "test4: \n";
    std::size_t res4 = MaxProfit(prices4);
    std::cout << res4 << ", ";
    (19 == res4) ? 
    std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";

    std::vector<std::size_t> prices5{8,2,6,5,20,3,7};
    std::cout << "test1: \n";
    long long res5 = MaxProfit(prices5);
    std::cout << res5 << ", ";
    (18 == res5) ? std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";

    return 0;
}

std::size_t MaxProfit(std::vector<std::size_t> &prices)
{
    std::size_t ogSize = prices.size();
    std::vector<std::vector<long long>> dp(ogSize + 1, 
                                        std::vector<long long>(3, 0));
    prices.push_back(0);
    dp[0][0] = -prices[0];
    for (std::size_t i = 1; i <= ogSize; ++i)
    {
        dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][2] - 
                    static_cast<long long>(prices[i]));
        dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][0] + 
                    static_cast<long long>(prices[i]));
        dp[i][2] = dp[i - 1][1];
    }
    
    return dp[ogSize - 1][1];
}
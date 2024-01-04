
#include <iostream>
#include <sys/types.h>
#include <climits>

ssize_t MinCoinsForSum(std::size_t *coins, 
                        std::size_t coins_size, 
                        std::size_t sum); 
void InitTable(std::size_t *table, std::size_t table_size);

int main(void)
{
    std::size_t coins1[] = {1, 5, 10, 25};
    std::size_t coins_size1 = sizeof(coins1) / sizeof(coins1[0]);
    std::size_t sum1 = 30;

    ssize_t result = MinCoinsForSum(coins1, coins_size1, sum1);
    std::cout << "min num of coins for sum " << sum1 << " is " << result;
    (2 == result) ? std::cout << " SUCCESS ✅\n" : std::cout << " FAIL ❌\n";
    
    std::size_t coins2[] = {9, 6, 5, 1};
    std::size_t coins_size2 = sizeof(coins2) / sizeof(coins2[0]);
    std::size_t sum2 = 11;

    result = MinCoinsForSum(coins2, coins_size2, sum2);
    std::cout << "min num of coins for sum " << sum2 << " is " << result;
    (2 == result) ? std::cout << " SUCCESS ✅\n" : std::cout << " FAIL ❌\n";

    std::size_t coins3[] = {1, 2, 5};
    std::size_t coins_size3 = sizeof(coins3) / sizeof(coins3[0]);
    std::size_t sum3 = 13;

    result = MinCoinsForSum(coins3, coins_size3, sum3);
    std::cout << "min num of coins for sum " << sum3 << " is " << result;
    (4 == result) ? std::cout << " SUCCESS ✅\n" : std::cout << " FAIL ❌\n";

    std::size_t coins4[] = {2, 5};
    std::size_t coins_size4 = sizeof(coins4) / sizeof(coins4[0]);
    std::size_t sum4 = 3;

    result = MinCoinsForSum(coins4, coins_size4, sum4);
    std::cout << "min num of coins for sum " << sum4 << " is " << result;
    (-1 == result) ? std::cout << " SUCCESS ✅\n" : std::cout << " FAIL ❌\n";
    
    return 0;
}

ssize_t MinCoinsForSum(std::size_t *coins, 
                        std::size_t coins_size, 
                        std::size_t sum)
{
    std::size_t *table = new std::size_t[sum + 1];
    table[0] = 0;
    InitTable(table, sum);

    for (std::size_t i = 1; i <= sum; ++i)
    {
        for (std::size_t j = 0; j < coins_size; ++j)
        {
            if (coins[j] <= i)
            {
                std::size_t tmp = table[i - coins[j]];
                if ((ULONG_MAX != tmp) && ((tmp + 1) < table[i]))
                {
                    table[i] = tmp + 1;
                }
            }
        }
    }

    std::size_t ret = table[sum];
    delete[] table;

    return ((ULONG_MAX != ret) ? ret : -1);
}

void InitTable(std::size_t *table, std::size_t table_size)
{
    for (std::size_t i = 1; i <= table_size; ++i)
    {
        table[i] = ULONG_MAX;
    }
}
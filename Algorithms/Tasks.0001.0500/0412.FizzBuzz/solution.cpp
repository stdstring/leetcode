#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::string> fizzBuzz(int n) const
    {
        std::vector<std::string> result;
        for (int number = 1; number <= n; ++number)
        {
            if (number % 3 == 0 && number % 5 == 0)
                result.emplace_back("FizzBuzz");
            else if (number % 3 == 0)
                result.emplace_back("Fizz");
            else if (number % 5 == 0)
                result.emplace_back("Buzz");
            else
                result.push_back(std::to_string(number));
        }
        return result;
    }
};

}

namespace FizzBuzzTask
{

TEST(FizzBuzzTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"1", "2", "Fizz", "4", "Buzz", "Fizz", "7", "8", "Fizz", "Buzz", "11", "Fizz", "13", "14", "FizzBuzz"}), solution.fizzBuzz(15));
}

}
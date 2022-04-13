#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct SumResult
{
    SumResult(int bit, int carry) : Bit(bit), Carry(carry)
    {
    }

    int Bit;
    int Carry;
};

class Solution
{
public:
    [[nodiscard]] std::vector<int> addNegabinary(std::vector<int> const &arr1, std::vector<int> const &arr2) const
    {
        const std::unordered_map<int, SumResult> sumTable = {{-2, {0, 1}}, {-1, {1, 1}}, {0, {0, 0}}, {1, {1, 0}}, {2, {0, -1}}, {3, {1, -1}}};
        int carry = 0;
        std::vector<int> result;
        for (auto riterator1 = arr1.crbegin(), riterator2 = arr2.crbegin(); riterator1 != arr1.crend() || riterator2 != arr2.crend() || carry != 0;)
        {
            int sum = carry;
            if (riterator1 != arr1.crend())
            {
                sum += *riterator1;
                ++riterator1;
            }
            if (riterator2 != arr2.crend())
            {
                sum += *riterator2;
                ++riterator2;
            }
            SumResult sumResult(sumTable.at(sum));
            result.push_back(sumResult.Bit);
            carry = sumResult.Carry;
        }
        while ((result.size() > 1) && (result[result.size() - 1] == 0))
            result.pop_back();
        std::reverse(result.begin(), result.end());
        return result;
    }
};

}

namespace AddingTwoNegabinaryNumbersTask
{

TEST(AddingTwoNegabinaryNumbersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 0, 0, 0, 0}), solution.addNegabinary({1, 1, 1, 1, 1}, {1, 0, 1}));
    ASSERT_EQ(std::vector<int>({0}), solution.addNegabinary({0}, {0}));
    ASSERT_EQ(std::vector<int>({1}), solution.addNegabinary({0}, {1}));
}

TEST(AddingTwoNegabinaryNumbersTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({0}), solution.addNegabinary({1}, {1, 1}));
}

}
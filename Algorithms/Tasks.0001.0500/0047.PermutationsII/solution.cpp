#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> permuteUnique(std::vector<int> const &nums) const
    {
        std::vector<int> numbers(nums);
        std::sort(numbers.begin(), numbers.end());
        std::vector<bool> usedNumbers;
        for (size_t index = 0; index < numbers.size(); ++index)
            usedNumbers.push_back(false);
        std::vector<int> current;
        std::vector<std::vector<int>> dest;
        generate(numbers, usedNumbers, current, dest);
        return dest;
    }

private:
    void generate(std::vector<int> const &numbers, std::vector<bool> &usedNumbers, std::vector<int> &current, std::vector<std::vector<int>> &dest) const
    {
        size_t lastUsedIndex = numbers.size();
        for (size_t index = 0; index < numbers.size(); ++index)
        {
            if (!usedNumbers[index])
            {
                if (lastUsedIndex != numbers.size() && numbers[lastUsedIndex] == numbers[index])
                    continue;
                lastUsedIndex = index;
                current.push_back(numbers[index]);
                const bool isPermutation = current.size() == numbers.size();
                if (isPermutation)
                    dest.push_back(current);
                else
                {
                    usedNumbers[index] = true;
                    generate(numbers, usedNumbers, current, dest);
                    usedNumbers[index] = false;
                }
                current.pop_back();
                if (isPermutation)
                    return;
            }
        }
    }
};

}

namespace PermutationsIITask
{

TEST(PermutationsIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 1, 2}, {1, 2, 1}, {2, 1, 1}}), solution.permuteUnique({1, 1, 2}));
}

}

#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> permute(std::vector<int> const &nums) const
    {
        std::vector<bool> usedNumbers;
        for (size_t index = 0; index < nums.size(); ++index)
            usedNumbers.push_back(false);
        std::vector<std::vector<int>> dest;
        std::vector<int> current;
        generate(nums, usedNumbers, current, dest);
        return dest;
    }

private:
    void generate(std::vector<int> const &nums, std::vector<bool> &usedNumbers, std::vector<int> &current, std::vector<std::vector<int>> &dest) const
    {
        for (size_t index = 0; index < nums.size(); ++index)
        {
            if (!usedNumbers[index])
            {
                current.push_back(nums[index]);
                const bool isPermutation = current.size() == nums.size();
                if (isPermutation)
                    dest.push_back(current);
                else
                {
                    usedNumbers[index] = true;
                    generate(nums, usedNumbers, current, dest);
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

namespace PermutationsTask
{

TEST(PermutationsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}}), solution.permute({1, 2, 3}));
}

}

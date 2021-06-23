#include <map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isPossibleDivide(std::vector<int> const &nums, int k) const
    {
        if (nums.size() % k != 0)
            return false;
        std::map<int, int> numbersMap;
        for (int number : nums)
            ++numbersMap[number];
        for (size_t group = 0; group < nums.size() / k; ++group)
        {
            auto iterator = numbersMap.begin();
            int prevNumber = iterator->first;
            --iterator->second;
            iterator = checkMoveNext(numbersMap, iterator);
            for (size_t groupIndex = 1; groupIndex < static_cast<size_t>(k); ++groupIndex)
            {
                if (iterator == numbersMap.end())
                    return false;
                if (iterator->first > prevNumber + 1)
                    return false;
                prevNumber = iterator->first;
                --iterator->second;
                iterator = checkMoveNext(numbersMap, iterator);
            }
        }
        return true;
    }

private:
    std::map<int, int>::iterator checkMoveNext(std::map<int, int> &numbersMap, std::map<int, int>::iterator iterator) const
    {
        if (iterator->second == 0)
        {
            const auto current = iterator++;
            numbersMap.erase(current);
        }
        else
            ++iterator;
        return iterator;
    }
};

}

namespace DivideArrayInSetsKConsecutiveNumbersTask
{

TEST(DivideArrayInSetsKConsecutiveNumbersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isPossibleDivide({1, 2, 3, 3, 4, 4, 5, 6}, 4));
    ASSERT_EQ(true, solution.isPossibleDivide({3, 2, 1, 2, 3, 4, 3, 4, 5, 9, 10, 11}, 3));
    ASSERT_EQ(true, solution.isPossibleDivide({3, 3, 2, 2, 1, 1}, 3));
    ASSERT_EQ(false , solution.isPossibleDivide({1, 2, 3, 4}, 3));
}

}
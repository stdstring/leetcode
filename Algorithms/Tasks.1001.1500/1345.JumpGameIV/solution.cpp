#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minJumps(std::vector<int> const &arr) const
    {
        std::unordered_map<int, std::vector<size_t>> valuesMap;
        for (size_t index = 0; index < arr.size(); ++index)
            valuesMap[arr[index]].push_back(index);
        if (arr.size() == 1)
            return 0;
        std::vector<size_t> jumpSizes(arr.size(), 0);
        std::vector<size_t> jumps(arr.size(), 0);
        jumpSizes[0] = 0;
        size_t start = 0;
        size_t next = 1;
        while (start < arr.size())
        {
            const size_t currentIndex = jumps[start++];
            const size_t currentSize = jumpSizes[currentIndex];
            if ((currentIndex > 0) && (jumpSizes[currentIndex - 1] == 0))
            {
                jumps[next++] = currentIndex - 1;
                jumpSizes[currentIndex - 1] = currentSize + 1;
            }
            if ((currentIndex < (arr.size() - 1)) && (jumpSizes[currentIndex + 1] == 0))
            {
                if ((currentIndex + 1) == (arr.size() - 1))
                    return static_cast<int>(currentSize + 1);
                jumps[next++] = currentIndex + 1;
                jumpSizes[currentIndex + 1] = currentSize + 1;
            }
            for (auto iterator = valuesMap[arr[currentIndex]].crbegin(); iterator != valuesMap[arr[currentIndex]].crend(); ++iterator)
            {
                const size_t index = *iterator;
                if (index == (arr.size() - 1))
                    return static_cast<int>(currentSize + 1);
                if (jumpSizes[index] == 0)
                {
                    jumps[next++] = index;
                    jumpSizes[index] = currentSize + 1;
                }
            }
            valuesMap.erase(arr[currentIndex]);
        }
        return -1;
    }
};

}

namespace JumpGameIVTask
{

TEST(JumpGameIVTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.minJumps({100, -23, -23, 404, 100, 23, 23, 23, 3, 404}));
    ASSERT_EQ(0, solution.minJumps({7}));
    ASSERT_EQ(1, solution.minJumps({7, 6, 9, 6, 9, 6, 9, 7}));
}

TEST(JumpGameIVTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(2, solution.minJumps({6, 1, 9}));
    ASSERT_EQ(3, solution.minJumps({7, 7, 2, 1, 7, 7, 7, 3, 4, 1}));
}

}
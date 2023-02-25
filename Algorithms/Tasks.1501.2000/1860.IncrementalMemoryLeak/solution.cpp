#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> memLeak(int memory1, int memory2) const
    {
        for (int time = 1;; ++time)
        {
            const int consumingMemory = time;
            if (std::max(memory1, memory2) < consumingMemory)
                return {time, memory1, memory2};
            (memory1 >= memory2 ? memory1 : memory2) -= consumingMemory;
        }
    }
};

}

namespace IncrementalMemoryLeakTask
{

TEST(IncrementalMemoryLeakTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({3, 1, 0}), solution.memLeak(2, 2));
    ASSERT_EQ(std::vector<int>({6, 0, 4}), solution.memLeak(8, 11));
}

TEST(IncrementalMemoryLeakTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({50, 17, 43}), solution.memLeak(578, 707));
}

}
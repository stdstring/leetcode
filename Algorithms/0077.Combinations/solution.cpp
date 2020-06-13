#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> combine(int n, int k)
    {
        std::vector<std::vector<int>> combinations;
        std::vector<int> buffer;
        buffer.reserve(k);
        combineImpl(n, k, combinations, buffer);
        return combinations;
    }

private:
    void combineImpl(int n, int k, std::vector<std::vector<int>> &combinations, std::vector<int> &buffer)
    {
        if (buffer.size() == k)
            combinations.emplace_back(buffer);
        else
        {
            int size = buffer.size();
            for (int number = size == 0 ? 1 : buffer.back() + 1; number <= (n - k + size + 1); ++number)
            {
                buffer.push_back(number);
                combineImpl(n, k, combinations, buffer);
                buffer.pop_back();
            }
        }
    }
};

}

namespace CombinationsTask
{

TEST(CombinationsTaskTests, Examples)
{
    Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}}), solution.combine(4, 2));
}

}
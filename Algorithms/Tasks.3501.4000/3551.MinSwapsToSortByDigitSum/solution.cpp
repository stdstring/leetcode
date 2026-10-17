#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minSwaps(std::vector<int> const &nums) const
    {
        // We are given an array nums of distinct positive integers that must be sorted in ascending order by each number's digit sum,
        // breaking ties by placing smaller numbers first.
        // Our goal is to determine the minimum number of swaps required to transform the original array into this target order.
        // Because all elements in nums are distinct, each element has a unique target position after sorting.
        // We can therefore treat the mapping from each element's original position to its target position as a permutation,
        // reducing this to the classic problem of finding the minimum number of swaps needed to sort a permutation.
        // For a permutation of length n, treat the n positions as n nodes in a graph,
        // and add a directed edge from each position i to the target position targets[i] of the element currently at index i.
        // Since every node has both in-degree and out-degree equal to 1, the graph decomposes into disjoint directed cycles, known as permutation cycles.
        // For a permutation cycle of length k, exactly k-1 swaps are needed to move all elements to their correct positions.
        // Therefore, the total minimum number of swaps is: Sum(k(i) - 1) = Sum(k(i)) - cycles = n - cycles
        // Here, k(i) is the length of the i-th permutation cycle, and cycles is the number of permutation cycles.
        std::vector<int> digitSums(nums.size(), 0);
        for (size_t index = 0; index < nums.size(); ++index)
            digitSums[index] = calcDigitSum(nums[index]);
        std::vector<size_t> indices(nums.size(), 0);
        std::ranges::iota(indices, 0);
        auto comp = [&nums, &digitSums](size_t l, size_t r){
            if (digitSums[l] != digitSums[r])
                return digitSums[l] < digitSums[r];
            return nums[l] < nums[r];
        };
        std::ranges::sort(indices, comp);
        std::vector<size_t> targets(nums.size(), 0);
        for (size_t index = 0; index < nums.size(); ++index)
            targets[indices[index]] = index;
        std::vector<bool> visited(nums.size(), false);
        size_t cycles = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            if (visited[index])
                continue;
            ++cycles;
            for (size_t current = index; !visited[current]; current = targets[current])
                visited[current] = true;
        }
        return static_cast<int>(nums.size() - cycles);
    }

private:
    [[nodiscard]] int calcDigitSum(int number) const
    {
        int result = 0;
        for (; number > 0; number /= 10)
            result += (number % 10);
        return result;
    }
};

}

namespace MinSwapsToSortByDigitSumTask
{

TEST(MinSwapsToSortByDigitSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minSwaps({37, 100}));
    ASSERT_EQ(0, solution.minSwaps({22, 14, 33, 7}));
    ASSERT_EQ(2, solution.minSwaps({18, 43, 34, 16}));
}

}
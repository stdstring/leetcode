#include <set>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<long long> mostFrequentIDs(std::vector<int> const &nums, std::vector<int> const &freq) const
    {
        std::unordered_map<int, long long> idMap;
        std::multiset<long long> freqSet;
        std::vector<long long> answer(nums.size(), 0);
        for (size_t index = 0; index < nums.size(); ++index)
        {
            auto idIterator = idMap.find(nums[index]);
            if (idIterator == idMap.cend())
                idIterator = idMap.emplace(nums[index], 0).first;
            else
                freqSet.erase(freqSet.find(idIterator->second));
            idIterator->second += freq[index];
            if (idIterator->second == 0)
                idMap.erase(idIterator);
            else
                freqSet.emplace(idIterator->second);
            answer[index] = freqSet.empty() ? 0 : *freqSet.crbegin();
        }
        return answer;
    }
};

}

namespace MostFrequentIDsTask
{

TEST(MostFrequentIDsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<long long>({3, 3, 2, 2}), solution.mostFrequentIDs({2, 3, 2, 1}, {3, 2, -3, 1}));
    ASSERT_EQ(std::vector<long long>({2, 0, 1}), solution.mostFrequentIDs({5, 5, 3}, {2, -2, 1}));
}

TEST(MostFrequentIDsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<long long>({4, 0, 3, 3, 3}), solution.mostFrequentIDs({3, 3, 4, 3, 10}, {4, -4, 3, 1, 2}));
}

}
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<long long> getDistances(std::vector<int> const &arr) const
    {
        std::unordered_map<int, std::vector<long long>> numberIndicesMap;
        for (size_t index = 0; index < arr.size(); ++index)
            numberIndicesMap[arr[index]].emplace_back(index);
        std::vector<long long> result(arr.size(), 0);
        for (auto const &[_, indices] : numberIndicesMap)
        {
            if (indices.size() == 1)
                continue;
            long long suffixIndicesSum = std::accumulate(indices.cbegin(), indices.cend(), 0LL);
            long long prefixIndicesSum = 0;
            for (size_t index = 0; index < indices.size(); ++index)
            {
                const long long current = indices[index];
                suffixIndicesSum -= current;
                const long long intervalsBefore = static_cast<int>(index);
                const long long intervalsAfter = static_cast<int>(indices.size() - 1 - index);
                result[current] = intervalsBefore * current - prefixIndicesSum + suffixIndicesSum - intervalsAfter * current;
                prefixIndicesSum += current;
            }
        }
        return result;
    }
};

}

namespace IntervalsBetweenIdenticalElementsTask
{

TEST(IntervalsBetweenIdenticalElementsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<long long>({4, 2, 7, 2, 4, 4, 5}), solution.getDistances({2, 1, 3, 1, 2, 3, 3}));
    ASSERT_EQ(std::vector<long long>({5, 0, 3, 4}), solution.getDistances({10, 5, 10, 10}));
}

}
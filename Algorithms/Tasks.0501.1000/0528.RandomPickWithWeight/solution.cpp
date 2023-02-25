#include <map>
#include <numeric>
#include <random>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    Solution(std::vector<int> const &w) : _generator(std::random_device()())
    {
        int currentSum = 0;
        for(size_t index = 0; index < w.size(); ++index)
        {
            _prefixSumMap.emplace(currentSum, index);
            currentSum += w[index];
        }
        _prefixSumMap.emplace(currentSum, w.size());
        _distribution = std::uniform_int_distribution<>(0, currentSum - 1);
    }

    int pickIndex()
    {
        const int randomNumber = _distribution(_generator);
        auto iterator = _prefixSumMap.lower_bound(randomNumber);
        if (iterator->first > randomNumber)
            --iterator;
        return static_cast<int>(iterator->second);
    }

private:
    std::map<int, size_t> _prefixSumMap;
    std::mt19937 _generator;
    std::uniform_int_distribution<> _distribution;
};

}

namespace
{

bool contains(std::vector<int> const &sourceValues, int value)
{
    return std::find(sourceValues.cbegin(), sourceValues.cend(), value) != sourceValues.cend();
}

void checkSolution(std::vector<int> const &w, size_t pickIndexCallCount)
{
    Solution solution(w);
    std::vector<int> indices(w.size(), 0);
    std::iota(indices.begin(), indices.end(), 0);
    // TODO (std_string) : think about check for uniform distribution
    for (size_t pickIndexCallIndex = 0; pickIndexCallIndex < pickIndexCallCount; ++pickIndexCallIndex)
        ASSERT_TRUE(contains(indices, solution.pickIndex()));
}

}

namespace RandomPickWithWeightTask
{

TEST(RandomPickWithWeightTaskTests, Examples)
{
    checkSolution({1}, 1);
    checkSolution({1, 3}, 5);
}

TEST(RandomPickWithWeightTaskTests, FromWrongAnswers)
{
    checkSolution({1, 3, 1}, 5);
}

}
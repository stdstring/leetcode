#include <algorithm>
#include <map>
#include <random>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    Solution(int n, std::vector<int> const &blacklist) : _generator(std::random_device()())
    {
        int freeNumbersCount = n - static_cast<int>(blacklist.size());
        _distribution = std::uniform_int_distribution<>(0, freeNumbersCount - 1);
        std::vector<int> sortedBlacklist(blacklist);
        std::sort(sortedBlacklist.begin(), sortedBlacklist.end());
        int currentNumber = 0;
        int currentFreeNumber = 0;
        for (const int blackNumber : sortedBlacklist)
        {
            if (currentNumber < blackNumber)
            {
                _freeNumberRanges.emplace(currentFreeNumber, std::pair<int, int>(currentNumber, blackNumber - 1));
                currentFreeNumber += (blackNumber - currentNumber);
            }
            currentNumber = blackNumber + 1;
        }
        if (currentNumber < n)
            _freeNumberRanges.emplace(currentFreeNumber, std::pair<int, int>(currentNumber, n - 1));
        _freeNumberRanges.emplace(freeNumbersCount, std::pair<int, int>(n, n));
    }

    int pick()
    {
        const int randomNumber = _distribution(_generator);
        auto iterator = _freeNumberRanges.lower_bound(randomNumber);
        if (iterator->first > randomNumber)
            --iterator;
        return iterator->second.first + (randomNumber - iterator->first);
    }

private:
    std::mt19937 _generator;
    std::uniform_int_distribution<> _distribution;
    std::map<int, std::pair<int, int>> _freeNumberRanges;
};

}

namespace
{

bool contains(std::vector<int> const &sourceValues, int value)
{
    return std::find(sourceValues.cbegin(), sourceValues.cend(), value) != sourceValues.cend();
}

}

namespace RandomPickWithBlacklistTask
{

TEST(RandomPickWithBlacklistTaskTests, Examples)
{
    constexpr size_t pickCallCount = 10;
    Solution solution(7, {2, 3, 5});
    // TODO (std_string) : think about check for uniform distribution
    for (size_t callIndex = 0; callIndex < pickCallCount; ++callIndex)
        contains({0, 1, 4, 6}, solution.pick());
}

}
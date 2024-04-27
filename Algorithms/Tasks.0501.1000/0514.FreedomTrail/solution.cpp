#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findRotateSteps(std::string const &ring, std::string const &key) const
    {
        constexpr size_t absentCostValue = INT_MAX;
        constexpr size_t alphabetStart = 'a';
        constexpr size_t alphabetSize = 26;
        std::vector<std::vector<size_t>> letters(alphabetSize);
        std::vector<size_t> currentPositions(ring.size(), absentCostValue);
        // init
        for (size_t index = 0; index < ring.size(); ++index)
            letters[ring[index] - alphabetStart].emplace_back(index);
        for (size_t position : letters[key[0] - alphabetStart])
            currentPositions[position] = 1 + std::min(position, ring.size() - position);
        // move
        for (size_t index = 1; index < key.size(); ++index)
        {
            std::vector<size_t> nextPositions(ring.size(), absentCostValue);
            for (size_t currentPosition = 0; currentPosition < currentPositions.size(); ++currentPosition)
            {
                if (currentPositions[currentPosition] == absentCostValue)
                    continue;
                for (size_t nextPosition : letters[key[index] - alphabetStart])
                {
                    const size_t moves1 = std::max(nextPosition, currentPosition) - std::min(nextPosition, currentPosition);
                    const size_t moves2 = currentPositions.size() - moves1;
                    size_t nextPositionCost = currentPositions[currentPosition] + 1 + std::min(moves1, moves2);
                    nextPositions[nextPosition] = std::min(nextPositions[nextPosition], nextPositionCost);
                }
            }
            std::swap(currentPositions, nextPositions);
        }
        return static_cast<int>(*std::ranges::min_element(currentPositions));
    }
};

}

namespace FreedomTrailTask
{

TEST(FreedomTrailTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.findRotateSteps("godding", "gd"));
    ASSERT_EQ(13, solution.findRotateSteps("godding", "godding"));
}

}
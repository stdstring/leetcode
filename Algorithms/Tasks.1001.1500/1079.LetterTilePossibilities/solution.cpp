#include <string>
#include <unordered_set>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int numTilePossibilities(std::string const &tiles) const
    {
        std::unordered_set<std::string> sequences;
        std::string current;
        createPossibleSequences(tiles, sequences, current, 0);
        return static_cast<int>(sequences.size());
    }

private:
    void createPossibleSequences(std::string const &tiles, std::unordered_set<std::string> &sequences, std::string &current, size_t usedMask) const
    {
        for (size_t index = 0; index < tiles.size(); ++index)
        {
            const size_t mask = 1LL << index;
            if ((usedMask & mask) != 0)
                continue;
            current.push_back(tiles[index]);
            sequences.insert(current);
            if (current.size() == tiles.size())
            {
                current.pop_back();
                return;
            }
            createPossibleSequences(tiles, sequences, current, usedMask | mask);
            current.pop_back();
        }
    }
};

}

namespace LetterTilePossibilitiesTask
{

TEST(LetterTilePossibilitiesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(8, solution.numTilePossibilities("AAB"));
    ASSERT_EQ(188, solution.numTilePossibilities("AAABBC"));
    ASSERT_EQ(1, solution.numTilePossibilities("V"));
}

}
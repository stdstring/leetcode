#include <algorithm>
#include <array>
#include <iterator>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::string> wordSubsets(std::vector<std::string> const &words1, std::vector<std::string> const &words2) const
    {
        std::array<size_t, AlphabetSize> representation2{};
        representation2.fill(0);
        for (std::string const &word : words2)
        {
            std::array<size_t, AlphabetSize> representation(createWordRepresentation(word));
            for (size_t index = 0; index < AlphabetSize; ++index)
                representation2[index] = std::max(representation2[index], representation[index]);
        }
        std::vector<std::string> result;
        std::copy_if(words1.cbegin(), words1.cend(), std::back_inserter(result), [this, &representation2](std::string const &word){ return checkRepresentation(createWordRepresentation(word), representation2); });
        return result;
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';

    std::array<size_t, AlphabetSize> createWordRepresentation(std::string const &word) const
    {
        std::array<size_t, AlphabetSize> representation{};
        representation.fill(0);
        for (char ch : word)
            ++representation[ch - AlphabetStart];
        return representation;
    }

    bool checkRepresentation(std::array<size_t, AlphabetSize> const &representation, std::array<size_t, AlphabetSize> const &universalRepresentation) const
    {
        for (size_t index = 0; index < AlphabetSize; ++index)
        {
            if (representation[index] < universalRepresentation[index])
                return false;
        }
        return true;
    }
};

}

namespace WordSubsetsTask
{

TEST(WordSubsetsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"facebook", "google", "leetcode"}), solution.wordSubsets({"amazon", "apple", "facebook", "google", "leetcode"}, {"e", "o"}));
    ASSERT_EQ(std::vector<std::string>({"apple", "google", "leetcode"}), solution.wordSubsets({"amazon", "apple", "facebook", "google", "leetcode"}, {"l", "e"}));
    ASSERT_EQ(std::vector<std::string>({"facebook", "google"}), solution.wordSubsets({"amazon", "apple", "facebook", "google", "leetcode"}, {"e", "oo"}));
    ASSERT_EQ(std::vector<std::string>({"google", "leetcode"}), solution.wordSubsets({"amazon", "apple", "facebook", "google", "leetcode"}, {"lo", "eo"}));
    ASSERT_EQ(std::vector<std::string>({"facebook", "leetcode"}), solution.wordSubsets({"amazon", "apple", "facebook", "google", "leetcode"}, {"ec", "oc", "ceo"}));
}

}
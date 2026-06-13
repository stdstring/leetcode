#include <numeric>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string mapWordWeights(std::vector<std::string> const &words, std::vector<int> const &weights) const
    {
        std::string result(words.size(), '=');
        for (size_t index = 0; index < words.size(); ++index)
            result[index] = calcWordResult(words[index], weights);
        return result;
    }

private:
    [[nodiscard]] char calcWordResult(std::string const &word, std::vector<int> const &weights) const
    {
        constexpr int alphabetStart = 'a';
        constexpr int alphabetSize = 26;
        auto accFun = [&weights, alphabetStart](int acc, char ch) { return acc + weights[ch - alphabetStart]; };
        int totalWeight = std::accumulate(word.cbegin(), word.cend(), 0, accFun);
        totalWeight %= alphabetSize;
        return static_cast<char>('z' - totalWeight);
    }
};

}

namespace WeightedWordMappingTask
{

TEST(WeightedWordMappingTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("rij", solution.mapWordWeights({"abcd", "def", "xyz"},
                                             {5, 3, 12, 14, 1, 2, 3, 2, 10, 6, 6, 9, 7, 8, 7, 10, 8, 9, 6, 9, 9, 8, 3, 7, 7, 2}));
    ASSERT_EQ("yyy", solution.mapWordWeights({"a", "b", "c"},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    ASSERT_EQ("g", solution.mapWordWeights({"abcd"},
                                           {7, 5, 3, 4, 3, 5, 4, 9, 4, 2, 2, 7, 10, 2, 5, 10, 6, 1, 2, 2, 4, 1, 3, 4, 4, 5}));
}

}
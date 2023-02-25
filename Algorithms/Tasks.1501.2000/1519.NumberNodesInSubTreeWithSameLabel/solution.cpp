#include <array>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> countSubTrees(int n, std::vector<std::vector<int>> const &edges, std::string const &labels) const
    {
        std::vector<std::vector<int>> neighbors(n, std::vector<int>());
        for (std::vector<int> const &edge : edges)
        {
            neighbors[edge[0]].push_back(edge[1]);
            neighbors[edge[1]].push_back(edge[0]);
        }
        std::vector<int> result(n, 0);
        processNode(neighbors, 0, labels, result);
        return result;
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';

    std::array<size_t, AlphabetSize> processNode(std::vector<std::vector<int>> const &neighbors, size_t current, std::string const &labels, std::vector<int> &result) const
    {
        std::array<size_t, AlphabetSize> lettersData{};
        lettersData.fill(0);
        result[current] = 1;
        for (int neighbor : neighbors[current])
        {
            if (result[neighbor] == 0)
                mergeLetterData(processNode(neighbors, neighbor, labels, result), lettersData);
        }
        result[current] += static_cast<int>(lettersData[labels[current] - AlphabetStart]);
        ++lettersData[labels[current] - AlphabetStart];
        return lettersData;
    }

    void mergeLetterData(std::array<size_t, AlphabetSize> const &source, std::array<size_t, AlphabetSize> &dest) const
    {
        for (size_t index = 0; index < AlphabetSize; ++index)
            dest[index] += source[index];
    }
};

}

namespace NumberNodesInSubTreeWithSameLabelTask
{

TEST(NumberNodesInSubTreeWithSameLabelTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({2, 1, 1, 1, 1, 1, 1}), solution.countSubTrees(7, {{0, 1}, {0, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6}}, "abaedcd"));
    ASSERT_EQ(std::vector<int>({4, 2, 1, 1}), solution.countSubTrees(4, {{0, 1}, {1, 2}, {0, 3}}, "bbbb"));
    ASSERT_EQ(std::vector<int>({3, 2, 1, 1, 1}), solution.countSubTrees(5, {{0, 1}, {0, 2}, {1, 3}, {0, 4}}, "aabab"));
    ASSERT_EQ(std::vector<int>({1, 2, 1, 1, 2, 1}), solution.countSubTrees(6, {{0, 1}, {0, 2}, {1, 3}, {3, 4}, {4, 5}}, "cbabaa"));
    ASSERT_EQ(std::vector<int>({6, 5, 4, 1, 3, 2, 1}), solution.countSubTrees(7, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}}, "aaabaaa"));
}

TEST(NumberNodesInSubTreeWithSameLabelTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 1, 2, 1}), solution.countSubTrees(4, {{0, 2}, {0, 3}, {1, 2}}, "aeed"));
}

}
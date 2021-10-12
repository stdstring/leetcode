#include <queue>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct Node
{
    Node(size_t index, size_t mutationCount) : Index(index), MutationCount(mutationCount)
    {
    }

    size_t Index;
    size_t MutationCount;
};

class Solution
{
public:
    [[nodiscard]] int minMutation(std::string const &start, std::string const &end, std::vector<std::string> const &bank) const
    {
        if (start == end)
            return 0;
        std::vector<uint8_t> usedBank(bank.size(), 0);
        std::queue<Node> bankQueue;
        processGene(start, 0, bank, bankQueue, usedBank);
        while (!bankQueue.empty())
        {
            if (bank[bankQueue.front().Index] == end)
                return static_cast<int>(bankQueue.front().MutationCount);
            processGene(bank[bankQueue.front().Index], bankQueue.front().MutationCount, bank, bankQueue, usedBank);
            bankQueue.pop();
        }
        return -1;
    }

private:
    bool canMutate(std::string const &source, std::string const &dest) const
    {
        bool hasMutation = false;
        for (size_t index = 0; index < source.size(); ++index)
        {
            if (source[index] != dest[index])
            {
                if (hasMutation)
                    return false;
                hasMutation = true;
            }
        }
        return hasMutation;
    }

    void processGene(std::string const &current, size_t currentCount, std::vector<std::string> const &bank, std::queue<Node> &bankQueue, std::vector<uint8_t> &usedBank) const
    {
        for (size_t index = 0; index < bank.size(); ++index)
        {
            if (usedBank[index])
                continue;
            if (canMutate(current, bank[index]))
            {
                usedBank[index] = 1;
                bankQueue.emplace(index, currentCount + 1);
            }
        }
    }
};

}

namespace MinimumGeneticMutationTask
{

TEST(MinimumGeneticMutationTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.minMutation("AACCGGTT", "AACCGGTA", {"AACCGGTA"}));
    ASSERT_EQ(2, solution.minMutation("AACCGGTT", "AAACGGTA", {"AACCGGTA", "AACCGCTA", "AAACGGTA"}));
    ASSERT_EQ(3, solution.minMutation("AAAAACCC", "AACCCCCC", {"AAAACCCC", "AAACCCCC", "AACCCCCC"}));
}

TEST(MinimumGeneticMutationTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(-1, solution.minMutation("AACCGGTT", "AACCGGTA", {}));
}

}
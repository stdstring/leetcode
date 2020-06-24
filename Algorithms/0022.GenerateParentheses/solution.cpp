#include <string>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::string> generateParenthesis(int n) const
    {
        std::vector<std::vector<std::string>> storage;
        storage.push_back({"()"});
        for (int count = 2; count <= n; ++count)
        {
            std::vector<std::string> parentheses;
            // add outer parentheses for all combinations generated on previous step
            for (std::string const &combination : storage.back())
                parentheses.push_back("(" + combination + ")");
            std::unordered_set<std::string> gs;
            // combine all possible cases of previously generated combinations
            for (int smallCount = 1; smallCount <= count/2; ++smallCount)
                generatePairs(storage, parentheses, gs, smallCount, count - smallCount);
            storage.push_back(parentheses);
        }
        return storage.back();
    }

private:
    void generatePairs(std::vector<std::vector<std::string>> const &storage, std::vector<std::string> &parentheses, std::unordered_set<std::string> &parenthesesSet, int smallCount, int bigCount) const
    {
        for (size_t smallIndex = 0; smallIndex < storage[smallCount - 1].size(); ++smallIndex)
        {
            for (size_t bigIndex = 0; bigIndex < storage[bigCount - 1].size(); ++bigIndex)
            {
                if (smallCount == bigCount && smallIndex == bigIndex)
                    addCombination(parentheses, parenthesesSet, storage[smallCount - 1][smallIndex] + storage[bigCount - 1][bigIndex]);
                else
                {
                    addCombination(parentheses, parenthesesSet, storage[smallCount - 1][smallIndex] + storage[bigCount - 1][bigIndex]);
                    addCombination(parentheses, parenthesesSet, storage[bigCount - 1][bigIndex] + storage[smallCount - 1][smallIndex]);
                }
            }
        }
    }

    void addCombination(std::vector<std::string> &parentheses, std::unordered_set<std::string> &parenthesesSet, std::string const &combination) const
    {
        if (parenthesesSet.count(combination) != 0)
            return;
        parentheses.push_back(combination);
        parenthesesSet.insert(combination);
    }
};

}

namespace GenerateParenthesesTask
{

TEST(GenerateParenthesesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"((()))", "(()())", "()(())", "(())()", "()()()"}), solution.generateParenthesis(3));
}

TEST(GenerateParenthesesTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"(((())))", "((()()))", "(()(()))", "((())())", "(()()())", "()((()))", "((()))()", "()(()())", "(()())()", "()()(())", "()(())()", "(())()()", "()()()()", "(())(())"}), solution.generateParenthesis(4));
}

}
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::string> printVertically(std::string const &s) const
    {
        std::vector<std::string> words;
        size_t currentPos = 0;
        size_t maxSize = 0;
        while (currentPos < s.size())
        {
            size_t spacePos = s.find(' ', currentPos);
            if (spacePos == std::string::npos)
                spacePos = s.size();
            words.push_back(s.substr(currentPos, spacePos - currentPos));
            maxSize = std::max(maxSize, words.back().size());
            currentPos = spacePos + 1;
        }
        std::vector<std::string> result(maxSize, "");
        for (std::string const &word : words)
        {
            for (size_t index = 0; index < maxSize; ++index)
                result[index].push_back(index >= word.size() ? ' ' : word[index]);
        }
        for (std::string &resultStr : result)
        {
            while (resultStr.back() == ' ')
                resultStr.pop_back();
        }
        return result;
    }
};

}

namespace PrintWordsVerticallyTask
{

TEST(PrintWordsVerticallyTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"HAY", "ORO", "WEU"}), solution.printVertically("HOW ARE YOU"));
    ASSERT_EQ(std::vector<std::string>({"TBONTB", "OEROOE", "   T"}), solution.printVertically("TO BE OR NOT TO BE"));
    ASSERT_EQ(std::vector<std::string>({"CIC", "OSO", "N M", "T I", "E N", "S G", "T"}), solution.printVertically("CONTEST IS COMING"));
}

}
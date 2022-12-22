#include <map>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string largestWordCount(std::vector<std::string> const &messages, std::vector<std::string> const &senders) const
    {
        std::map<std::string, size_t> senderWordsMap;
        for (size_t index = 0; index < messages.size(); ++index)
            senderWordsMap[senders[index]] += calcWordCount(messages[index]);
        std::string bestSender;
        size_t bestWordsCount = 0;
        for (auto const &[sender, wordsCount] : senderWordsMap)
        {
            if (wordsCount >= bestWordsCount)
            {
                bestWordsCount = wordsCount;
                bestSender = sender;
            }
        }
        return bestSender;
    }

private:
    [[nodiscard]] size_t calcWordCount(std::string const &message) const
    {
        return 1 + std::count(message.cbegin(), message.cend(), ' ');
    }
};

}

namespace SenderWithLargestWordCountTask
{

TEST(SenderWithLargestWordCountTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("Alice", solution.largestWordCount({"Hello userTwooo", "Hi userThree", "Wonderful day Alice", "Nice day userThree"},
                                                 {"Alice", "userTwo", "userThree", "Alice"}));
    ASSERT_EQ("Charlie", solution.largestWordCount({"How is leetcode for everyone", "Leetcode is useful for practice"}, {"Bob", "Charlie"}));
}

}
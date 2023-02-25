#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> findOcurrences(std::string const &text, std::string const &first, std::string const &second) const
    {
        std::vector<std::string> result;
        for (size_t start = 0; start < text.size();)
        {
            const size_t firstStart = start;
            const size_t firstEnd = text.find(' ', firstStart);
            if (firstEnd == std::string::npos)
                break;
            start = firstEnd + 1;
            if (!compareWords(text, firstStart, firstEnd - firstStart, first))
                continue;
            const size_t secondStart = firstEnd + 1;
            const size_t secondEnd = text.find(' ', secondStart);
            if (secondEnd == std::string::npos)
                break;
            if (!compareWords(text, secondStart, secondEnd - secondStart, second))
                continue;
            const size_t thirdStart = secondEnd + 1;
            const size_t thirdEnd = text.find(' ', thirdStart);
            result.push_back(text.substr(thirdStart, (thirdEnd == std::string::npos ? text.size() : thirdEnd) - thirdStart));
            if (thirdEnd == std::string::npos)
                break;
        }
        return result;
    }

private:
    [[nodiscard]] bool compareWords(std::string const &text, size_t start, size_t size, std::string const &word) const
    {
        if (word.size() != size)
            return false;
        for (size_t index = 0; index < size; ++index)
        {
            if (word[index] != text[start + index])
                return false;
        }
        return true;
    }
};

}

namespace OccurrencesAfterBigramTask
{

TEST(OccurrencesAfterBigramTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"girl", "student"}), solution.findOcurrences("alice is a good girl she is a good student", "a", "good"));
    ASSERT_EQ(std::vector<std::string>({"we", "rock"}), solution.findOcurrences("we will we will rock you", "we", "will"));
}

}
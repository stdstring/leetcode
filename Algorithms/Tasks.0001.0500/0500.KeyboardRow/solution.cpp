#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::string> findWords(std::vector<std::string> const &words) const
    {
        const int firstRow = createRepresentation(_firstRow);
        const int secondRow = createRepresentation(_secondRow);
        const int thirdRow = createRepresentation(_thirdRow);
        std::vector<std::string> dest;
        for (std::string const &word : words)
        {
            if (checkWord(word, firstRow))
                dest.push_back(word);
            if (checkWord(word, secondRow))
                dest.push_back(word);
            if (checkWord(word, thirdRow))
                dest.push_back(word);
        }
        return dest;
    }

private:
    int createRepresentation(std::string const &word) const
    {
        int result = 0;
        for (char ch : word)
            result |= (1 << (ch - 'a'));
        return result;
    }

    bool checkWord(std::string const &word, int row) const
    {
        for (char ch : word)
        {
            if ((row & (1 << (tolower(ch) - 'a'))) == 0)
                return false;
        }
        return true;
    }

    const std::string _firstRow = "qwertyuiop";
    const std::string _secondRow = "asdfghjkl";
    const std::string _thirdRow = "zxcvbnm";
};

}

namespace KeyboardRowTask
{

TEST(KeyboardRowTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"Alaska", "Dad"}), solution.findWords({"Hello", "Alaska", "Dad", "Peace"}));
}

TEST(KeyboardRowTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"a", "b"}), solution.findWords({"a", "b"}));
}

}
#include <cctype>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool detectCapitalUse(std::string const &word) const
    {
        if (word.size() == 1)
            return true;
        if (islower(word[0]) && isupper(word[1]))
            return false;
        const bool expectUpperLetters = isupper(word[1]);
        for (size_t index = 2; index < word.size(); ++index)
        {
            if (static_cast<bool>(isupper(word[index])) != expectUpperLetters)
                return false;
        }
        return true;
    }
};

}

namespace DetectCapitalTask
{

TEST(DetectCapitalTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.detectCapitalUse("USA"));
    ASSERT_EQ(false, solution.detectCapitalUse("FlaG"));
}

}
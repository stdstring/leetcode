#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isAnagram(std::string const &s, std::string const &t) const
    {
        if (s.length() != t.length())
            return false;
        const int alphabetSize = 26;
        std::array<size_t, alphabetSize> letters{};
        // fill
        letters.fill(0);
        for (char ch : s)
            letters[ch - 'a'] += 1;
        // check
        for (char ch : t)
        {
            if (letters[ch - 'a'] == 0)
                return false;
            letters[ch - 'a'] -= 1;
        }
        return true;
    }
};

}

namespace ValidAnagramTask
{

TEST(ValidAnagramTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isAnagram("anagram", "nagaram"));
    ASSERT_EQ(false, solution.isAnagram("rat", "car"));
}

}

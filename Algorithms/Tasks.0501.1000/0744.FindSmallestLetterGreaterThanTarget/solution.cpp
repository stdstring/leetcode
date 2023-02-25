#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    char nextGreatestLetter(std::vector<char> const &letters, char target) const
    {
        if ((target < letters.front()) || (target >= letters.back()))
            return letters.front();
        char letter = letters.back();
        size_t left = 0;
        size_t right = letters.size() - 1;
        while (left <= right)
        {
            const size_t middle = (left + right) / 2;
            if (letters[middle] <= target)
                left = middle + 1;
            else
            {
                letter = letters[middle];
                right = middle - 1;
            }
        }
        return letter;
    }
};

}

namespace FindSmallestLetterGreaterThanTargetTask
{

TEST(FindSmallestLetterGreaterThanTargetTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ('c', solution.nextGreatestLetter({'c', 'f', 'j'}, 'a'));
    ASSERT_EQ('f', solution.nextGreatestLetter({'c', 'f', 'j'}, 'c'));
    ASSERT_EQ('f', solution.nextGreatestLetter({'c', 'f', 'j'}, 'd'));
    ASSERT_EQ('j', solution.nextGreatestLetter({'c', 'f', 'j'}, 'g'));
    ASSERT_EQ('c', solution.nextGreatestLetter({'c', 'f', 'j'}, 'j'));
    ASSERT_EQ('c', solution.nextGreatestLetter({'c', 'f', 'j'}, 'k'));
}

}
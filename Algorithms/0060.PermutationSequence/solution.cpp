#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string getPermutation(int n, int k) const
    {
        std::string result;
        int lexNumberSup = 1;
        std::string alphabet;
        for (int number = 1; number <= n; ++number)
        {
            lexNumberSup *= number;
            alphabet.push_back('0' + number);
        }
        int lexNumber = k - 1;
        while (!alphabet.empty())
        {
            lexNumberSup /= static_cast<int>(alphabet.size());
            const int index = lexNumber / lexNumberSup;
            result.push_back(alphabet[index]);
            alphabet.erase(index, 1);
            lexNumber %= lexNumberSup;
        }
        return result;
    }
};

}

namespace PermutationSequenceTask
{

TEST(PermutationSequenceTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("213", solution.getPermutation(3, 3));
    ASSERT_EQ("2314", solution.getPermutation(4, 9));
}

}
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int countVowelPermutation(int n) const
    {
        const int modValue = 1000000007;
        const int vowelsCount = 5;
        const int vowelA = 0;
        const int vowelE = 1;
        const int vowelI = 2;
        const int vowelO = 3;
        const int vowelU = 4;
        std::vector<int> countData(vowelsCount, 1);
        for (int size = 1; size < n; ++size)
        {
            int vowelACount = 0;
            int vowelECount = 0;
            int vowelICount = 0;
            int vowelOCount = 0;
            int vowelUCount = 0;
            // Each vowel 'a' may only be followed by an 'e'.
            vowelECount = (vowelECount + countData[vowelA]) % modValue;
            // Each vowel 'e' may only be followed by an 'a' or an 'i'.
            vowelACount = (vowelACount + countData[vowelE]) % modValue;
            vowelICount = (vowelICount + countData[vowelE]) % modValue;
            // Each vowel 'i' may not be followed by another 'i'.
            vowelACount = (vowelACount + countData[vowelI]) % modValue;
            vowelECount = (vowelECount + countData[vowelI]) % modValue;
            vowelOCount = (vowelOCount + countData[vowelI]) % modValue;
            vowelUCount = (vowelUCount + countData[vowelI]) % modValue;
            // Each vowel 'o' may only be followed by an 'i' or a 'u'.
            vowelICount = (vowelICount + countData[vowelO]) % modValue;
            vowelUCount = (vowelUCount + countData[vowelO]) % modValue;
            // Each vowel 'u' may only be followed by an 'a'.
            vowelACount = (vowelACount + countData[vowelU]) % modValue;
            countData[vowelA] = vowelACount;
            countData[vowelE] = vowelECount;
            countData[vowelI] = vowelICount;
            countData[vowelO] = vowelOCount;
            countData[vowelU] = vowelUCount;
        }
        int result = 0;
        for (int count : countData)
            result = (result + count) % modValue;
        return result;
    }
};

}

namespace CountVowelsPermutationTask
{

TEST(CountVowelsPermutationTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(5, solution.countVowelPermutation(1));
    ASSERT_EQ(10, solution.countVowelPermutation(2));
    ASSERT_EQ(68, solution.countVowelPermutation(5));
}

TEST(CountVowelsPermutationTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(18208803, solution.countVowelPermutation(144));
}

}
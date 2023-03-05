#include <array>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countAnagrams(std::string const &s) const
    {
        constexpr int64_t modValue = 1000000007;
        int64_t result = 1;
        std::vector<int64_t> factorialMemo({1});
        int currentWordSize = 0;
        std::array<int, AlphabetSize> lettersData{};
        lettersData.fill(0);
        for (const char ch : s)
        {
            if (ch == ' ')
            {
                result = (result * calcWordAnagramsCount(currentWordSize, lettersData, modValue, factorialMemo)) % modValue;
                currentWordSize = 0;
                lettersData.fill(0);
            }
            else
            {
                ++currentWordSize;
                ++lettersData[ch - AlphabetStart];
            }
        }
        if (currentWordSize > 0)
            result = (result * calcWordAnagramsCount(currentWordSize, lettersData, modValue, factorialMemo)) % modValue;
        return static_cast<int>(result);
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';

    [[nodiscard]] int64_t calcInverseValue(int64_t value, int64_t modValue) const
    {
        // Extended Euclidean algorithm
        int64_t t = 0;
        int64_t r = modValue;
        int64_t newt = 1;
        int64_t newr = value;
        while (newr > 0)
        {
            const int64_t quotient = r / newr;
            const int64_t nextNewT = t - quotient * newt;
            t = newt;
            newt = nextNewT;
            const int64_t nextNewR = r - quotient * newr;
            r = newr;
            newr = nextNewR;
        }
        if (t < 0)
            t = t + modValue;
        return t;
    }

    int64_t calcFactorialWithMemo(int n, int64_t modValue, std::vector<int64_t> &factorialMemo) const
    {
        int knownN = static_cast<int>(factorialMemo.size());
        if (n <= knownN)
            return factorialMemo[n - 1];
        while (knownN < n)
        {
            ++knownN;
            factorialMemo.emplace_back((factorialMemo.back() * knownN) % modValue);
        }
        return factorialMemo.back();
    }

    int64_t calcWordAnagramsCount(int wordSize, std::array<int, AlphabetSize> const &lettersData, int64_t modValue, std::vector<int64_t> &factorialMemo) const
    {
        int64_t anagramsCount = calcFactorialWithMemo(wordSize, modValue, factorialMemo);
        for (const int letterCount : lettersData)
        {
            if (letterCount > 1)
            {
                const int64_t letterCountFactorial = calcFactorialWithMemo(letterCount, modValue, factorialMemo);
                anagramsCount = (anagramsCount * calcInverseValue(letterCountFactorial, modValue)) % modValue;
            }
        }
        return anagramsCount;
    }
};

}

namespace CountAnagramsTask
{

TEST(CountAnagramsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(18, solution.countAnagrams("too hot"));
    ASSERT_EQ(1, solution.countAnagrams("aa"));
}

TEST(CountAnagramsTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(3360, solution.countAnagrams("abbdeeeh"));
    ASSERT_EQ(6, solution.countAnagrams("aabb"));
    ASSERT_EQ(20160, solution.countAnagrams("abbdeeeh aabb"));
}

}
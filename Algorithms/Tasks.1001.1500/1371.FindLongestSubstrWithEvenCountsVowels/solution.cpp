#include <string>
#include <unordered_map>
#include <utility>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findTheLongestSubstring(std::string const &s) const
    {
        constexpr int aMask = 1 << 0;
        constexpr int eMask = 1 << 1;
        constexpr int iMask = 1 << 2;
        constexpr int oMask = 1 << 3;
        constexpr int uMask = 1 << 4;
        std::unordered_map<int, std::pair<size_t, size_t>> stateMap;
        stateMap.emplace(0, std::pair<size_t, size_t>(0, std::string::npos));
        // count of all vowel is even initially
        int state = 0;
        for (size_t index = 0; index < s.size(); ++index)
        {
            switch (s[index])
            {
            case 'a':
            {
                const int currentAState = state & aMask;
                state = (currentAState == 0) ? state | aMask : state & ~aMask;
                break;
            }
            case 'e':
            {
                const int currentEState = state & eMask;
                state = (currentEState == 0) ? state | eMask : state & ~eMask;
                break;
            }
            case 'i':
            {
                const int currentIState = state & iMask;
                state = (currentIState == 0) ? state | iMask : state & ~iMask;
                break;
            }
            case 'o':
            {
                const int currentOState = state & oMask;
                state = (currentOState == 0) ? state | oMask : state & ~oMask;
                break;
            }
            case 'u':
            {
                const int currentUState = state & uMask;
                state = (currentUState == 0) ? state | uMask : state & ~uMask;
                break;
            }
            default:
                break;
            }
            auto iterator = stateMap.find(state);
            if (iterator == stateMap.cend())
                stateMap.emplace(state, std::pair<size_t, size_t>(index + 1, std::string::npos));
            else
                iterator->second.second = index + 1;
        }
        size_t result = 0;
        for (auto const &[_, indices] : stateMap)
        {
            if (indices.second != std::string::npos)
                result = std::max(result, indices.second - indices.first);
        }
        return static_cast<int>(result);
    }
};

}

namespace FindLongestSubstrWithEvenCountsVowelsTask
{

TEST(FindLongestSubstrWithEvenCountsVowelsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(13, solution.findTheLongestSubstring("eleetminicoworoep"));
    ASSERT_EQ(5, solution.findTheLongestSubstring("leetcodeisgreat"));
    ASSERT_EQ(6, solution.findTheLongestSubstring("bcbcbc"));
}

TEST(FindLongestSubstrWithEvenCountsVowelsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(8, solution.findTheLongestSubstring("amntyyaw"));
}

}
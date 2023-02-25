#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> removeAnagrams(std::vector<std::string> const &words) const
    {
        std::vector<std::string> dest;
        std::string lastKey;
        for (std::string const &word : words)
        {
            std::string key(word);
            std::sort(key.begin(), key.end());
            if (key != lastKey)
            {
                dest.push_back(word);
                std::swap(lastKey, key);
            }
        }
        return dest;
    }
};

}

namespace FindResultArrayAfterRemovingAnagramsTask
{

TEST(FindResultArrayAfterRemovingAnagramsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"abba", "cd"}), solution.removeAnagrams({"abba", "baba", "bbaa", "cd", "cd"}));
    ASSERT_EQ(std::vector<std::string>({"a", "b", "c", "d", "e"}), solution.removeAnagrams({"a", "b", "c", "d", "e"}));
}

}
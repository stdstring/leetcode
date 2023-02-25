#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string> const &strs) const
    {
        std::vector<std::vector<std::string>> dest;
        std::unordered_map<std::string, size_t> keyIndexMap;
        for(std::string const &value: strs)
        {
            std::string key(value);
            std::sort(key.begin(), key.end());
            std::unordered_map<std::string, size_t>::iterator iterator = keyIndexMap.find(key);
            if (iterator == keyIndexMap.end())
            {
                keyIndexMap.emplace(key, dest.size());
                dest.push_back(std::vector<std::string>({value}));
            }
            else
                dest[iterator->second].push_back(value);
        }
        return dest;
    }
};

}

namespace GroupAnagramsTask
{

TEST(GroupAnagramsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<std::string>>({{"eat", "tea", "ate"}, {"tan", "nat"}, {"bat"}}), solution.groupAnagrams({"eat", "tea", "tan", "ate", "nat", "bat"}));
}

TEST(GroupAnagramsTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<std::string>>({{""}, {"b"}}), solution.groupAnagrams({"", "b"}));
}

}
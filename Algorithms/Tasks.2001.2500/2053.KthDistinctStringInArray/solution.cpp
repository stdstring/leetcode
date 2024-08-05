#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string kthDistinct(std::vector<std::string> const &arr, int k) const
    {
        std::unordered_map<std::string, bool> uniqueMap;
        for (std::string const &str : arr)
        {
            auto iterator = uniqueMap.find(str);
            if (iterator == uniqueMap.cend())
                uniqueMap.emplace(str, true);
            else
                iterator->second = false;
        }
        std::vector<std::string> data;
        data.reserve(arr.size());
        for (std::string const &str : arr)
        {
            if (uniqueMap[str])
                data.emplace_back(str);
        }
        const size_t selectedString = k - 1;
        return selectedString < data.size() ? data[selectedString] : "";
    }
};

}

namespace KthDistinctStringInArrayTask
{

TEST(KthDistinctStringInArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("a", solution.kthDistinct({"d", "b", "c", "b", "c", "a"}, 2));
    ASSERT_EQ("aaa", solution.kthDistinct({"aaa", "aa", "a"}, 1));
    ASSERT_EQ("", solution.kthDistinct({"a", "b", "a"}, 3));
}

}
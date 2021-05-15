#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string findReplaceString(std::string const &s, std::vector<int> const &indexes, std::vector<std::string> const &sources, std::vector<std::string> const &targets) const
    {
        std::vector<size_t> partIndices;
        for (size_t index = 0; index < indexes.size(); ++index)
            partIndices.push_back(index);
        std::sort(partIndices.begin(), partIndices.end(), [&indexes](size_t i1, size_t i2){ return indexes[i1] < indexes[i2]; });
        std::string target;
        size_t partIndex = 0;
        for (size_t sourceIndex = 0; sourceIndex < s.size();)
        {
            if ((partIndex < partIndices.size()) && (sourceIndex == static_cast<size_t>(indexes[partIndices[partIndex]])))
            {
                if (s.compare(sourceIndex, sources[partIndices[partIndex]].size(), sources[partIndices[partIndex]]) == 0)
                {
                    target.append(targets[partIndices[partIndex]]);
                    sourceIndex += sources[partIndices[partIndex]].size();
                }
                else
                    target.push_back(s[sourceIndex++]);
                ++partIndex;
            }
            else
                target.push_back(s[sourceIndex++]);
        }
        return target;
    }
};

}

namespace FindAndReplaceInStringTask
{

TEST(FindAndReplaceInStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("eeebffff", solution.findReplaceString("abcd", {0, 2}, {"a", "cd"}, {"eee", "ffff"}));
    ASSERT_EQ("eeecd", solution.findReplaceString("abcd", {0, 2}, {"ab", "ec"}, {"eee", "ffff"}));
}

}
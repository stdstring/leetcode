#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numSimilarGroups(std::vector<std::string> const &strs) const
    {
        std::vector<GroupData> groupsData;
        groupsData.reserve(strs.size());
        for (size_t index = 0; index < strs.size(); ++index)
            groupsData.emplace_back();
        for (size_t index1 = 0; index1 < groupsData.size(); ++index1)
        {
            for (size_t index2 = index1 + 1; index2 < groupsData.size(); ++index2)
            {
                if (!isSimiliar(strs[index1], strs[index2]))
                    continue;
                const size_t root1 = getRoot(groupsData, index1);
                const size_t root2 = getRoot(groupsData, index2);
                if (root1 != root2)
                    mergeGroups(groupsData, root1, root2);
            }
        }
        size_t groupCount = 0;
        for (GroupData const &group : groupsData)
        {
            if (group.Root == -1)
                ++groupCount;
        }
        return static_cast<int>(groupCount);
    }

private:
    struct GroupData
    {
        GroupData() : Root(-1), GroupSize(1)
        {
        }
        int Root;
        size_t GroupSize;
    };

    [[nodiscard]] bool isSimiliar(std::string const &str1, std::string const &str2) const
    {
        std::vector<size_t> differentCharPos;
        for (size_t index = 0; index < str1.size(); ++index)
        {
            if (str1[index] != str2[index])
                differentCharPos.emplace_back(index);
            if (differentCharPos.size() > 2)
                return false;
        }
        return differentCharPos.empty() ||
               ((differentCharPos.size() == 2) && (str1[differentCharPos[0]] == str2[differentCharPos[1]]) && (str1[differentCharPos[1]] == str2[differentCharPos[0]]));
    }

    [[nodiscard]] size_t getRoot(std::vector<GroupData> const &groupData, size_t current) const
    {
        while (groupData[current].Root != -1)
            current = groupData[current].Root;
        return current;
    }

    void mergeGroups(std::vector<GroupData> &groupData, size_t root1, size_t root2) const
    {
        if (groupData[root1].GroupSize >= groupData[root2].GroupSize)
        {
            groupData[root2].Root = static_cast<int>(root1);
            groupData[root1].GroupSize += groupData[root2].GroupSize;
        }
        else
        {
            groupData[root1].Root = static_cast<int>(root2);
            groupData[root2].GroupSize += groupData[root1].GroupSize;
        }
    }
};

}

namespace SimilarStringGroupsTask
{

TEST(SimilarStringGroupsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.numSimilarGroups({"tars", "rats", "arts", "star"}));
    ASSERT_EQ(1, solution.numSimilarGroups({"omv", "ovm"}));
}

}
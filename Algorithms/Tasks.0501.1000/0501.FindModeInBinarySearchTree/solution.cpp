#include <algorithm>
#include <unordered_map>
#include <vector>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    std::vector<int> findMode(TreeNode* root) const
    {
        std::unordered_map<int, size_t> storage;
        collectValues(root, storage);
        const auto iterator = std::ranges::max_element(std::as_const(storage), [](auto const &left, auto const &right){ return left.second < right.second; });
        const size_t modeCount = iterator->second;
        std::vector<int> result;
        for (auto const &entry : storage)
        {
            if (entry.second == modeCount)
                result.emplace_back(entry.first);
        }
        std::ranges::sort(result);
        return result;
    }

private:
    void collectValues(TreeNode* root, std::unordered_map<int, size_t> &storage) const
    {
        ++storage[root->val];
        if (root->left)
            collectValues(root->left, storage);
        if (root->right)
            collectValues(root->right, storage);
    }
};

}

using CommonLib::Codec;

namespace FindModeInBinarySearchTreeTask
{

TEST(FindModeInBinarySearchTreeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({2}), solution.findMode(Codec::createTree("[1,null,2,2]").get()));
    ASSERT_EQ(std::vector<int>({0}), solution.findMode(Codec::createTree("[0]").get()));
}

}
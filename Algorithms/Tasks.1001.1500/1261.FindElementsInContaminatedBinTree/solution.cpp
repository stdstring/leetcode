#include <string>
#include <unordered_set>
#include <vector>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class FindElements
{
public:
    FindElements(TreeNode* root)
    {
        root->val = 0;
        _values.insert(0);
        processTree(root, 0);
    }

    bool find(int target) const
    {
        return _values.count(target) == 1;
    }

private:
    std::unordered_set<int> _values;

    void processTree(TreeNode* root, int correctValue)
    {
        processSubtree(root->left, 2 * correctValue + 1);
        processSubtree(root->right, 2 * correctValue + 2);
    }

    void processSubtree(TreeNode* subtreeRoot, int possibleValue)
    {
        if (subtreeRoot != nullptr)
        {
            subtreeRoot->val = possibleValue;
            _values.insert(possibleValue);
            processTree(subtreeRoot, possibleValue);
        }
    }
};

}

using CommonLib::Codec;

namespace
{

void checkFindElements(std::string const &source, std::vector<int> const &targets, std::vector<bool> const &expectedResults)
{
    const FindElements findElements(Codec::createTree(source).get());
    for (size_t index = 0; index < targets.size(); ++index)
        ASSERT_EQ(expectedResults[index], findElements.find(targets[index]));
}

}

namespace FindElementsInContaminatedBinTreeTask
{

TEST(FindElementsInContaminatedBinTreeTaskTests, Examples)
{
    checkFindElements("[-1,null,-1]", {1, 2}, {false, true});
    checkFindElements("[-1,-1,-1,-1,-1]", {1, 3, 5}, {true, true, false});
    checkFindElements("[-1,null,-1,-1,null,-1]", {2, 3, 4, 5}, {true, false, false, true});
}

}

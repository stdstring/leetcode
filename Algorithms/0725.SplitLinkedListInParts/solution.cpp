#include <vector>

#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;

namespace
{

class Solution
{
public:
    std::vector<ListNode*> splitListToParts(ListNode* root, int k)
    {
        std::vector<ListNode*> result;
        const int length = calcLength(root);
        const int partSize = length / k;
        for (int partNumber = 1; partNumber <= length % k; ++partNumber)
            root = cutPart(root, partSize + 1, result);
        for (int partNumber = 1; partNumber <= k - length % k; ++partNumber)
        {
            if (root == nullptr)
                result.push_back(nullptr);
            else
                root = cutPart(root, partSize, result);
        }
        return result;
    }

private:
    int calcLength(ListNode* root)
    {
        int length = 0;
        while (root != nullptr)
        {
            ++length;
            root = root->next;
        }
        return length;
    }

    ListNode* findPartLastNode(ListNode* root, int size)
    {
        ListNode* lastNode = root;
        for (int number = 1; number < size; ++number)
            lastNode = lastNode->next;
        return lastNode;
    }

    ListNode* cutPart(ListNode* root, int partSize, std::vector<ListNode*> &result)
    {
        result.push_back(root);
        ListNode* partLastNode = findPartLastNode(root, partSize);
        root = partLastNode->next;
        partLastNode->next = nullptr;
        return root;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::checkAndDeleteLinkedList;

namespace
{

void checkSplitListToParts(std::vector<int> const &source, int k, std::vector<std::vector<int>> const &expected)
{
    Solution solution;
    std::vector<ListNode*> parts = solution.splitListToParts(createLinkedList(source, false).get(), k);
    ASSERT_EQ(expected.size(), parts.size());
    for (size_t index = 0; index < expected.size(); ++index)
        checkAndDeleteLinkedList(expected[index], parts[index]);
}

}

namespace SplitLinkedListInPartsTask
{

TEST(SplitLinkedListInPartsTaskTests, Examples)
{
    checkSplitListToParts({1, 2, 3}, 5, {{1}, {2}, {3}, {}, {}});
    checkSplitListToParts({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 3, {{1, 2, 3, 4}, {5, 6, 7}, {8, 9, 10}});
}

}
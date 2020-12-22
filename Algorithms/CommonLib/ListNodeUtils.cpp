#include <functional>
#include <memory>
#include <vector>

#include "gtest/gtest.h"

#include "ListNode.h"
#include "ListNodeUtils.h"

namespace
{

}

std::shared_ptr<CommonLib::ListNode> CommonLib::createLinkedList(std::vector<int> const &source, bool withDeleter)
{
    ListNode* current = nullptr;
    for (std::vector<int>::const_reverse_iterator it = source.crbegin(); it != source.crend(); ++it)
        current = new ListNode(*it, current);
    return createLinkedListHolder(current, withDeleter);
}

std::shared_ptr<CommonLib::ListNode> CommonLib::createLinkedListWithCycle(std::vector<int> const &source, size_t cycleStartPos)
{
    ListNode* head = nullptr;
    ListNode* prev = nullptr;
    ListNode* cycleStartNode = nullptr;
    for (size_t index = 0; index < source.size(); ++index)
    {
        ListNode* current = new ListNode(source[index]);
        if (head == nullptr)
            head = current;
        if (prev != nullptr)
            prev->next = current;
        if (index == cycleStartPos)
            cycleStartNode = current;
        prev = current;
    }
    if (prev != nullptr)
        prev->next = cycleStartNode;
    const std::function<void(ListNode*)> deleteFun = [cycleStartNode](ListNode* root)
    {
        if (root == nullptr)
            return;
        bool inCycle = false;
        ListNode* current = root;
        while (!inCycle || (current->next != nullptr && current->next != cycleStartNode))
        {
            if (current == cycleStartNode)
                inCycle = true;
            current = current->next;
        }
        current->next = nullptr;
        deleteLinkedList(root);
    };
    return std::shared_ptr<ListNode>(head, deleteFun);
}

std::vector<int> CommonLib::convertLinkedListToVector(ListNode* current)
{
    std::vector<int> dest;
    while (current != nullptr)
    {
        dest.push_back(current->val);
        current = current->next;
    }
    return dest;
}

void CommonLib::checkAndDeleteLinkedList(std::vector<int> const &expectedValues, ListNode *current)
{
    std::shared_ptr<ListNode> linkedListHolder = createLinkedListHolder(current, true);
    const std::vector<int> actualValues(convertLinkedListToVector(current));
    ASSERT_EQ(expectedValues, actualValues);
    if (expectedValues.empty())
        ASSERT_EQ(nullptr, current);
}
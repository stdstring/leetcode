#include <memory>
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
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) const
    {
        if (headA == nullptr || headB == nullptr)
            return nullptr;
        ListNode* ptr1 = headA;
        ListNode* ptr2 = headB;
        while (ptr1 != ptr2)
        {
            if (ptr1 == nullptr)
                ptr1 = headB;
            else if (ptr2 == nullptr)
                ptr2 = headA;
            else
            {
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
            }
        }
        return ptr1;
    }
};

}

using CommonLib::createLinkedListHolder;

namespace
{

struct ListData
{
    ListData(std::shared_ptr<ListNode> headA, std::shared_ptr<ListNode> headB, ListNode* expectedIntersection) : HeadA(headA), HeadB(headB), ExpectedIntersection(expectedIntersection)
    {
    }

    std::shared_ptr<ListNode> HeadA;
    std::shared_ptr<ListNode> HeadB;
    ListNode* ExpectedIntersection;
};

std::shared_ptr<ListNode> createLinkedList(std::vector<int> const &data, size_t size)
{
    ListNode* root = nullptr;
    ListNode* previous = nullptr;
    for (size_t index = 0; index < size; ++index)
    {
        ListNode* current = new ListNode(data[index]);
        if (root == nullptr)
            root = previous = current;
        else
        {
            previous->next = current;
            previous = current;
        }
    }
    return createLinkedListHolder(root, true);
}

ListNode* findByIndex(ListNode* root, size_t prefixSize)
{
    ListNode* current = root;
    for (size_t index = 0; index < prefixSize; ++index)
        current = current->next;
    return current;
}

ListNode* findLastNode(ListNode* root)
{
    ListNode* current = root;
    while (current->next != nullptr)
        current = current->next;
    return current;
}

ListData generateListData(std::vector<int> const &listA, std::vector<int> const &listB, int intersectVal, size_t skipA, size_t skipB)
{
    const std::shared_ptr<ListNode> headA = createLinkedList(listA, listA.size());
    if (intersectVal == 0)
        return ListData(headA, createLinkedList(listB, listB.size()), nullptr);
    const std::shared_ptr<ListNode> headB = createLinkedList(listB, skipB);
    ListNode* expectedIntersection = findByIndex(headA.get(), skipA);
    return ListData(headA, headB, expectedIntersection);
}

void checkGetIntersectionNode(std::vector<int> const &listA, std::vector<int> const &listB, int intersectVal, size_t skipA, size_t skipB)
{
    const ListData listData(generateListData(listA, listB, intersectVal, skipA, skipB));
    ListNode* lastBNode = findLastNode(listData.HeadB.get());
    if (lastBNode != nullptr)
        lastBNode->next = listData.ExpectedIntersection;
    const Solution solution;
    ASSERT_EQ(listData.ExpectedIntersection, solution.getIntersectionNode(listData.HeadA.get(), listData.HeadB.get()));
    if (lastBNode != nullptr)
        lastBNode->next = nullptr;
}

}

namespace IntersectionOfTwoLinkedListsTask
{

TEST(IntersectionOfTwoLinkedListsTaskTests, Examples)
{
    checkGetIntersectionNode({4, 1, 8, 4, 5}, {5, 6, 1, 8, 4, 5}, 8, 2, 3);
    checkGetIntersectionNode({1, 9, 1, 2, 4}, {3, 2, 4}, 2, 3, 1);
    checkGetIntersectionNode({2, 6, 4}, {1, 5}, 0, 3, 2);
}

}
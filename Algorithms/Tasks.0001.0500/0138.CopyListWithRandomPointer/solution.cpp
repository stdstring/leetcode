#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

#include <ListNodeUtils.h>

#include "gtest/gtest.h"

namespace
{

class Node
{
public:
    Node(int val) : val(val), next(nullptr), random(nullptr)
    {
    }

    int val;
    Node* next;
    Node* random;
};

std::shared_ptr<Node> createLinkedList(std::vector<std::pair<int, int>> const &source, int nullPtrValue)
{
    std::vector<Node*> nodesList;
    nodesList.reserve(source.size());
    for (std::pair<int, int> const &item : source)
        nodesList.push_back(new Node(item.first));
    for (size_t index = 0; index < source.size(); ++index)
    {
        nodesList[index]->next = index == source.size() - 1 ? nullptr : nodesList[index + 1];
        nodesList[index]->random = source[index].second == nullPtrValue ? nullptr : nodesList[source[index].second];
    }
    return nodesList.empty() ? std::shared_ptr<Node>() : CommonLib::createLinkedListHolder(nodesList[0], true);
}

void checkLinkedList(std::vector<std::pair<int, int>> const &source, int nullPtrValue, std::shared_ptr<Node> head)
{
    std::vector<Node*> nodesList;
    Node* current = head.get();
    while (current != nullptr)
    {
        nodesList.push_back(current);
        current = current->next;
    }
    ASSERT_EQ(source.size(), nodesList.size());
    for (size_t index = 0; index < source.size(); ++index)
    {
        ASSERT_EQ(source[index].first, nodesList[index]->val);
        if (source[index].second == nullPtrValue)
            ASSERT_EQ(nullptr, nodesList[index]->random);
        else
            ASSERT_EQ(nodesList[source[index].second], nodesList[index]->random);
    }
}

}

namespace
{

class Solution
{
public:
    Node* copyRandomList(Node* head) const
    {
        std::unordered_map<Node*, Node*> nodeMap;
        Node* cloneHead = nullptr;
        Node* current = head;
        Node* cloneCurrent = nullptr;
        // clone linked list
        while (current != nullptr)
        {
            Node* clone = new Node(current->val);
            if (cloneHead == nullptr)
                cloneHead = clone;
            if (cloneCurrent != nullptr)
                cloneCurrent->next = clone;
            nodeMap.emplace(current, clone);
            cloneCurrent = clone;
            current = current->next;
        }
        // setup random pointers
        current = head;
        cloneCurrent = cloneHead;
        while (current != nullptr)
        {
            if (current->random != nullptr)
                cloneCurrent->random = nodeMap[current->random];
            current = current->next;
            cloneCurrent = cloneCurrent->next;
        }
        return cloneHead;
    }
};

}

namespace
{

void checkCopyRandomList(std::vector<std::pair<int, int>> const &source, int nullPtrValue)
{
    const std::shared_ptr<Node> sourceList = createLinkedList(source, nullPtrValue);
    const Solution solution;
    const std::shared_ptr<Node> cloneList = CommonLib::createLinkedListHolder(solution.copyRandomList(sourceList.get()), true);
    checkLinkedList(source, nullPtrValue, sourceList);
    checkLinkedList(source, nullPtrValue, cloneList);
    if (sourceList == nullptr)
        ASSERT_EQ(nullptr, cloneList.get());
    else
        ASSERT_NE(sourceList.get(), cloneList.get());
}

}

namespace CopyListWithRandomPointerTask
{

TEST(CopyListWithRandomPointerTaskTests, Examples)
{
    checkCopyRandomList({{7, -1}, {13, 0}, {11, 4}, {10, 2}, {1, 0}}, -1);
    checkCopyRandomList({{1, 1}, {2, 1}}, -1);
    checkCopyRandomList({{3, -1},{3, 0},{3, -1}}, -1);
    checkCopyRandomList({}, -1);
}

}
#include <algorithm>
#include <memory>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

#include "Node.h"
#include "NodeUtils.h"

namespace
{

void createNodesListImpl(CommonLib::Node* node, std::vector<CommonLib::Node*> &nodesList, std::unordered_set<CommonLib::Node*> &processedNodes)
{
    if (processedNodes.count(node) == 0)
    {
        nodesList.push_back(node);
        processedNodes.insert(node);
        for (CommonLib::Node* neighbor : node->neighbors)
            createNodesListImpl(neighbor, nodesList, processedNodes);
    }
}

std::vector<CommonLib::Node*> createNodesList(CommonLib::Node* node)
{
    std::vector<CommonLib::Node*> nodesList;
    std::unordered_set<CommonLib::Node*> processedNodes;
    createNodesListImpl(node, nodesList, processedNodes);
    return nodesList;
}

void deleteGraph(CommonLib::Node* node)
{
    if (node == nullptr)
        return;
    std::vector<CommonLib::Node*> nodesList(createNodesList(node));
    for (CommonLib::Node* current : nodesList)
        delete current;
}

}

std::shared_ptr<CommonLib::Node> CommonLib::createGraphHolder(CommonLib::Node* node)
{
    return std::shared_ptr<CommonLib::Node>(node, deleteGraph);
}

std::shared_ptr<CommonLib::Node> CommonLib::createFromAdjacencyList(std::vector<std::vector<int>> const &adjacencyList)
{
    if (adjacencyList.empty())
        return std::shared_ptr<CommonLib::Node>();
    std::vector<CommonLib::Node*> nodesList(adjacencyList.size(), nullptr);
    for (size_t number = 1; number <= adjacencyList.size(); ++number)
        nodesList[number - 1] = new CommonLib::Node(static_cast<int>(number));
    for (size_t number = 1; number <= adjacencyList.size(); ++number)
    {
        for (int toLink : adjacencyList[number - 1])
            nodesList[number - 1]->neighbors.push_back(nodesList[static_cast<size_t>(toLink) - 1]);
    }
    return createGraphHolder(nodesList.front());
}

void CommonLib::checkGraphStructure(std::shared_ptr<CommonLib::Node> const &node, std::vector<std::vector<int>> const &expectedAdjacencyList)
{
    if (expectedAdjacencyList.empty())
    {
        ASSERT_EQ(nullptr, node.get());
        return;
    }
    std::vector<CommonLib::Node*> nodesList(createNodesList(node.get()));
    std::sort(nodesList.begin(), nodesList.end(), [](CommonLib::Node* left, CommonLib::Node* right){ return left->val < right->val; });
    ASSERT_EQ(expectedAdjacencyList.size(), nodesList.size());
    for (size_t index = 0; index < expectedAdjacencyList.size(); ++index)
    {
        ASSERT_EQ(index + 1, nodesList[index]->val);
        ASSERT_EQ(expectedAdjacencyList[index].size(), nodesList[index]->neighbors.size());
        for (size_t linkIndex = 0; linkIndex < expectedAdjacencyList[index].size(); ++linkIndex)
            ASSERT_EQ(expectedAdjacencyList[index][linkIndex], nodesList[index]->neighbors[linkIndex]->val);
    }
}
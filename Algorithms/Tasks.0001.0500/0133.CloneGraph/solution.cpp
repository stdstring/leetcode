#include <memory>
#include <unordered_map>

#include "Node.h"
#include "NodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::Node;

namespace
{

class Solution
{
public:
    Node* cloneGraph(Node* node) const
    {
        std::unordered_map<Node*, Node*> clonedNodes;
        return cloneNodes(node, clonedNodes);
    }

private:
    Node* cloneNodes(Node* current, std::unordered_map<Node*, Node*> &clonedNodes) const
    {
        if (current == nullptr)
            return nullptr;
        const std::unordered_map<Node*, Node*>::const_iterator it = clonedNodes.find(current);
        if (it == clonedNodes.cend())
        {
            Node* clone = new Node(current->val);
            clonedNodes.emplace(current, clone);
            for (Node* neighbor : current->neighbors)
                clone->neighbors.push_back(cloneNodes(neighbor, clonedNodes));
            return clone;
        }
        return it->second;
    }
};

}

using CommonLib::createGraphHolder;
using CommonLib::createFromAdjacencyList;
using CommonLib::checkGraphStructure;

namespace
{

void checkClonedGraph(std::vector<std::vector<int>> const &sourceAdjacencyList)
{
    const Solution solution;
    const std::shared_ptr<Node> sourceGraph = createFromAdjacencyList(sourceAdjacencyList);
    const std::shared_ptr<Node> clonedGraph = createGraphHolder(solution.cloneGraph(sourceGraph.get()));
    checkGraphStructure(sourceGraph, sourceAdjacencyList);
    checkGraphStructure(clonedGraph, sourceAdjacencyList);
    if (sourceGraph.get() != nullptr)
        ASSERT_NE(sourceGraph.get(), clonedGraph.get());
}

}

namespace CloneGraphTask
{

TEST(CloneGraphTaskTests, Examples)
{
    checkClonedGraph({{2, 4}, {1, 3}, {2, 4}, {1, 3}});
    checkClonedGraph({{}});
    checkClonedGraph({});
    checkClonedGraph({{2}, {1}});
}

}
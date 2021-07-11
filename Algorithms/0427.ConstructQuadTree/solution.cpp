#include <deque>
#include <memory>
#include <sstream>
#include <vector>

#include "gtest/gtest.h"

namespace
{

// TODO (std_string) : think about moving into common library
class Node
{
public:
    Node(bool val, bool isLeaf) : val(val), isLeaf(isLeaf), topLeft(nullptr), topRight(nullptr), bottomLeft(nullptr), bottomRight(nullptr)
    {
    }

    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;
};

class Solution
{
public:
    Node* construct(std::vector<std::vector<int>> const &grid) const
    {
        return construct(grid, 0, 0, grid.size());
    }

private:
    Node* construct(std::vector<std::vector<int>> const &grid, size_t row, size_t column, size_t size) const
    {
        if (size == 1 || isSame(grid, row, column, size))
            return new Node(grid[row][column] == 1, true);
        Node* node = new Node(true, false);
        const size_t subgridSize = size / 2;
        node->topLeft = construct(grid, row, column, subgridSize);
        node->topRight = construct(grid, row, column + subgridSize, subgridSize);
        node->bottomLeft = construct(grid, row + subgridSize, column, subgridSize);
        node->bottomRight = construct(grid, row + subgridSize, column + subgridSize, subgridSize);
        return node;
    }

    bool isSame(std::vector<std::vector<int>> const &grid, size_t row, size_t column, size_t size) const
    {
        const int expectedValue = grid[row][column];
        for (size_t rowShift = 0; rowShift < size; ++rowShift)
        {
            for (size_t columnShift = 0; columnShift < size; ++columnShift)
            {
                if (grid[row + rowShift][column + columnShift] != expectedValue)
                    return false;
            }
        }
        return true;
    }
};

}

namespace
{

void deleteQuadTree(Node* root)
{
    if (root == nullptr)
        return;
    deleteQuadTree(root->topLeft);
    deleteQuadTree(root->topRight);
    deleteQuadTree(root->bottomLeft);
    deleteQuadTree(root->bottomRight);
    delete root;
}

// TODO (std_string) : think about moving into common library
std::shared_ptr<Node> createQuadTreeHolder(Node* root)
{
    return std::shared_ptr<Node>(root, deleteQuadTree);
}

void writeNode(std::stringstream &stream, Node* node)
{
    if (stream.str().size() > 1)
        stream << ',';
    if (node == nullptr)
        stream << "null";
    else
        stream << '[' << (node->isLeaf ? 1 : 0) << ',' << (node->val ? 1 : 0) << ']';
}

// TODO (std_string) : think about moving into common library
class Codec
{
public:
    // Encodes a tree to a single string.
    std::string serialize(std::shared_ptr<Node> const& root) const;
    std::string serializeRaw(Node* root) const;

    static std::string createData(std::shared_ptr<Node> const& root);
};

std::string Codec::serialize(std::shared_ptr<Node> const& root) const
{
    return serializeRaw(root.get());
}

std::string Codec::serializeRaw(Node* root) const
{
    std::stringstream dest;
    dest << '[';
    std::deque<Node*> processedNodes;
    if (root != nullptr)
        processedNodes.push_back(root);
    int lastNonNullIndex = root != nullptr ? 0 : -1;
    while (lastNonNullIndex >= 0)
    {
        Node* current = processedNodes.front();
        writeNode(dest, current);
        processedNodes.pop_front();
        --lastNonNullIndex;
        if (current != nullptr)
        {
            processedNodes.push_back(current->topLeft);
            if (current->topLeft)
                lastNonNullIndex = static_cast<int>(processedNodes.size()) - 1;
            processedNodes.push_back(current->topRight);
            if (current->topRight)
                lastNonNullIndex = static_cast<int>(processedNodes.size()) - 1;
            processedNodes.push_back(current->bottomLeft);
            if (current->bottomLeft)
                lastNonNullIndex = static_cast<int>(processedNodes.size()) - 1;
            processedNodes.push_back(current->bottomRight);
            if (current->bottomRight)
                lastNonNullIndex = static_cast<int>(processedNodes.size()) - 1;
        }
    }
    dest << ']';
    return dest.str();
}

std::string Codec::createData(std::shared_ptr<Node> const& root)
{
    return Codec().serialize(root);
}

}

namespace ConstructQuadTreeTask
{

TEST(ConstructQuadTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("[[0,1],[1,0],[1,1],[1,1],[1,0]]", Codec::createData(createQuadTreeHolder(solution.construct({{0, 1}, {1, 0}}))));
    ASSERT_EQ("[[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]",
              Codec::createData(createQuadTreeHolder(solution.construct({{1, 1, 1, 1, 0, 0, 0, 0},
                                                                         {1, 1, 1, 1, 0, 0, 0, 0},
                                                                         {1, 1, 1, 1, 1, 1, 1, 1},
                                                                         {1, 1, 1, 1, 1, 1, 1, 1},
                                                                         {1, 1, 1, 1, 0, 0, 0, 0},
                                                                         {1, 1, 1, 1, 0, 0, 0, 0},
                                                                         {1, 1, 1, 1, 0, 0, 0, 0},
                                                                         {1, 1, 1, 1, 0, 0, 0, 0}}))));
    ASSERT_EQ("[[1,1]]", Codec::createData(createQuadTreeHolder(solution.construct({{1, 1}, {1, 1}}))));
    ASSERT_EQ("[[1,0]]", Codec::createData(createQuadTreeHolder(solution.construct({{0}}))));
    ASSERT_EQ("[[0,1],[1,1],[1,0],[1,0],[1,1]]", Codec::createData(createQuadTreeHolder(solution.construct({{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 1, 1}, {0, 0, 1, 1}}))));
}

}
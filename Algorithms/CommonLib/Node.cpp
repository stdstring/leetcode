#include <utility>
#include <vector>

#include "Node.h"

CommonLib::Node::Node() : val(0)
{
}

CommonLib::Node::Node(int value) : val(value)
{
}

CommonLib::Node::Node(int value, std::vector<Node*> neighbors) : val(value), neighbors(std::move(neighbors))
{
}
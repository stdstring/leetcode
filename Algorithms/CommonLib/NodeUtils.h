#pragma once

#include <memory>
#include <vector>

#include "Node.h"

namespace CommonLib
{

std::shared_ptr<Node> createGraphHolder(Node* node);

std::shared_ptr<Node> createFromAdjacencyList(std::vector<std::vector<int>> const &adjacencyList);

void checkGraphStructure(std::shared_ptr<Node> const &node, std::vector<std::vector<int>> const &expectedAdjacencyList);

}
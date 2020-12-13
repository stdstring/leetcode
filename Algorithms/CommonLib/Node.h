#pragma once

#include <vector>

namespace CommonLib
{

class Node
{
public:
    Node();
    Node(int value);
    Node(int value, std::vector<Node*> neighbors);

    int val;
    std::vector<Node*> neighbors;
};

}
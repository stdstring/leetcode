#pragma once

#include <memory>
#include <vector>

#include "TreeNode.h"

namespace CommonLib
{

std::shared_ptr<TreeNode> createTreeHolder(TreeNode* root);
void checkTree(TreeNode* expected, TreeNode* actual);
void checkAndDeleteTree(TreeNode* expected, TreeNode* actual);
void checkTreeNextLinks(std::vector<std::vector<int>> const &nextLinksLayers, TreeNode* root);

}
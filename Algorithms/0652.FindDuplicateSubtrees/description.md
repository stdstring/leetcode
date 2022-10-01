## 652. Find Duplicate Subtrees

Given the ```root``` of a binary tree, return all **duplicate subtrees**.

For each kind of duplicate subtrees, you only need to return the root node of any **one** of them.

Two trees are **duplicate** if they have the **same structure** with the **same node values**.

### Example 1:

![Example 1](images/example1.jpg)

```
Input: root = [1,2,3,4,null,2,4,null,null,4]
Output: [[2,4],[4]]
```
### Example 2:

![Example 2](images/example2.jpg)

```
Input: root = [2,1,1]
Output: [[1]]
```
### Example 3:

![Example 3](images/example3.jpg)

```
Input: root = [2,2,2,3,null,3,null]
Output: [[2,3],[3]]
```

### Constraints:

* The number of the nodes in the tree will be in the range ```[1, 5000]```
* ```-200 <= Node.val <= 200```
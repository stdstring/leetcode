## 856. Score of Parentheses

Given a balanced parentheses string ```s```, compute the score of the string based on the following rule:

* ```()``` has score 1
* ```AB``` has score ```A + B```, where A and B are balanced parentheses strings.
* ```(A)``` has score ```2 * A```, where A is a balanced parentheses string.

##### Example 1:
```
Input: "()"
Output: 1
```
##### Example 2:
```
Input: "(())"
Output: 2
```
##### Example 3:
```
Input: "()()"
Output: 2
```
##### Example 4:
```
Input: "(()(()))"
Output: 6
```

##### Note:

* ```s``` is a balanced parentheses string, containing only ```(``` and ```)```.
* ```2 <= s.length <= 50```
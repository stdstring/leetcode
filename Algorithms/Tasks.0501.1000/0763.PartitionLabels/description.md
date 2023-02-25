## 763. Partition Labels

A string ```s``` of lowercase English letters is given. We want to partition this string into as many parts as possible so that each letter appears in at most one part, and return a list of integers representing the size of these parts.

##### Example:
```
Input: s = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits s into less parts.
```

##### Note:

* ```s``` will have length in range ```[1, 500]```.
* ```s``` will consist of lowercase English letters (```'a'``` to ```'z'```) only.
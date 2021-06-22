## 846. Hand of Straights

Alice has a ```hand``` of cards, given as an array of integers.

Now she wants to rearrange the cards into groups so that each group is size ```groupSize```, and consists of ```groupSize``` consecutive cards.

Return ```true``` if and only if she can.

##### Example 1:
```
Input: hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
Output: true
Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8]
```
##### Example 2:
```
Input: hand = [1,2,3,4,5], groupSize = 4
Output: false
Explanation: Alice's hand can't be rearranged into groups of 4.
```
##### Constraints:

* ```1 <= hand.length <= 10000```
* ```0 <= hand[i] <= 10^9```
* ```1 <= groupSize <= hand.length```
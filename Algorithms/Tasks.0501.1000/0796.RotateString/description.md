## 796. Rotate String

We are given two strings, ```a``` and ```b```.

A *shift on* ```a``` consists of taking string ```a``` and moving the leftmost character to the rightmost position. For example, if ```a = 'abcde'```, then it will be ```'bcdea'``` after one shift on ```a```. Return ```True``` if and only if ```a``` can become ```b``` after some number of shifts on ```a```.

##### Example 1:
```
Input: a = 'abcde', b = 'cdeab'
Output: true
```
##### Example 2:
```
Input: a = 'abcde', b = 'abced'
Output: false
```
**Note:** ```a``` and ```b``` will have length at most ```100```.
## 791. Custom Sort String

```s``` and ```t``` are strings composed of lowercase letters. In ```s```, no letter occurs more than once.

```s``` was sorted in some custom order previously. We want to permute the characters of ```t``` so that they match the order that ```s``` was sorted. More specifically, if ```x``` occurs before ```y``` in ```s```, then ```x``` should occur before ```y``` in the returned string.

Return any permutation of ```t``` (as a string) that satisfies this property.

##### Example :
```
Input:
s = "cba"
t = "abcd"
Output: "cbad"
Explanation:
"a", "b", "c" appear in s, so the order of "a", "b", "c" should be "c", "b", and "a".
Since "d" does not appear in s, it can be at any position in t. "dcba", "cdba", "cbda" are also valid outputs.
```

##### Note:

* ```s``` has length at most ```26```, and no character is repeated in ```s```.
* ```t``` has length at most ```200```.
* ```s``` and ```t``` consist of lowercase letters only.
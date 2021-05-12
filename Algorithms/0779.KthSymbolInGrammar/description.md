## 779. K-th Symbol in Grammar

On the first row, we write a ```0```. Now in every subsequent row, we look at the previous row and replace each occurrence of ```0``` with ```01```, and each occurrence of ```1``` with ```10```.

Given row ```n``` and index ```k```, return the ```k-th``` indexed symbol in row ```n```. (The values of ```k``` are 1-indexed.) (1 indexed).

##### Examples:
```
Input: n = 1, k = 1
Output: 0

Input: n = 2, k = 1
Output: 0

Input: n = 2, k = 2
Output: 1

Input: n = 4, k = 5
Output: 1

Explanation:
row 1: 0
row 2: 01
row 3: 0110
row 4: 01101001
```

##### Note:

1. ```n``` will be an integer in the range ```[1, 30]```.
1. ```k``` will be an integer in the range ```[1, 2^(n-1)]```.
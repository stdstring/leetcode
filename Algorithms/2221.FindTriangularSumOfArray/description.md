## 2221. Find Triangular Sum of an Array

You are given a **0-indexed** integer array ```nums```, where ```nums[i]``` is a digit between ```0``` and ```9``` (**inclusive**).

The **triangular sum** of ```nums``` is the value of the only element present in ```nums``` after the following process terminates:

1. Let ```nums``` comprise of ```n``` elements. If ```n == 1```, **end** the process. Otherwise, **create** a new **0-indexed** integer array ```newNums``` of length ```n - 1```.
1. For each index ```i```, where ```0 <= i < n - 1```, **assign** the value of ```newNums[i]``` as ```(nums[i] + nums[i+1]) % 10```, where ```%``` denotes modulo operator.
1. **Replace** the array ```nums``` with ```newNums```.
1. **Repeat** the entire process starting from step 1.

Return *the triangular sum of* ```nums```.

##### Example 1:
```
Input: nums = [1,2,3,4,5]
Output: 8
```
##### Example 2:
```
Input: nums = [5]
Output: 5
```

##### Constraints:

* ```1 <= nums.length <= 1000```
* ```0 <= nums[i] <= 9```
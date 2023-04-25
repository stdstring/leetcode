## 2512. Reward Top K Students

You are given two string arrays ```positiveFeedback``` and ```negativeFeedback```, containing the words denoting positive and negative feedback, respectively. Note that **no** word is both positive and negative.

Initially every student has ```0``` points. Each positive word in a feedback report **increases** the points of a student by ```3```, whereas each negative word **decreases** the points by ```1```.

You are given ```n``` feedback reports, represented by a **0-indexed** string array ```report``` and a **0-indexed** integer array ```studentId```, where ```studentId[i]``` represents the ID of the student who has received the feedback report ```report[i]```. The ID of each student is **unique**.

Given an integer ```k```, return *the top* ```k``` *students after ranking them in **non-increasing** order by their points*. In case more than one student has the same points, the one with the lower ID ranks higher.

### Example 1:
```
Input: positiveFeedback = ["smart","brilliant","studious"],
       negativeFeedback = ["not"],
       report = ["this student is studious","the student is smart"],
       studentId = [1,2],
       k = 2
Output: [1,2]
Explanation:
Both the students have 1 positive feedback and 3 points but since student 1 has a lower ID he ranks higher.
```
### Example 2:
```
Input: positiveFeedback = ["smart","brilliant","studious"],
       negativeFeedback = ["not"],
       report = ["this student is not studious","the student is smart"],
       studentId = [1,2],
       k = 2
Output: [2,1]
Explanation:
- The student with ID 1 has 1 positive feedback and 1 negative feedback, so he has 3-1=2 points.
- The student with ID 2 has 1 positive feedback, so he has 3 points.
Since student 2 has more points, [2,1] is returned.
```

### Constraints:

* ```1 <= positiveFeedback.length, negativeFeedback.length <= 10^4```
* ```1 <= positiveFeedback[i].length, negativeFeedback[j].length <= 100```
* Both ```positiveFeedback[i]``` and ```negativeFeedback[j]``` consists of lowercase English letters.
* No word is present in both ```positiveFeedback``` and ```negativeFeedback```.
* ```n == report.length == studentId.length```
* ```1 <= n <= 10^4```
* ```report[i]``` consists of lowercase English letters and spaces ```' '```.
* There is a single space between consecutive words of ```report[i]```.
* ```1 <= report[i].length <= 100```
* ```1 <= studentId[i] <= 10^9```
* All the values of ```studentId[i]``` are **unique**.
* ```1 <= k <= n```
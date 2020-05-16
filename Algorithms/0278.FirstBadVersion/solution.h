// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        if (isBadVersion(1))
            return 1;
        long long left = 1;
        long long right = n;
        while (right - left > 1)
        {
            long long middle = (right  + left) / 2;
            if (isBadVersion(middle))
                right = middle;
            else
                left = middle;
        }
        return right;
    }
};
class Solution
{
public:
    int mySqrt(int x)
    {
        if (x == 1)
            return 1;
        long long left = 0;
        long long right = x;
        while (right - left > 1)
        {
            long long middle = (right + left) / 2;
            long long product = middle * middle;
            if (product == x)
                return middle;
            else if (product < x)
                left = middle;
            else if (product > x)
                right = middle;
        }
        return left;
    }
};
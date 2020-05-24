class Solution
{
public:
    bool isHappy(int n)
    {
        std::array<bool, 4 + 9 * 81> sumStorage;
        sumStorage.fill(false);
        int sum = n;
        while (sum != 1)
        {
            sum = calcDigitsSquareSum(sum);
            if (sumStorage[sum])
                return false;
            else
                sumStorage[sum] = true;
        }
        return true;
    }

private:
    int calcDigitsSquareSum(int n)
    {
        if (n < 10)
            return n * n;
        else
        {
            int lastDigit = n % 10;
            return (lastDigit * lastDigit) + calcDigitsSquareSum(n / 10);
        }
    }
};
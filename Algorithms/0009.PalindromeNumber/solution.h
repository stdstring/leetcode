class Solution
{
public:
    bool isPalindrome(int x)
    {
        if (x == 0)
            return true;
        if (x < 0)
            return false;
        std::vector<int> digits;
        while (x > 0)
        {
            digits.push_back(x % 10);
            x /= 10;
        }
        if (digits.back() == 0)
            return false;
        for (int index = 0; index < digits.size() / 2; ++index)
        {
            if (digits[index] != digits[digits.size() - 1 - index])
                return false;
        }
        return true;
    }
};
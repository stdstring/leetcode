class Solution {
public:
    std::vector<int> plusOne(std::vector<int>& digits) {
        for (std::vector<int>::reverse_iterator it = digits.rbegin(); it != digits.rend(); ++it)
        {
            int oldValue = *it;
            int newValue = oldValue + 1;
            *it = newValue % 10;
            if (newValue < 10)
                return digits;
        }
        digits.insert(digits.begin(), 1);
        return digits;
    }
};
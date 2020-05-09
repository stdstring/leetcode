class Solution {
public:
    std::string addStrings(std::string const &a, std::string const &b) {
        std::string buf;
        size_t maxSize = std::max(a.size(), b.size());
        std::div_t dv{};
        char carry = 0;
        for (size_t index = 0; index < maxSize; ++index)
        {
            char aDigit = (index < a.size()) ? a[a.size() - index - 1] - '0' : 0;
            char bDigit = (index < b.size()) ? b[b.size() - index - 1] - '0' : 0;
            char sum = aDigit + bDigit + carry;
            dv.quot = sum;
            dv = std::div(dv.quot, 10);
            buf += "0123456789"[dv.rem];
            carry = dv.quot;
        }
        if (carry == 1) buf += "1";
        return {buf.rbegin(), buf.rend()};
    }
};
class Solution {
public:
    std::string convertToBase7(int num) {
        std::string buf;
        std::div_t dv{};
        dv.quot = num;
        do {
            dv = std::div(dv.quot, 7);
            buf += "0123456"[std::abs(dv.rem)];
        } while(dv.quot);
        if(num < 0) buf += '-';
        return {buf.rbegin(), buf.rend()};
    }
};
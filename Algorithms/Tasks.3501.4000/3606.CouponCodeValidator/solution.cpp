#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> validateCoupons(std::vector<std::string> const &code,
                                                           std::vector<std::string> const &businessLine,
                                                           std::vector<bool> const &isActive) const
    {
        std::unordered_map<std::string, int> knownBusinessLine({{"electronics", 0}, {"grocery", 1}, {"pharmacy", 2}, {"restaurant", 3}});
        std::vector<size_t> validCoupons;
        for (size_t index = 0; index < code.size(); ++index)
        {
            if (!isActive[index])
                continue;
            if (!knownBusinessLine.contains(businessLine[index]))
                continue;
            auto predicate = [](char ch)
            {
                return (ch == '_') || (('0' <= ch) && (ch <= '9')) || (('A' <= ch) && (ch <= 'Z')) || (('a' <= ch) && (ch <= 'z'));
            };
            if (code[index].empty() || !std::ranges::all_of(code[index], predicate))
                continue;
            validCoupons.emplace_back(index);
        }
        auto comp = [&code, &businessLine, &knownBusinessLine](size_t l, size_t r)
        {
            const int businessLineL = knownBusinessLine[businessLine[l]];
            const int businessLineR = knownBusinessLine[businessLine[r]];
            return (businessLineL < businessLineR) || ((businessLineL == businessLineR) && (code[l] < code[r]));
        };
        std::ranges::sort(validCoupons, comp);
        std::vector<std::string> result(validCoupons.size());
        for (size_t index = 0; index < result.size(); ++index)
            result[index] = code[validCoupons[index]];
        return result;
    }
};

}

namespace CouponCodeValidatorTask
{

TEST(CouponCodeValidatorTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"PHARMA5", "SAVE20"}),
              solution.validateCoupons({"SAVE20", "", "PHARMA5", "SAVE@20"}, {"restaurant", "grocery", "pharmacy", "restaurant"}, {true, true, true, true}));
    ASSERT_EQ(std::vector<std::string>({"ELECTRONICS_50"}),
              solution.validateCoupons({"GROCERY15", "ELECTRONICS_50", "DISCOUNT10"}, {"grocery", "electronics", "invalid"}, {false, true, true}));
}

}
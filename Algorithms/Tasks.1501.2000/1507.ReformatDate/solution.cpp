#include <string>
#include <unordered_map>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string reformatDate(std::string const &date) const
    {
        std::unordered_map<std::string, std::string> monthMap({{"Jan", "01"},
                                                               {"Feb", "02"},
                                                               {"Mar", "03"},
                                                               {"Apr", "04"},
                                                               {"May", "05"},
                                                               {"Jun", "06"},
                                                               {"Jul", "07"},
                                                               {"Aug", "08"},
                                                               {"Sep", "09"},
                                                               {"Oct", "10"},
                                                               {"Nov", "11"},
                                                               {"Dec", "12"}});
        const size_t firstDelimiter = date.find(' ');
        const size_t secondDelimiter = date.find(' ', firstDelimiter + 1);
        const std::string firstPart(date.substr(0, firstDelimiter));
        const std::string secondPart(date.substr(firstDelimiter + 1, secondDelimiter - firstDelimiter - 1));
        const std::string thirdPart(date.substr(secondDelimiter + 1));
        std::string result;
        result.append(thirdPart).append("-");
        result.append(monthMap[secondPart]).append("-");
        if (firstPart.size() == 3)
            result.append("0");
        result.append(firstPart.substr(0, firstPart.size() - 2));
        return result;
    }
};

}

namespace ReformatDateTask
{

TEST(ReformatDateTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("2052-10-20", solution.reformatDate("20th Oct 2052"));
    ASSERT_EQ("1933-06-06", solution.reformatDate("6th Jun 1933"));
    ASSERT_EQ("1960-05-26", solution.reformatDate("26th May 1960"));
}

}
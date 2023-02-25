#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> subdomainVisits(std::vector<std::string> const &cpdomains) const
    {
        std::map<std::string, size_t> domainVisitMap;
        for (std::string const &domainData : cpdomains)
        {
            const size_t spacePos = domainData.find(' ');
            const size_t count = std::stoi(domainData.substr(0, spacePos));
            std::string domain(domainData.substr(spacePos + 1));
            size_t start = 0;
            while (start != std::string::npos)
            {
                domainVisitMap[start == 0 ? domain : domain.substr(start)] += count;
                start = domain.find('.', start);
                if (start != std::string::npos)
                    ++start;
            }
        }
        std::vector<std::string> result;
        std::transform(domainVisitMap.cbegin(), domainVisitMap.cend(), std::back_inserter(result), [](auto entry){ return std::to_string(entry.second).append(" ").append(entry.first); });
        return result;
    }
};

}

namespace SubdomainVisitCountTask
{

TEST(SubdomainVisitCountTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"9001 com", "9001 discuss.leetcode.com", "9001 leetcode.com"}), solution.subdomainVisits({"9001 discuss.leetcode.com"}));
    ASSERT_EQ(std::vector<std::string>({"951 com", "900 google.mail.com", "1 intel.mail.com", "901 mail.com", "5 org", "5 wiki.org", "50 yahoo.com"}),
              solution.subdomainVisits({"900 google.mail.com", "50 yahoo.com", "1 intel.mail.com", "5 wiki.org"}));
}

}
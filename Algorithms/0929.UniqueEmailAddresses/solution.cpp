#include <string>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int numUniqueEmails(std::vector<std::string> const &emails) const
    {
        std::unordered_set<std::string> uniqueEmails;
        for (std::string const &email : emails)
        {
            std::string preparedEmail;
            bool isLocalName = true;
            bool skipChars = false;
            for (char ch : email)
            {
                if (ch == '@')
                    isLocalName = false;
                if (isLocalName)
                {
                    if (skipChars)
                        continue;
                    if (ch == '.')
                        continue;
                    if (ch == '+')
                    {
                        skipChars = true;
                        continue;
                    }
                }
                preparedEmail.push_back(ch);
            }
            uniqueEmails.insert(preparedEmail);
        }
        return static_cast<int>(uniqueEmails.size());
    }
};

}

namespace UniqueEmailAddressesTask
{

TEST(UniqueEmailAddressesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.numUniqueEmails({"test.email+alex@leetcode.com", "test.e.mail+bob.cathy@leetcode.com", "testemail+david@lee.tcode.com"}));
    ASSERT_EQ(3, solution.numUniqueEmails({"a@leetcode.com", "b@leetcode.com", "c@leetcode.com"}));
}

}
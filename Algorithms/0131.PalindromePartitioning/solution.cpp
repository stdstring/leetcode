#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<std::string>> partition(std::string const &s) const
    {
        std::vector<std::vector<std::string>> partitions;
        std::vector<std::string> current;
        partitionImpl(s, partitions, current);
        return partitions;
    }

private:
    bool isPalindrome(std::string const &source, size_t last) const
    {
        size_t front = 0;
        size_t back = last;
        while (front < back)
        {
            if (source[front] != source[back])
                return false;
            ++front;
            --back;
        }
        return true;
    }

    void partitionImpl(std::string const &source, std::vector<std::vector<std::string>> &partitions, std::vector<std::string> &current) const
    {
        if (source.empty())
        {
            partitions.push_back(current);
            return;
        }
        for (size_t index = 0; index < source.size(); ++index)
        {
            if (isPalindrome(source, index))
            {
                current.push_back(source.substr(0, index + 1));
                partitionImpl(source.substr(index + 1), partitions, current);
                current.erase(current.end() - 1);
            }
        }
    }
};

}

namespace PalindromePartitioningTask
{

TEST(PalindromePartitioningTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<std::string>>({{"a", "a", "b"}, {"aa", "b"}}), solution.partition("aab"));
    ASSERT_EQ(std::vector<std::vector<std::string>>({{"a"}}), solution.partition("a"));
}

}
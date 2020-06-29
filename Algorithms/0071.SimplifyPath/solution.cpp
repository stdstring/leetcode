#include <deque>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string simplifyPath(std::string const &path) const
    {
        std::deque<std::string> pathParts;
        // 0 char is '/' - root
        size_t index = 1;
        while (index < path.size())
        {
            if (path[index] == '/')
                ++index;
            else
            {
                std::string pathPart = extractPathPart(path, index);
                index += pathPart.size();
                if (pathPart == ".")
                {
                    // do nothing
                }
                else if (pathPart == "..")
                {
                    if (!pathParts.empty())
                        pathParts.pop_back();
                }
                else
                    pathParts.push_back(pathPart);
            }
        }
        return constructPath(pathParts);
    }

private:
    std::string extractPathPart(std::string const &path, size_t index) const
    {
        std::string pathPart;
        while (index < path.size() && path[index] != '/')
            pathPart.push_back(path[index++]);
        return pathPart;
    }

    std::string constructPath(std::deque<std::string> const &pathParts) const
    {
        std::string result;
        for (std::string const &part : pathParts)
        {
            result.push_back('/');
            result.append(part);
        }
        if (result.empty())
            result.push_back('/');
        return result;
    }
};

}

namespace SimplifyPathTask
{

TEST(SimplifyPathTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("/home", solution.simplifyPath("/home/"));
    ASSERT_EQ("/", solution.simplifyPath("/../"));
    ASSERT_EQ("/home/foo", solution.simplifyPath("/home//foo/"));
    ASSERT_EQ("/c", solution.simplifyPath("/a/./b/../../c/"));
    ASSERT_EQ("/c", solution.simplifyPath("/a/../../b/../c//.//"));
    ASSERT_EQ("/a/b/c", solution.simplifyPath("/a//b////c/d//././/.."));
}

TEST(SimplifyPathTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ("/zu/q/e", solution.simplifyPath("/.././GVzvE/./xBjU///../..///././//////T/../../.././zu/q/e"));
}

}
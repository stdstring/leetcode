#include <string>
#include <unordered_map>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    // Encodes a URL to a shortened URL.
    std::string encode(std::string const &longUrl)
    {
        const auto it = _longUrlMap.find(longUrl);
        if (it != _longUrlMap.cend())
            return it->second;
        std::string shortUrl = "http://tinyurl.com/" + std::to_string(_longUrlMap.size());
        _longUrlMap.emplace(longUrl, shortUrl);
        _shortUrlMap.emplace(shortUrl, longUrl);
        return shortUrl;
    }

    // Decodes a shortened URL to its original URL.
    std::string decode(std::string const &shortUrl)
    {
        const auto it = _shortUrlMap.find(shortUrl);
        return it == _shortUrlMap.cend() ? "" : it->second;
    }

private:
    std::unordered_map<std::string, std::string> _longUrlMap;
    std::unordered_map<std::string, std::string> _shortUrlMap;
};

}

namespace EncodeDecodeTinyURLTask
{

TEST(EncodeDecodeTinyURLTaskTests, Examples)
{
    Solution solution;
    ASSERT_EQ("https://leetcode.com/problems/design-tinyurl", solution.decode(solution.encode("https://leetcode.com/problems/design-tinyurl")));
}

}
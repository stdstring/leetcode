#include <iterator>
#include <string>
#include <unordered_map>

#include "gtest/gtest.h"

namespace
{

class AuthenticationManager
{
public:
    AuthenticationManager(int timeToLive) : _timeToLive(timeToLive)
    {
    }

    void generate(std::string const &tokenId, int currentTime)
    {
        _tokensMap.emplace(tokenId, currentTime);
    }

    void renew(std::string const &tokenId, int currentTime)
    {
        const auto iterator = _tokensMap.find(tokenId);
        if (iterator == _tokensMap.end())
            return;
        if ((iterator->second + _timeToLive) <= currentTime)
        {
            _tokensMap.erase(iterator);
            return;
        }
        iterator->second = currentTime;
    }

    int countUnexpiredTokens(int currentTime)
    {
        for (auto iterator = _tokensMap.cbegin(); iterator != _tokensMap.cend();)
        {
            const auto nextIterator = std::next(iterator, 1);
            if ((iterator->second + _timeToLive) <= currentTime)
                _tokensMap.erase(iterator);
            iterator = nextIterator;
        }
        return static_cast<int>(_tokensMap.size());
    }

private:
    int _timeToLive;
    std::unordered_map<std::string, int> _tokensMap;
};

}

namespace DesignAuthenticationManagerTask
{

TEST(DesignAuthenticationManagerTaskTests, Examples)
{
    AuthenticationManager authenticationManager(5);
    ASSERT_NO_THROW(authenticationManager.renew("aaa", 1));
    ASSERT_NO_THROW(authenticationManager.generate("aaa", 2));
    ASSERT_EQ(1, authenticationManager.countUnexpiredTokens(6));
    ASSERT_NO_THROW(authenticationManager.generate("bbb", 7));
    ASSERT_NO_THROW(authenticationManager.renew("aaa", 8));
    ASSERT_NO_THROW(authenticationManager.renew("bbb", 10));
    ASSERT_EQ(0, authenticationManager.countUnexpiredTokens(15));
}

}
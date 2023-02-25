#include <string>
#include <sstream>
#include <utility>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string complexNumberMultiply(std::string const &a, std::string const &b) const
    {
        const std::pair<int, int> aNumber = toComplex(a);
        const std::pair<int, int> bNumber = toComplex(b);
        return toString({aNumber.first * bNumber.first - aNumber.second * bNumber.second, aNumber.first * bNumber.second + aNumber.second * bNumber.first});
    }

private:
    std::pair<int, int> toComplex(std::string const &source) const
    {
        size_t plusIndex = 0;
        int a = std::stoi(source, &plusIndex);
        int b = std::stoi(source.substr(plusIndex + 1, source.size() - plusIndex - 2));
        return {a, b};
    }

    std::string toString(std::pair<int, int> const &source) const
    {
        std::stringstream buffer;
        buffer << source.first << "+" << source.second << "i";
        return buffer.str();
    }
};

}

namespace ComplexNumberMultiplicationTask
{

TEST(ComplexNumberMultiplicationTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("0+2i", solution.complexNumberMultiply("1+1i", "1+1i"));
    ASSERT_EQ("0+-2i", solution.complexNumberMultiply("1+-1i", "1+-1i"));
}

}
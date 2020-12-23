#include <cctype>
#include <map>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string countOfAtoms(std::string const &formula) const
    {
        size_t pos = 0;
        std::map<std::string, int> data(read(formula, pos));
        std::string result;
        for (auto const &element : data)
        {
            result.append(element.first);
            if (element.second > 1)
                result.append(std::to_string(element.second));
        }
        return result;
    }

private:
    int readCount(std::string const &formula, size_t &pos) const
    {
        int count = 0;
        while (pos < formula.size() && std::isdigit(formula[pos]))
            count = 10 * count + (formula[pos++] - '0');
        return count == 0 ? 1 : count;
    }

    std::string readElement(std::string const &formula, size_t &pos) const
    {
        std::string element;
        element.push_back(formula[pos++]);
        while (pos < formula.size() && std::islower(formula[pos]))
            element.push_back(formula[pos++]);
        return element;
    }

    void appendElement(std::map<std::string, int> &data, std::string const &element, int count) const
    {
        std::map<std::string, int>::iterator entry = data.find(element);
        if (entry == data.end())
            data.emplace(element, count);
        else
            entry->second += count;
    }

    void mergeData(std::map<std::string, int> &data, std::map<std::string, int> const &subFormulaData, int multiplier) const
    {
        for (auto const &subFormulaElement : subFormulaData)
            appendElement(data, subFormulaElement.first, multiplier * subFormulaElement.second);
    }

    std::map<std::string, int> read(std::string const &formula, size_t &pos) const
    {
        std::map<std::string, int> data;
        while (pos < formula.size() && formula[pos] != ')')
        {
            if (std::isupper(formula[pos]))
            {
                // read element
                std::string element = readElement(formula, pos);
                // read count
                const int count = readCount(formula, pos);
                // append
                appendElement(data, element, count);
            }
            else if (formula[pos] == '(')
            {
                // read '('
                ++pos;
                // read sub formula
                std::map<std::string, int> subFormulaData(read(formula, pos));
                // read ')'
                ++pos;
                // read count
                const int count = readCount(formula, pos);
                // merge
                mergeData(data, subFormulaData, count);
            }
        }
        return data;
    }
};

}

namespace NumberOfAtomsTask
{

TEST(NumberOfAtomsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("H2O", solution.countOfAtoms("H2O"));
    ASSERT_EQ("H2MgO2", solution.countOfAtoms("Mg(OH)2"));
    ASSERT_EQ("K4N2O14S4", solution.countOfAtoms("K4(ON(SO3)2)2"));
    ASSERT_EQ("Be32", solution.countOfAtoms("Be32"));
}

}
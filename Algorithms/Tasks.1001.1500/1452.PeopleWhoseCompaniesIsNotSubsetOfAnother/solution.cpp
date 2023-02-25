#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> peopleIndexes(std::vector<std::vector<std::string>> const &favoriteCompanies) const
    {
        std::vector<Person> persons;
        persons.reserve(favoriteCompanies.size());
        for (size_t index = 0; index < favoriteCompanies.size(); ++index)
        {
            persons.emplace_back(index, favoriteCompanies[index]);
            std::sort(persons.back().Companies.begin(), persons.back().Companies.end());
        }
        std::sort(persons.begin(), persons.end(), [](Person const &l, Person const &r){ return l.Companies.size() < r.Companies.size(); });
        std::vector<int> indices;
        for (size_t checkedIndex = 0; checkedIndex < persons.size(); ++checkedIndex)
        {
            bool isSubset = false;
            for (size_t index = checkedIndex + 1; index < persons.size(); ++index)
            {
                if (persons[checkedIndex].Companies.size() == persons[index].Companies.size())
                    continue;
                if (isCompaniesSubset(persons[index].Companies, persons[checkedIndex].Companies))
                {
                    isSubset = true;
                    break;
                }
            }
            if (!isSubset)
                indices.push_back(static_cast<int>(persons[checkedIndex].Index));
        }
        std::sort(indices.begin(), indices.end());
        return indices;
    }

private:
    struct Person
    {
        Person(size_t index, std::vector<std::string> const &companies) : Index(index), Companies(companies)
        {
        }
        size_t Index;
        std::vector<std::string> Companies;
    };

    [[nodiscard]] bool isCompaniesSubset(std::vector<std::string> const &companies, std::vector<std::string> const &checked) const
    {
        size_t checkedIndex = 0;
        for (size_t companiesIndex = 0; (companiesIndex < companies.size()) && (checkedIndex < checked.size()); ++companiesIndex)
        {
            if (companies[companiesIndex] > checked[checkedIndex])
                return false;
            if (companies[companiesIndex] == checked[checkedIndex])
                ++checkedIndex;
            if (checkedIndex == checked.size())
                return true;
        }
        return false;
    }
};

}

namespace PeopleWhoseCompaniesIsNotSubsetOfAnotherTask
{

TEST(PeopleWhoseCompaniesIsNotSubsetOfAnotherTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 1, 4}), solution.peopleIndexes({{"leetcode", "google", "facebook"}, {"google", "microsoft"}, {"google", "facebook"}, {"google"}, {"amazon"}}));
    ASSERT_EQ(std::vector<int>({0, 1}), solution.peopleIndexes({{"leetcode", "google", "facebook"}, {"leetcode", "amazon"}, {"facebook", "google"}}));
    ASSERT_EQ(std::vector<int>({0, 1, 2, 3}), solution.peopleIndexes({{"leetcode"}, {"google"}, {"facebook"}, {"amazon"}}));
}

}
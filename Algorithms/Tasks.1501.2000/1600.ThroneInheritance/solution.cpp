#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class ThroneInheritance
{
public:
    ThroneInheritance(std::string const &kingName) : _kingName(kingName)
    {
        _persons.emplace(kingName, PersonData());
    }

    void birth(std::string const &parentName, std::string const &childName)
    {
        _persons[parentName].Children.push_back(childName);
        _persons.emplace(childName, PersonData());
    }

    void death(std::string const &name)
    {
        _persons[name].IsAlive = false;
    }

    std::vector<std::string> getInheritanceOrder()
    {
        std::vector<std::string> inheritance;
        generateInheritance(_kingName, inheritance);
        return inheritance;
    }

private:
    struct PersonData
    {
        bool IsAlive = true;
        std::vector<std::string> Children;
    };

    std::string _kingName;
    std::unordered_map<std::string, PersonData> _persons;

    void generateInheritance(std::string const &name, std::vector<std::string> &inheritance)
    {
        PersonData const &person = _persons[name];
        if (person.IsAlive)
            inheritance.push_back(name);
        for (std::string const &child : person.Children)
            generateInheritance(child, inheritance);
    }
};

}

namespace ThroneInheritanceTask
{

TEST(ThroneInheritanceTaskTests, Examples)
{
    ThroneInheritance inheritance("king");
    ASSERT_NO_THROW(inheritance.birth("king", "andy"));
    ASSERT_NO_THROW(inheritance.birth("king", "bob"));
    ASSERT_NO_THROW(inheritance.birth("king", "catherine"));
    ASSERT_NO_THROW(inheritance.birth("andy", "matthew"));
    ASSERT_NO_THROW(inheritance.birth("bob", "alex"));
    ASSERT_NO_THROW(inheritance.birth("bob", "asha"));
    ASSERT_EQ(std::vector<std::string>({"king", "andy", "matthew", "bob", "alex", "asha", "catherine"}), inheritance.getInheritanceOrder());
    ASSERT_NO_THROW(inheritance.death("bob"));
    ASSERT_EQ(std::vector<std::string>({"king", "andy", "matthew", "alex", "asha", "catherine"}), inheritance.getInheritanceOrder());
}

}
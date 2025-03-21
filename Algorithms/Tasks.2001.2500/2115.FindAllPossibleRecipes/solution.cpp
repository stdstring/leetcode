#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> findAllRecipes(std::vector<std::string> const &recipes,
                                                          std::vector<std::vector<std::string>> const &ingredients,
                                                          std::vector<std::string> const &supplies) const
    {
        std::unordered_set<std::string> suppliesSet(supplies.cbegin(), supplies.cend());
        std::unordered_map<std::string, bool> recipesStatus;
        std::unordered_map<std::string, std::vector<std::string>> ingredientsMap;
        for (size_t index = 0; index < recipes.size(); ++index)
        {
            recipesStatus[recipes[index]] = false;
            ingredientsMap.emplace(recipes[index], ingredients[index]);
        }
        std::vector<std::string> result;
        for (std::string const &recipe : recipes)
        {
            if (processRecipe(recipe, ingredientsMap, recipesStatus, suppliesSet))
                result.emplace_back(recipe);
        }
        std::ranges::sort(result);
        return result;
    }

private:
    [[nodiscard]] bool processRecipe(std::string const &recipe,
                                     std::unordered_map<std::string, std::vector<std::string>> const &ingredientsMap,
                                     std::unordered_map<std::string, bool> &recipesStatus,
                                     std::unordered_set<std::string> &suppliesSet) const
    {
        if (recipesStatus[recipe])
            return suppliesSet.contains(recipe);
        recipesStatus[recipe] = true;
        for (std::string const &ingredient : ingredientsMap.at(recipe))
        {
            if (suppliesSet.contains(ingredient))
                continue;
            if (!recipesStatus.contains(ingredient) || recipesStatus[ingredient])
                return false;
            bool canProcessed = processRecipe(ingredient, ingredientsMap, recipesStatus, suppliesSet);
            if (!canProcessed)
                return false;
        }
        suppliesSet.emplace(recipe);
        return true;
    }
};

}

namespace FindAllPossibleRecipesTask
{

TEST(FindAllPossibleRecipesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"bread"}),
              solution.findAllRecipes({"bread"}, {{"yeast", "flour"}}, {"yeast", "flour", "corn"}));
    ASSERT_EQ(std::vector<std::string>({"bread", "sandwich"}),
              solution.findAllRecipes({"bread", "sandwich"}, {{"yeast", "flour"}, {"bread", "meat"}}, {"yeast", "flour", "meat"}));
    ASSERT_EQ(std::vector<std::string>({"bread", "burger", "sandwich"}),
              solution.findAllRecipes({"bread", "sandwich", "burger"},
                                      {{"yeast", "flour"}, {"bread", "meat"}, {"sandwich", "meat", "bread"}},
                                      {"yeast", "flour", "meat"}));
}

TEST(FindAllPossibleRecipesTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>(), solution.findAllRecipes({"bread"}, {{"yeast", "flour"}}, {"yeast"}));
}

}
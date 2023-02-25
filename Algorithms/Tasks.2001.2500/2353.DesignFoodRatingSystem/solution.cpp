#include <map>
#include <set>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class FoodRatings
{
public:
    FoodRatings(std::vector<std::string> const &foods, std::vector<std::string> const &cuisines, std::vector<int> const &ratings)
    {
        for (size_t index = 0; index < foods.size(); ++index)
        {
            _foodMap[foods[index]] = FoodData(cuisines[index], ratings[index]);
            auto iterator = _cuisineMap.find(cuisines[index]);
            if (iterator == _cuisineMap.end())
                iterator = _cuisineMap.emplace(cuisines[index], TRatingFoodMap()).first;
            iterator->second[ratings[index]].emplace(foods[index]);
        }
    }

    void changeRating(std::string const &food, int newRating)
    {
        const auto foodIterator = _foodMap.find(food);
        const int oldRating = foodIterator->second.Rating;
        foodIterator->second.Rating = newRating;
        const auto cuisineIterator = _cuisineMap.find(foodIterator->second.Cuisine);
        const auto oldRatingIterator = cuisineIterator->second.find(oldRating);
        if (oldRatingIterator->second.size() == 1)
            cuisineIterator->second.erase(oldRatingIterator);
        else
            oldRatingIterator->second.erase(food);
        cuisineIterator->second[newRating].emplace(food);
    }

    std::string highestRated(std::string const &cuisine)
    {
        return *_cuisineMap[cuisine].crbegin()->second.cbegin();
    }

private:
    struct FoodData
    {
        FoodData() = default;

        FoodData(std::string const &cuisine, int rating) : Cuisine(cuisine), Rating(rating)
        {
        }

        std::string Cuisine;
        int Rating = 0;
    };

    typedef std::map<int, std::set<std::string>> TRatingFoodMap;
    std::unordered_map<std::string, FoodData> _foodMap;
    std::unordered_map<std::string, TRatingFoodMap> _cuisineMap;
};

}

namespace DesignFoodRatingSystemTask
{

TEST(DesignFoodRatingSystemTaskTests, Examples)
{
    FoodRatings foodRatings({"kimchi", "miso", "sushi", "moussaka", "ramen", "bulgogi"},
                            {"korean", "japanese", "japanese", "greek", "japanese", "korean"},
                            {9, 12, 8, 15, 14, 7});
    ASSERT_EQ("kimchi", foodRatings.highestRated("korean"));
    ASSERT_EQ("ramen", foodRatings.highestRated("japanese"));
    ASSERT_NO_THROW(foodRatings.changeRating("sushi", 16));
    ASSERT_EQ("sushi", foodRatings.highestRated("japanese"));
    ASSERT_NO_THROW(foodRatings.changeRating("ramen", 16));
    ASSERT_EQ("ramen", foodRatings.highestRated("japanese"));
}

}
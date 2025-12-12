#include <algorithm>
#include <map>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> countMentions(int numberOfUsers, std::vector<std::vector<std::string>> const &events) const
    {
        std::vector<Event> typedEvents(events.size());
        for (size_t index = 0; index < events.size(); ++index)
            typedEvents[index] = createEvent(events[index]);
        auto comp = [](Event const &l, Event const &r)
        {
            return (l.Timestamp < r.Timestamp) || ((l.Timestamp == r.Timestamp) && (l.Type < r.Type));
        };
        std::ranges::sort(typedEvents, comp);
        std::unordered_set<int> onlineUsers;
        for (int user = 0; user < numberOfUsers; ++user)
            onlineUsers.emplace(user);
        std::map<int, std::vector<int>> offlineData;
        std::vector<int> mentions(numberOfUsers, 0);
        for (Event const &event : typedEvents)
        {
            const int currentTime = event.Timestamp;
            while (!offlineData.empty() && offlineData.cbegin()->first <= currentTime)
            {
                for (int id : offlineData.cbegin()->second)
                    onlineUsers.emplace(id);
                offlineData.erase(offlineData.cbegin());
            }
            switch (event.Type)
            {
            case EventType::OFFLINE:
                processOfflineEvent(event, onlineUsers, offlineData);
                break;
            case EventType::MESSAGE:
                processMessageEvent(event, numberOfUsers, onlineUsers, mentions);
                break;
            }
        }
        return mentions;
    }

private:
    enum class EventType { OFFLINE = 1, MESSAGE = 2 };

    struct Event
    {
        Event() = default;
        Event(EventType type, int timestamp, std::string const &data)
            : Type(type), Timestamp(timestamp), Data(data)
        {
        }

        EventType Type = EventType::OFFLINE;
        int Timestamp = 0;
        std::string Data;
    };

    [[nodiscard]] Event createEvent(std::vector<std::string> const &source) const
    {
        const EventType eventType = source[0] == "OFFLINE" ? EventType::OFFLINE : EventType::MESSAGE;
        const int timestamp = std::stoi(source[1]);
        return Event(eventType, timestamp, source[2]);
    }

    void processOfflineEvent(Event const &event, std::unordered_set<int> &onlineUsers, std::map<int, std::vector<int>> &offlineData) const
    {
        constexpr int offlineDuration = 60;
        const int id = std::stoi(event.Data);
        onlineUsers.erase(id);
        offlineData[event.Timestamp + offlineDuration].emplace_back(id);
    }

    void processMessageEvent(Event const& event, int numberOfUsers, std::unordered_set<int> const &onlineUsers, std::vector<int> &mentions) const
    {
        if (event.Data == "ALL")
        {
            for (int user = 0; user < numberOfUsers; ++user)
                ++mentions[user];
            return;
        }
        if (event.Data == "HERE")
        {
            for (int user : onlineUsers)
                ++mentions[user];
            return;
        }
        constexpr size_t idHeaderSize = 2;
        for (size_t current = 0; current < event.Data.size();)
        {
            const size_t delimiter = event.Data.find(' ', current);
            size_t next = (delimiter == std::string::npos) ? event.Data.size() : delimiter;
            const int id = std::stoi(event.Data.substr(current + idHeaderSize, next - current - idHeaderSize));
            if (next < event.Data.size())
                ++next;
            ++mentions[id];
            current = next;
        }
    }
};

}

namespace CountMentionsPerUserTask
{

TEST(CountMentionsPerUserTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({2, 2}), solution.countMentions(2, {{"MESSAGE", "10", "id1 id0"}, {"OFFLINE", "11", "0"}, {"MESSAGE", "71", "HERE"}}));
    ASSERT_EQ(std::vector<int>({2, 2}), solution.countMentions(2, {{"MESSAGE", "10", "id1 id0"}, {"OFFLINE", "11", "0"}, {"MESSAGE", "12", "ALL"}}));
    ASSERT_EQ(std::vector<int>({0, 1}), solution.countMentions(2, {{"OFFLINE", "10", "0"}, {"MESSAGE", "12", "HERE"}}));
}

TEST(CountMentionsPerUserTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 0}), solution.countMentions(2, {{"OFFLINE", "10", "0"}, {"OFFLINE", "10", "1"}, {"MESSAGE", "12", "HERE"}}));
}

}
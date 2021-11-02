#include <algorithm>
#include <random>
#include <stdexcept>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Master
{
public:
    Master(std::vector<std::string> const &wordlist, std::string const &secret, size_t numguesses) :
        _words(wordlist.cbegin(), wordlist.cend()),
        _secret(secret),
        _currentGuesses(0),
        _maxGuesses(numguesses)
    {
    }

    int guess(std::string const &word)
    {
        if (_currentGuesses >= _maxGuesses)
            throw std::logic_error("guess count");
        ++_currentGuesses;
        if (_words.count(word) == 0)
            return -1;
        int matchCount = 0;
        for (size_t index = 0; index < _secret.size(); ++index)
        {
            if (_secret[index] == word[index])
                ++matchCount;
        }
        return matchCount;
    }

private:
    std::unordered_set<std::string> _words;
    std::string _secret;
    size_t _currentGuesses;
    size_t _maxGuesses;
};

class Solution
{
public:
    // This task isn't correct because this solution (and others) doesn't process all cases properly
    void findSecretWord(std::vector<std::string> const &wordlist, Master &master) const
    {
        std::vector<std::string> words(wordlist);
        std::random_device randomDevice;
        std::mt19937 generator(randomDevice());
        std::shuffle(words.begin(), words.end(), generator);
        std::vector<size_t> suitableWords(words.size(), 0);
        for (size_t index = 0; index < words.size(); ++index)
            suitableWords[index] = index;
        const size_t expectedMatchCount = words.front().size();
        while (true)
        {
            size_t sourceWord = suitableWords.front();
            size_t matchCount = master.guess(words[sourceWord]);
            if (matchCount == expectedMatchCount)
                return;
            std::vector<size_t> nextSuitableWords;
            auto predicate = [this, &words, sourceWord, matchCount](size_t checkedWord) { return sourceWord != checkedWord && checkMatch(words[sourceWord], words[checkedWord], matchCount); };
            std::copy_if(suitableWords.cbegin(), suitableWords.cend(), std::back_inserter(nextSuitableWords), predicate);
            std::swap(suitableWords, nextSuitableWords);
        }
    }

private:
    bool checkMatch(std::string const &sourceWord, std::string const &checkedWord, size_t matchCount) const
    {
        size_t actualMatchCount = 0;
        for (size_t index = 0; index < sourceWord.size(); ++index)
        {
            if (sourceWord[index] == checkedWord[index])
                ++actualMatchCount;
        }
        return actualMatchCount == matchCount;
    }
};

}

namespace
{

void checkFindSecretWord(std::vector<std::string> const &wordlist, std::string const &secret, size_t numguesses)
{
    Master master(wordlist, secret, numguesses);
    const Solution solution;
    ASSERT_NO_THROW(solution.findSecretWord(wordlist, master));
}

}

namespace GuessWordTask
{

TEST(GuessWordTaskTests, Examples)
{
    checkFindSecretWord({"acckzz", "ccbazz", "eiowzz", "abcczz"}, "acckzz", 10);
    checkFindSecretWord({"hamada", "khaled"}, "hamada", 10);
}

TEST(GuessWordTaskTests, FromWrongAnswers)
{
    checkFindSecretWord({"gaxckt", "trlccr", "jxwhkz", "ycbfps", "peayuf", "yiejjw", "ldzccp", "nqsjoa", "qrjasy", "pcldos",
                           "acrtag", "buyeia", "ubmtpj", "drtclz", "zqderp", "snywek", "caoztp", "ibpghw", "evtkhl", "bhpfla",
                           "ymqhxk", "qkvipb", "tvmued", "rvbass", "axeasm", "qolsjg", "roswcb", "vdjgxx", "bugbyv", "zipjpc",
                           "tamszl", "osdifo", "dvxlxm", "iwmyfb", "wmnwhe", "hslnop", "nkrfwn", "puvgve", "rqsqpq", "jwoswl",
                           "tittgf", "evqsqe", "aishiv", "pmwovj", "sorbte", "hbaczn", "coifed", "hrctvp", "vkytbw", "dizcxz",
                           "arabol", "uywurk", "ppywdo", "resfls", "tmoliy", "etriev", "oanvlx", "wcsnzy", "loufkw", "onnwcy",
                           "novblw", "mtxgwe", "rgrdbt", "ckolob", "kxnflb", "phonmg", "egcdab", "cykndr", "lkzobv", "ifwmwp",
                           "jqmbib", "mypnvf", "lnrgnj", "clijwa", "kiioqr", "syzebr", "rqsmhg", "sczjmz", "hsdjfp", "mjcgvm",
                           "ajotcx", "olgnfv", "mjyjxj", "wzgbmg", "lpcnbj", "yjjlwn", "blrogv", "bdplzs", "oxblph", "twejel",
                           "rupapy", "euwrrz", "apiqzu", "ydcroj", "ldvzgq", "zailgu", "xgqpsr", "wxdyho", "alrplq", "brklfk"}, "hbaczn", 10);
    checkFindSecretWord({"wichbx", "oahwep", "tpulot", "eqznzs", "vvmplb", "eywinm", "dqefpt", "kmjmxr", "ihkovg", "trbzyb",
                           "xqulhc", "bcsbfw", "rwzslk", "abpjhw", "mpubps", "viyzbc", "kodlta", "ckfzjh", "phuepp", "rokoro",
                           "nxcwmo", "awvqlr", "uooeon", "hhfuzz", "sajxgr", "oxgaix", "fnugyu", "lkxwru", "mhtrvb", "xxonmg",
                           "tqxlbr", "euxtzg", "tjwvad", "uslult", "rtjosi", "hsygda", "vyuica", "mbnagm", "uinqur", "pikenp",
                           "szgupv", "qpxmsw", "vunxdn", "jahhfn", "kmbeok", "biywow", "yvgwho", "hwzodo", "loffxk", "xavzqd",
                           "vwzpfe", "uairjw", "itufkt", "kaklud", "jjinfa", "kqbttl", "zocgux", "ucwjig", "meesxb", "uysfyc",
                           "kdfvtw", "vizxrv", "rpbdjh", "wynohw", "lhqxvx", "kaadty", "dxxwut", "vjtskm", "yrdswc", "byzjxm",
                           "jeomdc", "saevda", "himevi", "ydltnu", "wrrpoc", "khuopg", "ooxarg", "vcvfry", "thaawc", "bssybb",
                           "ccoyyo", "ajcwbj", "arwfnl", "nafmtm", "xoaumd", "vbejda", "kaefne", "swcrkh", "reeyhj", "vmcwaf",
                           "chxitv", "qkwjna", "vklpkp", "xfnayl", "ktgmfn", "xrmzzm", "fgtuki", "zcffuv", "srxuus", "pydgmq"}, "ccoyyo", 10);
}

}
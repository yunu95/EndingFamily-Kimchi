#include "NewsText.h"
#include <algorithm>
#include "GameInfo.h"

using namespace YunutyEngine;

vector<pair<int, string>> NewsText::newsList;
deque<pair<int, string>> NewsText::currentNewsList;
pair<int, string> NewsText::currentNews;
int NewsText::currentNewsIndex;
const int NewsText::maxConcurrentNews;

void NewsText::AddNews(int unlockKimchiNum, string news)
{
    newsList.push_back(make_pair(unlockKimchiNum, news));
}
void NewsText::Sort()
{
    sort(newsList.begin(), newsList.end(), [](const pair<int, string>& lhs, const pair<int, string>& rhs)
        {
            return lhs.first < rhs.first;
        });
}
void NewsText::Start()
{
    Update();
}
void NewsText::Update()
{
    accumulatedTime += Time::GetDeltaTimeUnscaled();
    if (accumulatedTime > refreshCooltime)
    {
        accumulatedTime -= refreshCooltime;
        while (!newsList.empty() && newsList.front().first <= GameInfo::kimchis)
        {
            currentNewsList.push_back(newsList.front());
            newsList.erase(newsList.begin());
            if (currentNewsList.size() > maxConcurrentNews)
                currentNewsList.pop_front();
        }
        if (!currentNewsList.empty())
            currentNews = currentNewsList[++currentNewsIndex % currentNewsList.size()];
        SetText(width, height, currentNews.second);
    }
}

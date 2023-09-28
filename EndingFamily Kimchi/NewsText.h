#pragma once
#include "TextImage.h"
#include <queue>

class NewsText :
    public TextImage
{
private :
    static vector<pair<int, string>> newsList;
    static deque<pair<int, string>> currentNewsList;
    static pair<int, string> currentNews;
    static int currentNewsIndex;
    static const int maxConcurrentNews = 3;
protected:
    void Start() override;
    void Update() override;
public:
    static void AddNews(int unlockKimchiNum, string news);
    static void Sort();
    double refreshCooltime=10;
    double accumulatedTime=refreshCooltime;
};


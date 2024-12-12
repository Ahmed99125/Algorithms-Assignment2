//
// Created by asus on 12/11/2024.
//

#ifndef SKIPLIST_GAME_H
#define SKIPLIST_GAME_H
#include "SkipList.h"
#include "SkipListDescendant.h"
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Game {
private:
    SkipList<int> ID_SkipList, *ScoresSkipList;
    map<int, pair<string, int>> Players;
public:
    Game();
    void join(string name, int id, int score);
    void updateScore(int id, int newScore);
    void leave(int id);
    vector<pair<string, int>> getTopN(int n);
};


#endif //SKIPLIST_GAME_H

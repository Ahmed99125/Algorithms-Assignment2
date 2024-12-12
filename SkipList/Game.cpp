//
// Created by asus on 12/11/2024.
//

#include "Game.h"
#include <iostream>
using namespace std;

Game::Game() {
    ID_SkipList = SkipList<int>();
    ScoresSkipList = new SkipListDescendant<int>();
}

void Game::join(string name, int id, int score) {
    Players.insert({id, {name, score}});
    Node<int>* idNode = ID_SkipList.insert(id);
    Node<int>* scoreNode = ScoresSkipList->insert(score);
    idNode->relationBetweenScoreAndID = scoreNode;
    scoreNode->relationBetweenScoreAndID = idNode;
}

void Game::updateScore(int id, int newScore) {
    int oldScore = Players[id].second;
    Node<int>* idNode = ID_SkipList.search(id).second;
    ScoresSkipList->Delete(oldScore);
    Node<int>* newScoreNode = ScoresSkipList->insert(newScore);
    newScoreNode->relationBetweenScoreAndID = idNode;
    idNode->relationBetweenScoreAndID = newScoreNode;

    Players[id].second = newScore;
}

void Game::leave(int id) {
    int score = Players[id].second;
    Node<int>* scoreNode = ID_SkipList.search(id).second->relationBetweenScoreAndID;
    ID_SkipList.Delete(id);
    ScoresSkipList->Delete(scoreNode);
    Players.erase(id);
}

vector<pair<string, int>> Game::getTopN(int n) {
    vector<pair<string, int>> topNPlayersWithTheirScores;
    Node<int>* cur = ScoresSkipList->getHead()->next;
    for (int i = 0; i < n && cur->next != nullptr; ++i) {
        int score = cur->val;
        int id = cur->relationBetweenScoreAndID->val;
        topNPlayersWithTheirScores.push_back({Players[id].first, score});
        cur = cur->next;
    }
    return topNPlayersWithTheirScores;
}

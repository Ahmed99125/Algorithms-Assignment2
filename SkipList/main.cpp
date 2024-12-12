#include <iostream>
#include "SkipList.h"
#include "SkipListDescendant.h"
#include "Game.h"
using namespace std;

int main() {
    Game g = Game();
    g.join("Jack", 1, 2000);
    g.join("Max", 2, 1500);
    g.join("Nour", 3, 4000);
    g.updateScore(2, 2000);
    g.join("Mostafa", 4, 5000);
    g.leave(2);
    vector<pair<string, int>> players = g.getTopN(3);
    for (auto element : players){
        cout << "Player: " << element.first << ". His score: " << element.second << endl;
    }

//    pair<bool, Node*> t = sl.search(2);
//    if (t.first){
//        cout << "Target found: 8, its details are\nNext: " << t.second->next->val << "\nprev: " << t.second->prev->val << '\n';
//        auto v1 = (t.second->LevelUp) ? t.second->LevelUp->val : 0;
//        auto v2 = (t.second->LevelDown) ? t.second->LevelDown->val : 0;
//        cout << "Up: " << v1 << "\nDown: " << v2;
//    }
}

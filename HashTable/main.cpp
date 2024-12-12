#include "HashTable.h"

using namespace std;

int main() {
    HashTable ht(10);
    ht.insert(10, 1, 1);
    ht.insert(20, 1, 1);
    ht.insert(30, 1, 1);
    ht.printTable();
}
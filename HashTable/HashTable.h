#include <iostream>

class Node {
public:
    int key;
    Node* next;

    Node(int key) {
        this->key = key;
        next = nullptr;
    }
};

class HashTable {
public:
    HashTable(int size) {
        tableSize = size;
        table = new Node*[size];
        for (int i = 0; i < size; i++) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < tableSize; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

    void insert(int key, int method, int collisionMethod) {
        int index = hash(key, method);

        if (collisionMethod == 1) { // Chaining
            Node* newNode = new Node(key);
            newNode->next = table[index];
            table[index] = newNode;
        } else if (collisionMethod == 2) { // Linear Probing
            linearProbing(key, index);
        } else if (collisionMethod == 3) { // Quadratic Probing
            quadraticProbing(key, index);
        } else if (collisionMethod == 4) { // Double Hashing
            doubleHashing(key, index);
        } else {
            std::cerr << "Invalid collision resolution method." << std::endl;
        }
    }

    void printTable() {
        for (int i = 0; i < tableSize; i++) {
            std::cout << "Index " << i << ": ";
            Node* current = table[i];
            while (current != nullptr) {
                std::cout << current->key << " -> ";
                current = current->next;
            }
            std::cout << "NULL" << std::endl;
        }
    }

private:
    Node** table;
    int tableSize;

    int hash(int key, int method) {
        switch (method) {
            case 1:
                return divisionMethod(key);
            case 2:
                return multiplicationMethod(key);
            case 3:
                return midSquareMethod(key);
            case 4:
                return foldingMethod(key);
            default:
                std::cerr << "Invalid hashing method." << std::endl;
                return -1;
        }
    }

    int divisionMethod(int key) {
        return key % tableSize;
    }

    int multiplicationMethod(int key) {
        double A = 0.6;
        double product = key * A;
        return (int)(tableSize * (product - (int)product));
    }

    int midSquareMethod(int key) {
        int square = key * key;
        int midDigits = (square / 100) % 100;
        return midDigits % tableSize;
    }

    int foldingMethod(int key) {
        int sum = 0;
        while (key > 0) {
            sum += key % 10;
            key /= 10;
        }
        return sum % tableSize;
    }

    void linearProbing(int key, int index) {
        int i = 1;
        while (table[(index + i) % tableSize] != nullptr) {
            i++;
        }
        table[(index + i) % tableSize] = new Node(key);
    }

    void quadraticProbing(int key, int index) {
        int i = 1;
        while (table[(index + i * i) % tableSize] != nullptr) {
            i++;
        }
        table[(index + i * i) % tableSize] = new Node(key);
    }

    int secondaryHash(int key) {
        return 7 - (key % 7);
    }

    void doubleHashing(int key, int index) {
        int i = 1;
        int h2 = secondaryHash(key);
        while (table[(index + i * h2) % tableSize] != nullptr) {
            i++;
        }
        table[(index + i * h2) % tableSize] = new Node(key);
    }
};
#pragma once
#include "User_DLL.h"

// Universal hash function
template <typename K>
size_t universalHash(const K& key, size_t tableSize, size_t a, size_t b, size_t prime) {
    size_t keyVal =  hash<K>{}(key);
    return ((a * keyVal + b) % prime) % tableSize;
}

// Hash table with double hashing for collision resolution
template <typename K, typename V>
class HashTableDoubleHashing {
private:
    struct HashEntry {
        K key;
        V value;
        bool isActive;
        HashEntry() : isActive(false) {}
        HashEntry(const K& k, const V& v) : key(k), value(v), isActive(true) {}
    };

     vector<HashEntry> table;
    size_t size;
    size_t capacity;
    size_t prime;
    size_t a1, b1; // For first hash function
    size_t a2, b2; // For second hash function

    size_t hash1(const K& key) const {
        return universalHash(key, capacity, a1, b1, prime);
    }

    size_t hash2(const K& key) const {
        return 1 + (universalHash(key, capacity - 1, a2, b2, prime) % (capacity - 1));
    }

    void rehash() {
         vector<HashEntry> oldTable = table;
        capacity = nextPrime(2 * capacity);
        table.clear();
        table.resize(capacity);
        size = 0;

        for (const auto& entry : oldTable) {
            if (entry.isActive) {
                insert(entry.key, entry.value);
            }
        }
    }

    size_t nextPrime(size_t n) const {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    bool isPrime(size_t n) const {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (size_t i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

public:
    HashTableDoubleHashing(size_t initialCapacity = 101)
        : capacity(nextPrime(initialCapacity)), size(0), prime(4294967291) {
        table.resize(capacity);
        // Initialize random hash function parameters
        a1 = rand() % (prime - 1) + 1;
        b1 = rand() % prime;
        a2 = rand() % (prime - 1) + 1;
        b2 = rand() % prime;
    }

    bool insert(const K& key, const V& value) {
        if (size >= capacity / 2) {
            rehash();
        }

        size_t index = hash1(key);
        size_t step = hash2(key);
        size_t initialIndex = index;
        size_t i = 0;

        while (table[index].isActive) {
            if (table[index].key == key) {
                table[index].value = value;
                return true;
            }
            i++;
            index = (initialIndex + i * step) % capacity;
            if (i >= capacity) return false;
        }

        table[index] = HashEntry(key, value);
        size++;
        return true;
    }

    bool remove(const K& key) {
        size_t index = hash1(key);
        size_t step = hash2(key);
        size_t initialIndex = index;
        size_t i = 0;

        while (table[index].isActive) {
            if (table[index].key == key) {
                table[index].isActive = false;
                size--;
                return true;
            }
            i++;
            index = (initialIndex + i * step) % capacity;
            if (i >= capacity) break;
        }
        return false;
    }

    V* search(const K& key) {
        size_t index = hash1(key);
        size_t step = hash2(key);
        size_t initialIndex = index;
        size_t i = 0;

        while (table[index].isActive) {
            if (table[index].key == key) {
                return &table[index].value;
            }
            i++;
            index = (initialIndex + i * step) % capacity;
            if (i >= capacity) break;
        }
        return nullptr;
    }

    const V* search(const K& key) const {
        size_t index = hash1(key);
        size_t step = hash2(key);
        size_t initialIndex = index;
        size_t i = 0;

        while (table[index].isActive) {
            if (table[index].key == key) {
                return &table[index].value;
            }
            i++;
            index = (initialIndex + i * step) % capacity;
            if (i >= capacity) break;
        }
        return nullptr;
    }

    void clear() {
        for (auto& entry : table) {
            entry.isActive = false;
        }
        size = 0;
    }

    bool isEmpty() const {
        return size == 0;
    }
};

// Hash table with chaining for collision resolution
template <typename K, typename V>
class HashTableChaining {
private:
    struct HashNode {
        K key;
        V value;
        HashNode* next;
        HashNode(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };

     vector<HashNode*> table;
    size_t size;
    size_t capacity;
    size_t prime;
    size_t a, b;

    size_t hash(const K& key) const {
        return universalHash(key, capacity, a, b, prime);
    }

    void rehash() {
         vector<HashNode*> oldTable = table;
        capacity = nextPrime(2 * capacity);
        table.clear();
        table.resize(capacity, nullptr);
        size = 0;

        for (auto& chain : oldTable) {
            HashNode* node = chain;
            while (node) {
                insert(node->key, node->value);
                HashNode* temp = node;
                node = node->next;
                delete temp;
            }
        }
    }

    size_t nextPrime(size_t n) const {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    bool isPrime(size_t n) const {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (size_t i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

public:
    HashTableChaining(size_t initialCapacity = 101): capacity(nextPrime(initialCapacity)), size(0), prime(4294967291) {
        table.resize(capacity, nullptr);
        a = rand() % (prime - 1) + 1;
        b = rand() % prime;
    }

    ~HashTableChaining() {
        clear();
    }

    bool insert(const K& key, const V& value) {
        if (size >= capacity) {
            rehash();
        }

        size_t index = hash(key);
        HashNode* node = table[index];
        HashNode* prev = nullptr;

        while (node) {
            if (node->key == key) {
                node->value = value;
                return true;
            }
            prev = node;
            node = node->next;
        }

        HashNode* newNode = new HashNode(key, value);
        if (prev) {
            prev->next = newNode;
        }
        else {
            table[index] = newNode;
        }
        size++;
        return true;
    }

    bool remove(const K& key) {
        size_t index = hash(key);
        HashNode* node = table[index];
        HashNode* prev = nullptr;

        while (node) {
            if (node->key == key) {
                if (prev) {
                    prev->next = node->next;
                }
                else {
                    table[index] = node->next;
                }
                delete node;
                size--;
                return true;
            }
            prev = node;
            node = node->next;
        }
        return false;
    }

    V* search(const K& key) {
        size_t index = hash(key);
        HashNode* node = table[index];

        while (node) {
            if (node->key == key) {
                return &node->value;
            }
            node = node->next;
        }
        return nullptr;
    }

    void clear() {
        for (auto& chain : table) {
            HashNode* node = chain;
            while (node) {
                HashNode* temp = node;
                node = node->next;
                delete temp;
            }
            chain = nullptr;
        }
        size = 0;
    }

    bool isEmpty() const {
        return size == 0;
    }
};

// Hash table with linear probing for collision resolution (for group index)
template <typename K>
class HashTableLinearProbing {
private:
    struct GroupHashEntry {
        K key;
         vector<DLLNode<User>*> users;
        bool isActive;
        GroupHashEntry() : isActive(false) {}
        GroupHashEntry(const K& k) : key(k), isActive(true) {}
    };

     vector<GroupHashEntry> table;
    size_t size;
    size_t capacity;
    size_t prime;
    size_t a, b;

    size_t hash(const K& key) const {
        return universalHash(key, capacity, a, b, prime);
    }

    void rehash() {
         vector<GroupHashEntry> oldTable = table;
        capacity = nextPrime(2 * capacity);
        table.clear();
        table.resize(capacity);
        size = 0;

        for (const auto& entry : oldTable) {
            if (entry.isActive) {
                for (auto userNode : entry.users) {
                    insert(entry.key, userNode);
                }
            }
        }
    }

    size_t nextPrime(size_t n) const {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    bool isPrime(size_t n) const {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (size_t i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

public:
    HashTableLinearProbing(size_t initialCapacity = 101)
        : capacity(nextPrime(initialCapacity)), size(0), prime(4294967291) {
        table.resize(capacity);
        // Initialize random hash function parameters
        a = rand() % (prime - 1) + 1;
        b = rand() % prime;
    }

    bool insert(const K& key, DLLNode<User>* userNode) {
        if (size >= capacity / 2) {
            rehash();
        }

        size_t index = hash(key);
        size_t initialIndex = index;
        size_t i = 0;

        while (table[index].isActive) {
            if (table[index].key == key) {
                table[index].users.push_back(userNode);
                return true;
            }
            i++;
            index = (initialIndex + i) % capacity;
            if (i >= capacity) return false; // Table is full
        }

        table[index] = GroupHashEntry(key);
        table[index].users.push_back(userNode);
        size++;
        return true;
    }

    bool removeUser(const K& key, DLLNode<User>* userNode) {
        size_t index = hash(key);
        size_t initialIndex = index;
        size_t i = 0;

        while (table[index].isActive) {
            if (table[index].key == key) {
                auto& users = table[index].users;
                for (auto it = users.begin(); it != users.end(); ++it) {
                    if (*it == userNode) {
                        users.erase(it);
                        if (users.empty()) {
                            table[index].isActive = false;
                            size--;
                        }
                        return true;
                    }
                }
                return false; // User not found in this group
            }
            i++;
            index = (initialIndex + i) % capacity;
            if (i >= capacity) break;
        }
        return false; // Key not found
    }

    GroupHashEntry* search(const K& key) {
        size_t index = hash(key);
        size_t initialIndex = index;
        size_t i = 0;

        while (table[index].isActive) {
            if (table[index].key == key) {
                return &table[index];
            }
            i++;
            index = (initialIndex + i) % capacity;
            if (i >= capacity) break;
        }
        return nullptr;
    }

    void clear() {
        for (auto& entry : table) {
            entry.isActive = false;
            entry.users.clear();
        }
        size = 0;
    }

    bool isEmpty() const {
        return size == 0;
    }

     vector< pair<K,  vector<DLLNode<User>*>>> getAllEntries() const {
         vector< pair<K,  vector<DLLNode<User>*>>> result;
        for (const auto& entry : table) {
            if (entry.isActive) {
                result.emplace_back(entry.key, entry.users);
            }
        }
        return result;
    }
};

// Hash table with quadratic probing for collision resolution (for group index)
template <typename K>
class HashTableQuadraticProbing {
private:
    struct GroupHashEntry {
        K key;
         vector<DLLNode<User>*> users;
        bool isActive;
        GroupHashEntry() : isActive(false) {}
        GroupHashEntry(const K& k) : key(k), isActive(true) {}
    };

     vector<GroupHashEntry> table;
    size_t size;
    size_t capacity;
    size_t prime;
    size_t a, b;

    size_t hash(const K& key) const {
        return universalHash(key, capacity, a, b, prime);
    }

    void rehash() {
         vector<GroupHashEntry> oldTable = table;
        capacity = nextPrime(2 * capacity);
        table.clear();
        table.resize(capacity);
        size = 0;

        for (const auto& entry : oldTable) {
            if (entry.isActive) {
                for (auto userNode : entry.users) {
                    insert(entry.key, userNode);
                }
            }
        }
    }

    size_t nextPrime(size_t n) const {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    bool isPrime(size_t n) const {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (size_t i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

public:
    HashTableQuadraticProbing(size_t initialCapacity = 101)
        : capacity(nextPrime(initialCapacity)), size(0), prime(4294967291) {
        table.resize(capacity);
        // Initialize random hash function parameters
        a = rand() % (prime - 1) + 1;
        b = rand() % prime;
    }

    bool insert(const K& key, DLLNode<User>* userNode) {
        if (size >= capacity / 2) {
            rehash();
        }

        size_t index = hash(key);
        size_t initialIndex = index;
        size_t i = 0;

        while (table[index].isActive) {
            if (table[index].key == key) {
                table[index].users.push_back(userNode);
                return true;
            }
            i++;
            index = (initialIndex + i * i) % capacity;
            if (i >= capacity) return false; // Table is full
        }

        table[index] = GroupHashEntry(key);
        table[index].users.push_back(userNode);
        size++;
        return true;
    }

    bool removeUser(const K& key, DLLNode<User>* userNode) {
        size_t index = hash(key);
        size_t initialIndex = index;
        size_t i = 0;

        while (table[index].isActive) {
            if (table[index].key == key) {
                auto& users = table[index].users;
                for (auto it = users.begin(); it != users.end(); ++it) {
                    if (*it == userNode) {
                        users.erase(it);
                        if (users.empty()) {
                            table[index].isActive = false;
                            size--;
                        }
                        return true;
                    }
                }
                return false; // User not found in this group
            }
            i++;
            index = (initialIndex + i * i) % capacity;
            if (i >= capacity) break;
        }
        return false; // Key not found
    }

    GroupHashEntry* search(const K& key) {
        size_t index = hash(key);
        size_t initialIndex = index;
        size_t i = 0;

        while (table[index].isActive) {
            if (table[index].key == key) {
                return &table[index];
            }
            i++;
            index = (initialIndex + i * i) % capacity;
            if (i >= capacity) break;
        }
        return nullptr;
    }

    void clear() {
        for (auto& entry : table) {
            entry.isActive = false;
            entry.users.clear();
        }
        size = 0;
    }

    bool isEmpty() const {
        return size == 0;
    }

     vector< pair<K,  vector<DLLNode<User>*>>> getAllEntries() const {
         vector< pair<K,  vector<DLLNode<User>*>>> result;
        for (const auto& entry : table) {
            if (entry.isActive) {
                result.emplace_back(entry.key, entry.users);
            }
        }
        return result;
    }
};
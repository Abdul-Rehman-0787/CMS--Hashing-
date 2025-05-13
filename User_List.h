#pragma once
#include "Hashing.h"

class UserList {
private:
    DoublyLinkedList<User> users;
    HashTableDoubleHashing<int, DLLNode<User>*> userIDIndex;
    HashTableChaining<string, DLLNode<User>*> userNameIndex;
    HashTableChaining<string, DLLNode<User>*> emailIndex;
    HashTableLinearProbing<string> countryIndex;
    HashTableQuadraticProbing<string> typeIndex;

    bool userNameIndexActive;
    bool emailIndexActive;
    bool countryIndexActive;
    bool typeIndexActive;

public:
    UserList() : userNameIndexActive(false), emailIndexActive(false),
        countryIndexActive(false), typeIndexActive(false) {}

    void insertUser(const User& user) {
        DLLNode<User>* node = new DLLNode<User>(user);
        users.insertSorted(user);
        userIDIndex.insert(user.getUserID(), node);

        if (userNameIndexActive) {
            userNameIndex.insert(user.getUserName(), node);
        }
        if (emailIndexActive) {
            emailIndex.insert(user.getEmail(), node);
        }
        if (countryIndexActive) {
            countryIndex.insert(user.getCountry(), node);
        }
        if (typeIndexActive) {
            typeIndex.insert(user.getType(), node);
        }
    }

    User* searchUserByID(int userID) {
        DLLNode<User>** nodePtr = userIDIndex.search(userID);
        if (nodePtr) {
            return &((*nodePtr)->data);
        }
        return nullptr;
    }

    User* searchUserByName(const string& userName) {
        if (userNameIndexActive) {
            DLLNode<User>** nodePtr = userNameIndex.search(userName);
            if (nodePtr) {
                return &((*nodePtr)->data);
            }
        }
        else {
            DLLNode<User>* current = users.getHead();
            while (current) {
                if (current->data.getUserName() == userName) {
                    return &(current->data);
                }
                current = current->next;
            }
        }
        return nullptr;
    }

    User* searchUserByEmail(const string& email) {
        if (emailIndexActive) {
            DLLNode<User>** nodePtr = emailIndex.search(email);
            if (nodePtr) {
                return &((*nodePtr)->data);
            }
        }
        else {
            DLLNode<User>* current = users.getHead();
            while (current) {
                if (current->data.getEmail() == email) {
                    return &(current->data);
                }
                current = current->next;
            }
        }
        return nullptr;
    }

    bool deleteUserByID(int userID) {
        DLLNode<User>** nodePtr = userIDIndex.search(userID);
        if (!nodePtr || !(*nodePtr)) {
            return false;
        }

        DLLNode<User>* node = *nodePtr;
        User user1 = node->data;

        userIDIndex.remove(userID);
        if (userNameIndexActive) {
            userNameIndex.remove(user1.getUserName());
        }
        if (emailIndexActive) {
            emailIndex.remove(user1.getEmail());
        }
        if (countryIndexActive) {
            countryIndex.removeUser(user1.getCountry(), node);
        }
        if (typeIndexActive) {
            typeIndex.removeUser(user1.getType(), node);
        }
        return users.deleteNodeByUserID(userID);
        return users.deleteNode(node);
    }

    void printAllUsers() const {
        users.printAll();
    }

    void createUserNameIndex() {
        if (userNameIndexActive) return;

        userNameIndex.clear();
        DLLNode<User>* current = users.getHead();
        while (current) {
            userNameIndex.insert(current->data.getUserName(), current);
            current = current->next;
        }
        userNameIndexActive = true;
    }

    void deleteUserNameIndex() {
        userNameIndex.clear();
        userNameIndexActive = false;
    }

    void createEmailIndex() {
        if (emailIndexActive) return;

        emailIndex.clear();
        DLLNode<User>* current = users.getHead();
        while (current) {
            emailIndex.insert(current->data.getEmail(), current);
            current = current->next;
        }
        emailIndexActive = true;
    }

    void deleteEmailIndex() {
        emailIndex.clear();
        emailIndexActive = false;
    }

    void createCountryIndex() {
        if (countryIndexActive) return;

        countryIndex.clear();
        DLLNode<User>* current = users.getHead();
        while (current) {
            countryIndex.insert(current->data.getCountry(), current);
            current = current->next;
        }
        countryIndexActive = true;
    }

    void deleteCountryIndex() {
        countryIndex.clear();
        countryIndexActive = false;
    }

    void createTypeIndex() {
        if (typeIndexActive) return;

        typeIndex.clear();
        DLLNode<User>* current = users.getHead();
        while (current) {
            typeIndex.insert(current->data.getType(), current);
            current = current->next;
        }
        typeIndexActive = true;
    }

    void deleteTypeIndex() {
        typeIndex.clear();
        typeIndexActive = false;
    }

    vector<User> getUsersByCountry(const string& country) {
        vector<User> result;
        if (!countryIndexActive) return result;

        auto entry = countryIndex.search(country);
        if (entry) {
            for (DLLNode<User>* userNode : entry->users) {
                result.push_back(userNode->data);
            }
        }
        return result;
    }

    vector<User> getUsersByType(const string& type) {
        vector<User> result;
        if (!typeIndexActive) return result;

        auto entry = typeIndex.search(type);
        if (entry) {
            for (DLLNode<User>* userNode : entry->users) {
                result.push_back(userNode->data);
            }
        }
        return result;
    }

    void displayIndices() const {
        cout << "Active Indices:\n";
        cout << "1. UserID Index (Always active)\n";
        cout << "2. UserName Index: " << (userNameIndexActive ? "Active" : "Inactive") << "\n";
        cout << "3. Email Index: " << (emailIndexActive ? "Active" : "Inactive") << "\n";
        cout << "4. Country Index: " << (countryIndexActive ? "Active" : "Inactive") << "\n";
        cout << "5. Type Index: " << (typeIndexActive ? "Active" : "Inactive") << "\n";
    }
};
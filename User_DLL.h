#pragma once
#include "Class_User.h"

// Node for doubly linked list
template<typename T>
struct DLLNode {
    T data;
    DLLNode* prev;
    DLLNode* next;

    DLLNode(const T& val) : data(val), prev(nullptr), next(nullptr) {}
};

// Doubly Linked List class
template<typename T>
class DoublyLinkedList {
private:
    DLLNode<T>* head;
    DLLNode<T>* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        clear();
    }

    void insertEnd(const T& val) {
        DLLNode<T>* newNode = new DLLNode<T>(val);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void insertSorted(const T& val) {
        DLLNode<T>* newNode = new DLLNode<T>(val);

        if (!head) {
            head = tail = newNode;
        }
        else if (val < head->data) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        else {
            DLLNode<T>* current = head;
            while (current->next && current->next->data < val) {
                current = current->next;
            }

            newNode->next = current->next;
            newNode->prev = current;
            if (current->next) {
                current->next->prev = newNode;
            }
            else {
                tail = newNode;
            }
            current->next = newNode;
        }
        size++;
    }

    bool deleteNodeByUserID(int userID) {
        DLLNode<User>* current = head;

        while (current != nullptr) {
            if (current->data.getUserID() == userID) {
                return deleteNode(current);
            }
            current = current->next;
        }
        return false;
    }

    bool deleteNode(DLLNode<T>* node) {
        if (!node) return false;

        if (node == head && node == tail) {
            head = tail = nullptr;
        }
        else if (node == head) {
            head = head->next;
            if (head) head->prev = nullptr;
        }
        else if (node == tail) {
            tail = tail->prev;
            if (tail) tail->next = nullptr;
        }
        else {
            if (node->prev && node->next) {
                node->prev->next = node->next;
                node->next->prev = node->prev;
            }
            else {
                return false;
            }
        }

        delete node;
        size--;
        return true;
    }

    DLLNode<T>* search(const T& val) const {
        DLLNode<T>* current = head;
        while (current) {
            if (current->data == val) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void clear() {
        while (head) {
            DLLNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }

    int getSize() const { return size; }
    DLLNode<T>* getHead() const { return head; }
    DLLNode<T>* getTail() const { return tail; }

    void printAll() const {
        DLLNode<T>* current = head;
        while (current) {
            cout << current->data << "\n<-------------------------------->\n";
            current = current->next;
        }
    }
};
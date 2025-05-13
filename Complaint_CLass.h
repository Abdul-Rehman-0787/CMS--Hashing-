#pragma once
#include "User_List.h"

class Complaint {
private:
    int complaintID;
    int userID;
    string description;
    int priorityValue;
    string userType;

public:
    Complaint(int id = 0, int uid = 0, const string& desc = "", const string& type = "NEW")
        : complaintID(id), userID(uid), description(desc), userType(type) {
        if (userType == PLATINUM) priorityValue = 0;
        else if (userType == GOLD) priorityValue = 1;
        else if (userType == SILVER) priorityValue = 2;
        else if (userType == NEW) priorityValue = 3;
        else priorityValue = 4;
    }

    int getComplaintID() const { return complaintID; }
    int getUserID() const { return userID; }
    string getDescription() const { return description; }
    int getPriorityValue() const { return priorityValue; }
    string getUserType() const { return userType; }

    bool operator<(const Complaint& other) const {
        if (priorityValue != other.priorityValue)
            return (priorityValue > other.priorityValue);
        return (complaintID > other.complaintID);
    }

    friend ostream& operator<<(ostream& os, const Complaint& complaint);
};

ostream& operator<<(ostream& os, const Complaint& complaint) {
    os << "\nComplaint ID : \t" << complaint.getComplaintID()
        << "\nUser ID      : \t" << complaint.getUserID()
        << "\nUser Type    : \t" << complaint.getUserType()
        << "\nDescription  : \t" << complaint.getDescription()
        << "\nPriority     : \t" << complaint.getPriorityValue() << "\n";
    return os;
}

// ComplaintQueue class
class ComplaintQueue {
private:
    vector<Complaint> heap;
    HashTableDoubleHashing<int, int> userIndex; // maps userID -> index in heap
    int nextComplaintID;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[parent] < heap[index]) {
                swap(heap[parent], heap[index]);
                updateIndex(parent);
                updateIndex(index);
                index = parent;
            }
            else break;
        }
    }

    void heapifyDown(int index) {
        int size = heap.size();
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < size && heap[largest] < heap[left]) largest = left;
            if (right < size && heap[largest] < heap[right]) largest = right;

            if (largest != index) {
                swap(heap[index], heap[largest]);
                updateIndex(index);
                updateIndex(largest);
                index = largest;
            }
            else break;
        }
    }

    void updateIndex(int index) {
        if (index >= 0 && index < heap.size()) {
            userIndex.insert(heap[index].getUserID(), index);
        }
    }

public:
    ComplaintQueue() : nextComplaintID(1) {}

    void registerComplaint(int userID, const string& description, const string& userType) {
        Complaint complaint(nextComplaintID++, userID, description, userType);
        heap.push_back(complaint);
        userIndex.insert(userID, heap.size() - 1);
        heapifyUp(heap.size() - 1);
    }

    bool serviceComplaint(Complaint& result) {
        if (heap.empty()) return false;

        result = heap[0];
        userIndex.remove(result.getUserID());

        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty()) {
            updateIndex(0);
            heapifyDown(0);
        }

        return true;
    }

    void increasePriority(int userID) {
        int* indexPtr = userIndex.search(userID);
        if (indexPtr == nullptr) return;

        int index = *indexPtr;
        if (index < 0 || index >= heap.size()) return;

        Complaint oldComplaint = heap[index];
        heap[index] = Complaint(
            oldComplaint.getComplaintID(),
            oldComplaint.getUserID(),
            oldComplaint.getDescription(),
            PLATINUM
        );

        heapifyUp(index);
    }

    vector<Complaint> getComplaintsByUser(int userID) const {
        vector<Complaint> result;
        const int* indexPtr = userIndex.search(userID);

        if (indexPtr) {
            int index = *indexPtr;
            if (index >= 0 && index < static_cast<int>(heap.size()) ){
                if (heap[index].getUserID() == userID) {
                    result.push_back(heap[index]);
                }
            }
        }
        return result;
    }

    void printAll() const {
        for (const auto& complaint : heap) {
            cout << complaint << "\n";
        }
    }

    bool isEmpty() const {
        return heap.empty();
    }

    void printAllComplaints(UserList& userList) const {
        cout << "\n=== ALL COMPLAINTS WITH USER DETAILS ===\n";
        cout << "======================================\n\n";

        for (const auto& complaint : heap) {
            User* user = userList.searchUserByID(complaint.getUserID());

            cout << "Complaint #" << complaint.getComplaintID() << "\n";
            cout << "--------------------------------------\n";

            if (user) {
                cout << "User: " << user->getUserName() << "\n";
                cout << "Email: " << user->getEmail() << "\n";
                cout << "From: " << user->getCountry() << " (" << user->getType() << ")\n";
            }
            else {
                cout << "User details not available\n";
            }

            cout << "\nPriority: " << complaint.getPriorityValue();
            cout << " (" << complaint.getUserType() << ")\n";
            cout << "Description:\n" << complaint.getDescription() << "\n";

            cout << "--------------------------------------\n\n";
        }

        cout << "Total complaints: " << heap.size() << "\n";
        cout << "======================================\n";
    }
};
#pragma once
#pragma once
#include "Complaint_Class.h"

class CustomerServiceModule {
private:
    UserList userList;
    ComplaintQueue complaintQueue;

public:
    void printAllUsers() {
        userList.printAllUsers();
    }

    void registerUserDirect(const User& user) {
        userList.insertUser(user);
        cout << "User " << user.getUserID() << " registered: " << user.getUserName() << endl;
    }

    UserList& getUserList() {
        return userList;
    }

    void initializeWithDummyUsers() {
        userList.createUserNameIndex();
        userList.createEmailIndex();
        userList.createCountryIndex();
        userList.createTypeIndex();

        struct DummyUser {
            int id;
            string firstName;
            string lastName;
            string country;
            string type;
        };

        DummyUser dummyData[20] = {
            {1, "Muhammad", "Khan", "Pakistan", PLATINUM},
            {2, "Ahmad", "Ahmad", "USA", GOLD},
            {3, "Ali", "Malik", "Saudi Arabia", SILVER},
            {4, "Omar", "Hussain", "Turkey", REGULAR},
            {5, "Yousaf", "Abdul", "Pakistan", NEW},
            {6, "Ibrahim", "Rahman", "USA", PLATINUM},
            {7, "Mustafa", "Iqbal", "Saudi Arabia", GOLD},
            {8, "Abdullah", "Farooq", "Turkey", SILVER},
            {9, "Fatima", "Saleh", "UAE", REGULAR},
            {10, "Aisha", "Kamal", "Pakistan", NEW},
            {11, "Mariyam", "Nasir", "USA", PLATINUM},
            {12, "Zainab", "Qureshi", "Saudi Arabia", GOLD},
            {13, "Hafsa", "Sheikh", "Turkey", SILVER},
            {14, "Khadija", "Mirza", "USA", REGULAR},
            {15, "Amina", "Ansari", "Pakistan", NEW},
            {16, "Sumayya", "Siddiqui", "USA", PLATINUM},
            {17, "Hamza", "Alam", "Saudi Arabia", GOLD},
            {18, "Bilal", "Raza", "Turkey", SILVER},
            {19, "Usman", "Baig", "Pakistan", REGULAR},
            {20, "Hassan", "Shah", "USA", NEW}
        };

        for (int i = 0; i < 20; i++) {
            DummyUser& d = dummyData[i];
            string email = d.firstName + "." + d.lastName + "@example.com";
            User user(d.id, d.firstName + " " + d.lastName, email, d.country, d.type);
            registerUserDirect(user);
        }
        cout << "20 dummy users inserted successfully!\n";
    }

    void registerUser() {
        User user1;
        cin >> user1;
        if (SearchByUserId_Bool(user1.getUserID())) {
            cout << "User ID is Already Registered!!!\n";
        }
        else {
            userList.insertUser(user1);
            cout << "User registered successfully!\n";
        }
    }

    bool SearchByUserId_Bool(int id) {
        User* user = userList.searchUserByID(id);
        if (user) {
            return true;
        }
        return false;
    }

    void searchUserByID() {
        int userID;
        cout << "Enter User ID to search: ";
        cin >> userID;

        User* user = userList.searchUserByID(userID);
        if (user) {
            cout << "User found:\n" << *user;
        }
        else {
            cout << "User not found!\n";
        }
    }

    void searchUserByName() {
        string userName;
        cout << "Enter User Name to search: ";
        cin >> userName;

        User* user = userList.searchUserByName(userName);
        if (user) {
            cout << "User found:\n" << *user;
        }
        else {
            cout << "User not found!\n";
        }
    }

    void searchUserByEmail() {
        string email;
        cout << "Enter Email to search: ";
        cin >> email;

        User* user = userList.searchUserByEmail(email);
        if (user) {
            cout << "User found:\n" << *user;
        }
        else {
            cout << "User not found!\n";
        }
    }

    void deleteUser() {
        int userID;
        cout << "Enter User ID to delete: ";
        cin >> userID;

        if (userList.deleteUserByID(userID)) {
            cout << "User deleted successfully!\n";
        }
        else {
            cout << "User not found!\n";
        }
    }

    void printAllComplaintsWithDetails() {
        complaintQueue.printAllComplaints(userList);
    }

    void createUserNameIndex() {
        userList.createUserNameIndex();
        cout << "UserName index created successfully!\n";
    }

    void deleteUserNameIndex() {
        userList.deleteUserNameIndex();
        cout << "UserName index deleted successfully!\n";
    }

    void createEmailIndex() {
        userList.createEmailIndex();
        cout << "Email index created successfully!\n";
    }

    void deleteEmailIndex() {
        userList.deleteEmailIndex();
        cout << "Email index deleted successfully!\n";
    }

    void createCountryIndex() {
        userList.createCountryIndex();
        cout << "Country index created successfully!\n";
    }

    void deleteCountryIndex() {
        userList.deleteCountryIndex();
        cout << "Country index deleted successfully!\n";
    }

    void createTypeIndex() {
        userList.createTypeIndex();
        cout << "Type index created successfully!\n";
    }

    void deleteTypeIndex() {
        userList.deleteTypeIndex();
        cout << "Type index deleted successfully!\n";
    }

    void displayIndices() {
        userList.displayIndices();
    }

    void listUsersByCountry() {
        string country;
        cout << "Enter country: ";
        cin >> country;

        vector<User> users = userList.getUsersByCountry(country);
        if (users.empty()) {
            cout << "No users found from " << country << "\n";
        }
        else {
            cout << "Users from " << country << ":\n";
            for (const auto& user : users) {
                cout << user << "\n";
            }
        }
    }

    void listUsersByType() {
        int type;
        cout << "Enter type (0: Platinum, 1: Gold, 2: Silver, 3: Regular, 4: New): ";
        cin >> type;

        string typeStr;
        if (type == 0) typeStr = PLATINUM;
        else if (type == 1) typeStr = GOLD;
        else if (type == 2) typeStr = SILVER;
        else if (type == 3) typeStr = REGULAR;
        else typeStr = NEW;

        vector<User> users = userList.getUsersByType(typeStr);
        if (users.empty()) {
            cout << "No users found of this type\n";
        }
        else {
            cout << "Users of type " << typeStr << ":\n";
            for (const auto& user : users) {
                cout << user << "\n";
            }
        }
    }

    void registerComplaint() {
        int userID;
        cout << "Enter your User ID: ";
        cin >> userID;

        User* user = userList.searchUserByID(userID);
        if (!user) {
            cout << "User not found!\n";
            return;
        }

        string description;
        cout << "Enter complaint description: ";
        cin.ignore();
        getline(cin, description);

        complaintQueue.registerComplaint(userID, description, user->getType());
        cout << "Complaint registered successfully!\n";
    }

    void serviceComplaint() {
        Complaint result;
        if (complaintQueue.serviceComplaint(result)) {
            cout << "Servicing complaint:\n" << result;
        }
        else {
            cout << "No complaints to service!\n";
        }
    }

    void increaseComplaintPriority() {
        int userID;
        cout << "Enter User ID to increase priority: ";
        cin >> userID;

        complaintQueue.increasePriority(userID);
        cout << "Complaint priority increased successfully!\n";
    }

    void displayUserComplaints() {
        int userID;
        cout << "Enter User ID: ";
        cin >> userID;

        vector<Complaint> complaints = complaintQueue.getComplaintsByUser(userID);
        if (complaints.empty()) {
            cout << "No complaints found for this user\n";
        }
        else {
            cout << "Complaints for user " << userID << ":\n";
            for (const auto& complaint : complaints) {
                cout << complaint << "\n";
            }
        }
    }

    void displayCountryComplaints() {
        string country;
        cout << "Enter country: ";
        cin >> country;

        vector<User> users = userList.getUsersByCountry(country);
        if (users.empty()) {
            cout << "No users found from " << country << "\n";
            return;
        }

        cout << "Complaints from " << country << ":\n";
        for (const auto& user : users) {
            vector<Complaint> complaints = complaintQueue.getComplaintsByUser(user.getUserID());
            if (!complaints.empty()) {
                cout << "User " << user.getUserID() << " (" << user.getUserName() << "):\n";
                for (const auto& complaint : complaints) {
                    cout << complaint << "\n";
                }
            }
        }
    }

    void run() {
        while (true) {
            system("pause");
            system("cls");
            cout << "\x1b[33m";
            cout << "\n\t\t\t\t\t\t*********************************";
            cout << "\n\t\t\t\t\t\t*   Customer Service Module     *";
            cout << "\n\t\t\t\t\t\t*********************************";
            cout << "\n\n\n\t\t\t\t\t\t1. User Management\n";
            cout << "\t\t\t\t\t\t2. Index Management\n";
            cout << "\t\t\t\t\t\t3. Complaint Management\n";
            cout << "\t\t\t\t\t\t4. Exit\n";
            cout << "Enter your choice : \t\t";

            int choice;
            cin >> choice;
            cout << "\x1b[37m";
            switch (choice) {
            case 1: {
                userManagementMenu();
                break;
            }
            case 2: {
                indexManagementMenu();
                break;
            }
            case 3: {
                complaintManagementMenu();
                break;
            }
            case 4: {
                return;
            }
            default: {
                cout << "Invalid choice!\n";
            }
            }
        }
    }

    void userManagementMenu() {
        while (true) {
            cout << "\x1b[34m";
            system("pause");
            system("cls");
            cout << "\n\t\t\t\t\t\t*********************************";
            cout << "\n\t\t\t\t\t\t*       User Management         *";
            cout << "\n\t\t\t\t\t\t*********************************";
            cout << "\n\n";
            cout << "\t\t\t\t\t\t1. Register User\n";
            cout << "\t\t\t\t\t\t2. Search User by ID\n";
            cout << "\t\t\t\t\t\t3. Search User by Name\n";
            cout << "\t\t\t\t\t\t4. Search User by Email\n";
            cout << "\t\t\t\t\t\t5. Delete User\n";
            cout << "\t\t\t\t\t\t6. Print All Users\n";
            cout << "\t\t\t\t\t\t7. Back to Main Menu\n";
            cout << "Enter your choice : \t\t";

            int choice;
            cin >> choice;
            cout << "\x1b[37m";
            switch (choice) {
            case 1: {
                registerUser();
                break;
            }
            case 2: {
                searchUserByID();
                break;
            }
            case 3: {
                searchUserByName();
                break;
            }
            case 4: {
                searchUserByEmail();
                break;
            }
            case 5: {
                deleteUser();
                break;
            }
            case 6: {
                printAllUsers();
                break;
            }
            case 7: {
                return;
            }
            default: {
                cout << "Invalid choice!\n";
            }
            }
        }
    }

    void indexManagementMenu() {
        while (true) {
            cout << "\x1b[35m";
            system("pause");
            system("cls");
            cout << "\n\t\t\t\t\t\t*********************************";
            cout << "\n\t\t\t\t\t\t*       Index Management        *";
            cout << "\n\t\t\t\t\t\t*********************************";
            cout << "\n\n";
            cout << "\t\t\t\t\t\t1. Create UserName Index\n";
            cout << "\t\t\t\t\t\t2. Delete UserName Index\n";
            cout << "\t\t\t\t\t\t3. Create Email Index\n";
            cout << "\t\t\t\t\t\t4. Delete Email Index\n";
            cout << "\t\t\t\t\t\t5. Create Country Index\n";
            cout << "\t\t\t\t\t\t6. Delete Country Index\n";
            cout << "\t\t\t\t\t\t7. Create Type Index\n";
            cout << "\t\t\t\t\t\t8. Delete Type Index\n";
            cout << "\t\t\t\t\t\t9. Display Active Indices\n";
            cout << "\t\t\t\t\t\t10. List Users by Country\n";
            cout << "\t\t\t\t\t\t11. List Users by Type\n";
            cout << "\t\t\t\t\t\t12. Back to Main Menu\n";
            cout << "Enter your choice : \t\t";

            int choice;
            cin >> choice;
            cout << "\x1b[37m";
            switch (choice) {
            case 1: {
                createUserNameIndex();
                break;
            }
            case 2: {
                deleteUserNameIndex();
                break;
            }
            case 3: {
                createEmailIndex();
                break;
            }
            case 4: {
                deleteEmailIndex();
                break;
            }
            case 5: {
                createCountryIndex();
                break;
            }
            case 6: {
                deleteCountryIndex();
                break;
            }
            case 7: {
                createTypeIndex();
                break;
            }
            case 8: {
                deleteTypeIndex();
                break;
            }
            case 9: {
                displayIndices();
                break;
            }
            case 10: {
                listUsersByCountry();
                break;
            }
            case 11: {
                listUsersByType();
                break;
            }
            case 12: {
                return;
            }
            default: {
                cout << "Invalid choice!\n";
            }
            }
        }
    }

    void complaintManagementMenu() {
        while (true) {
            cout << "\x1b[36m";
            system("pause");
            system("cls");
            cout << "\n\t\t\t\t\t\t*********************************";
            cout << "\n\t\t\t\t\t\t*     Complaint Management      *";
            cout << "\n\t\t\t\t\t\t*********************************";
            cout << "\n\n\t\t\t\t\t\t1. Register Complaint\n";
            cout << "\t\t\t\t\t\t2. Service Complaint\n";
            cout << "\t\t\t\t\t\t3. Increase Complaint Priority\n";
            cout << "\t\t\t\t\t\t4. Display User Complaints\n";
            cout << "\t\t\t\t\t\t5. Display Country Complaints\n";
            cout << "\t\t\t\t\t\t6. Display ALL Complaints\n";
            cout << "\t\t\t\t\t\t7. Back to Main Menu\n";
            cout << "Enter your choice : \t\t";

            int choice;
            cin >> choice;
            cout << "\x1b[37m";
            switch (choice) {
            case 1: {
                registerComplaint();
                break;
            }
            case 2: {
                serviceComplaint();
                break;
            }
            case 3: {
                increaseComplaintPriority();
                break;
            }
            case 4: {
                displayUserComplaints();
                break;
            }
            case 5: {
                displayCountryComplaints();
                break;
            }
            case 6: {
                printAllComplaintsWithDetails();
                break;
            }
            case 7: {
                return;
            }
            default: cout << "Invalid choice!\n";
            }
        }
    }
};
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

// User type constants
const string PLATINUM = "Platinum";
const string GOLD = "Gold";
const string SILVER = "Silver";
const string REGULAR = "Regular";
const string NEW = "New";

// User class
class User {
private:
    int userID;
    string userName;
    string email;
    string country;
    string type;

public:
    User(int id = 0, string name = "\0", string em = "\0", string cntry = "\0", string t = NEW) : userID(id), userName(name), email(em), country(cntry), type(t) {
    }

    // Getters
    int getUserID() const { return userID; }
    string getUserName() const { return userName; }
    string getEmail() const { return email; }
    string getCountry() const { return country; }
    string getType() const { return type; }

    // Setters
    void setUserID(int id) { userID = id; }
    void setUserName(const string& name) { userName = name; }
    void setEmail(const string& em) { email = em; }
    void setCountry(const string& cntry) { country = cntry; }
    void setType(const string& t) { type = t; }

    // Comparison operators
    bool operator<(const User& other) const { return (this->userID < other.userID); }
    bool operator>(const User& other) const { return (this->userID > other.userID); }
    bool operator==(const User& other) const { return (this->userID == other.userID); }

    friend ostream& operator<<(ostream& os, const User& user);
    friend istream& operator>>(istream& is, User& user);
};

ostream& operator<<(ostream& os, const User& user) {
    os << "User ID    : \t" << user.userID << "\n"
        << "User Name  : \t" << user.userName << "\n"
        << "Email      : \t" << user.email << "\n"
        << "Country    : \t" << user.country << "\n"
        << "Type       : \t" << user.type << "\n";
    return os;
}

istream& operator>>(istream& is, User& user) {
    cout << "Enter User ID   : \t";
    is >> user.userID;
    cout << "Enter User Name : \t";
    is >> user.userName;
    cout << "Enter Email     : \t";
    is >> user.email;
    cout << "Enter Country   : \t";
    is >> user.country;

    cout << "Enter User Type (0: Platinum, 1: Gold, 2: Silver, 3: Regular, 4: New): ";
    int type;
    is >> type;

    if (type == 0) user.type = PLATINUM;
    else if (type == 1) user.type = GOLD;
    else if (type == 2) user.type = SILVER;
    else if (type == 3) user.type = REGULAR;
    else user.type = NEW;

    return is;
}
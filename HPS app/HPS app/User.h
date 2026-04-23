#ifndef USER_H
#define USER_H
#include <string>
using namespace std;
class User {
protected:
    int userID;
    string username;
	string password;
    string role;
public:
    virtual void displayDashboard() = 0;
};

class Admin : public User {
public:
    void displayDashboard() override {
        // UI Logic for Admin Hub will go here
    }
};

class Doctor : public User {
public:
    void displayDashboard() override {
        // UI Logic for Clinical Dashboard will go here
    }
};
#endif

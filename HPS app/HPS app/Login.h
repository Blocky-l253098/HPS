#ifndef LOGIN_H
#define LOGIN_H

#include <string>
using namespace std;

class Login {
private:
    int userID;
    string username;
    string password;
    string userRole;

public:
    Login() : userID(-1), username(""), password(""), userRole("None") {}

    void setUserID(int id) {
        userID = id;
    }

    int getUserID() const {
        return userID;
    }

    void setUsername(string user) {
        username = user;
    }

    void setPassword(string pass) {
        password = pass;
    }

    string getUsername() const {
        return username;
    }

    string getPassword() const {
        return password;
    }

    string getUserRole() const {
        return userRole;
    }

    void setUserRole(string role) {
        userRole = role;
    }

    bool isValidated() const {
        return userRole != "None";
    }

    void clearCredentials() {
        userID = -1;
        username = "";
        password = "";
        userRole = "None";
    }
};

#endif

#pragma once
using namespace System;

public ref class SessionManager {
public:
    static int CurrentUserId;
    static String^ CurrentUserName;
    static String^ UserRole; // "Admin" or "Doctor"

    static void StartSession(int id, String^ name, String^ role) {
        CurrentUserId = id;
        CurrentUserName = name;
        UserRole = role;
    }

    static void EndSession() {
        CurrentUserId = 0;
        CurrentUserName = nullptr;
        UserRole = nullptr;
    }
};
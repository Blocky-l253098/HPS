#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <iostream>
#include "sqlite3.h"
#include <string>
using namespace std;
class DatabaseManager{
	sqlite3* DB;
	char* errorMessage;
public:
	bool Connect() {
		if(sqlite3_open("hospital.db", &DB)== SQLITE_OK) {
			return true;
		}
		return false;
	}
	void Disconnect() {
		sqlite3_close(DB);
	}
	bool AddPatient(string name, string history) {
		if (DB) {
			string sqlQuery = "INSERT INTO Patients (Name, History) VALUES ('" + name + "', '" + history + "');";
			return(sqlite3_exec(DB, sqlQuery.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK);
		}
		else {
			return false;
		}
	}
	bool AddUsername(string username, string password, string role) {
		if (DB) {
			string sqlQuery = "INSERT INTO Users (Username, Password, Role) VALUES ('" + username + "', '" + password + "', '" + role + "');";
			return(sqlite3_exec(DB, sqlQuery.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK);
		}
		return false;
	}
	string ValidateUser(string username, string password) {
		string role = "None";
		string sqlQuery = "SELECT Role FROM Users WHERE Username='" + username + "' AND Password='" + password + "';";
		sqlite3_stmt* stmt;
		if (sqlite3_prepare_v2(DB, sqlQuery.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
			if (sqlite3_step(stmt) == SQLITE_ROW) {
				role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
			}
			sqlite3_finalize(stmt);
		}
		return role;
	}
	bool AddDoctor(string name, string specialty,string salary,bool isAvailable) {
		if (DB) {
			string sqlQuery = "INSERT INTO Doctors (Name, Specialty, Salary, IsAvailable) VALUES ('" + name + "', '" + specialty + "', '" + salary + "', '" + (isAvailable ? "1" : "0") + "');";
			return(sqlite3_exec(DB, sqlQuery.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK);
		}
		return false;
	}
	bool CheckConflict(int doctorId, string time) {
		string sql = "SELECT COUNT(*) FROM Appointments WHERE DoctorId=" + to_string(doctorId) + " AND Time='" + time + "';";
		int count = 0;
		sqlite3_stmt* stmt;
		if(sqlite3_prepare_v2(DB,sql.c_str(),-1, &stmt, nullptr) == SQLITE_OK) {
			if(sqlite3_step(stmt) == SQLITE_ROW) {
				count = sqlite3_column_int(stmt, 0);
			}
			sqlite3_finalize(stmt);
		}
		if(count>0) {
			return true;
		}
		return false;	
	}
	bool BookAppointment(int patientId, int doctorId, string time,bool isSurgury) {
		string surg;
		if(isSurgury) {
			surg = "1";
		}
		else {
			surg = "0";
		}
		string sqlQuery = "INSERT INTO Appointments (PatientId, DoctorId, Time, IsSurgery) VALUES (" + to_string(patientId) + ", " + to_string(doctorId) + ", '" + time + "', " + surg + ");";

		return (sqlite3_exec(DB, sqlQuery.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK);
	}
	bool GenerateBill(int patientId, double amount,bool paid) {
		string sqlQuery = "INSERT INTO Billing (PatientId, Amount, Paid) VALUES (" + to_string(patientId) + ", " + to_string(amount) + "," + (paid ? "1" : "0") + ");";
		return(sqlite3_exec(DB, sqlQuery.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK);
	}
	bool UpdateBedStatus(int patientId, string bedId) {
		string sqlQuery = "UPDATE Patients SET AssignedBed='" + bedId + "' WHERE PatientID=" + to_string(patientId) + ";";
		return(sqlite3_exec(DB, sqlQuery.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK);
	}

};
#endif

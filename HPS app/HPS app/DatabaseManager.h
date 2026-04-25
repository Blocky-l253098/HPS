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
	bool CheckConflict(int doctorId, string StartTime, string EndTime, bool isSurgery) {
		string oppositeType = isSurgery ? "0" : "1";
		string sql = "SELECT COUNT(*) FROM Appointments WHERE DoctorId=" + to_string(doctorId) + 
					 " AND IsSurgery=" + oppositeType + 
					 " AND (StartTime < '" + EndTime + "' AND EndTime > '" + StartTime + "');";
		int count = 0;
		sqlite3_stmt* stmt;
		if(sqlite3_prepare_v2(DB,sql.c_str(),-1, &stmt, nullptr) == SQLITE_OK) {
			if(sqlite3_step(stmt) == SQLITE_ROW) {
				count = sqlite3_column_int(stmt, 0);
			}
			sqlite3_finalize(stmt);
		}
		
		return (count > 0);	
	}
	bool BookAppointment(int patientId, int doctorId, string Starttime,string EndTime,bool isSurgury) {
		string surg;
		if(isSurgury) {
			surg = "1";
		}
		else {
			surg = "0";
		}
		string sqlQuery = "INSERT INTO Appointments (PatientId, DoctorId, StartTime, EndTime, IsSurgery) VALUES (" + to_string(patientId) + ", " + to_string(doctorId) + ", '" + Starttime + "', '" + EndTime + "', " + surg + ");";

		return (sqlite3_exec(DB, sqlQuery.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK);
	}
	bool GenerateBill(int patientId, double amount,bool paid) {
		string sqlQuery = "INSERT INTO Billing (PatientId, Amount, Paid) VALUES (" + to_string(patientId) + ", " + to_string(amount) + "," + (paid ? "1" : "0") + ");";
		return(sqlite3_exec(DB, sqlQuery.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK);
	}
	bool UpdateBedStatus(int patientId, string bedId) {
		string sqlQuery = "UPDATE Patients SET AssignedBed='" + bedId + "' WHERE PatientID=" + to_string(patientId) + ";";
		string sqlQuery2 = "UPDATE Beds SET Status = CASE WHEN Status = 'Vacant' THEN 'Occupied' ELSE 'Vacant' END WHERE BedID='" + bedId + "';";
		
		return((sqlite3_exec(DB, sqlQuery.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK) && 
			   (sqlite3_exec(DB, sqlQuery2.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK));
	}
	bool SetNotices(int id,string content) {
		string sqlQuery = "UPDATE Notices SET Message='" + content + "' WHERE Id=" + to_string(id) + ";";
		return(sqlite3_exec(DB, sqlQuery.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK);
	}
	bool removeNotices(int id) {
		string sqlQuery = "DELETE FROM Notices WHERE Id=" + to_string(id) + ";";
		return(sqlite3_exec(DB, sqlQuery.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK);
	}

};
#endif

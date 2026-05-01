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

	// Check if username already exists in Users table
	bool UsernameExists(string username) {
		if (!DB) return false;
		string sqlQuery = "SELECT COUNT(*) FROM Users WHERE Username='" + username + "';";
		sqlite3_stmt* stmt;
		int count = 0;
		if (sqlite3_prepare_v2(DB, sqlQuery.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
			if (sqlite3_step(stmt) == SQLITE_ROW) {
				count = sqlite3_column_int(stmt, 0);
			}
			sqlite3_finalize(stmt);
		}
		return (count > 0);
	}

	// Check if patient name already exists
	bool PatientNameExists(string name) {
		if (!DB) return false;
		string sqlQuery = "SELECT COUNT(*) FROM Patients WHERE Name='" + name + "';";
		sqlite3_stmt* stmt;
		int count = 0;
		if (sqlite3_prepare_v2(DB, sqlQuery.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
			if (sqlite3_step(stmt) == SQLITE_ROW) {
				count = sqlite3_column_int(stmt, 0);
			}
			sqlite3_finalize(stmt);
		}
		return (count > 0);
	}

	// Check if doctor name already exists
	bool DoctorNameExists(string name) {
		if (!DB) return false;
		string sqlQuery = "SELECT COUNT(*) FROM Doctors WHERE Name='" + name + "';";
		sqlite3_stmt* stmt;
		int count = 0;
		if (sqlite3_prepare_v2(DB, sqlQuery.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
			if (sqlite3_step(stmt) == SQLITE_ROW) {
				count = sqlite3_column_int(stmt, 0);
			}
			sqlite3_finalize(stmt);
		}
		return (count > 0);
	}

	bool AddPatient(string name, string history) {
		if (DB) {
			string sqlQuery = "INSERT INTO Patients (Name, History) VALUES ('" + name + "', '" + history + "');";
			bool result = (sqlite3_exec(DB, sqlQuery.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK);
			if (!result) {
				cout << "Patient Add Error: " << errorMessage << "\nSQL: " << sqlQuery << endl;
			}
			return result;
		}
		else {
			return false;
		}			
	}
	bool AddUsername(string username, string password, string role) {
		if (DB) {
			string sqlQuery = "INSERT INTO Users (Username, Password, Role) VALUES ('" + username + "', '" + password + "', '" + role + "');";
			bool result = (sqlite3_exec(DB, sqlQuery.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK);
			if (!result) {
				cout << "Username Add Error: " << errorMessage << "\nSQL: " << sqlQuery << endl;
			}
			return result;
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
	bool AddDoctor(string name, string specialty, string salary, bool isAvailable) {
		if (DB) {
			// Salary REAL ہے تو number کے طور پر ڈالیں، اور IsAvailable بھی INTEGER کے طور پر
			string sqlQuery = "INSERT INTO Doctors (Name, Specialty, Salary, IsAvailable) VALUES ('" + name + "', '" + specialty + "', " + salary + ", " + (isAvailable ? "1" : "0") + ");";
			bool result = (sqlite3_exec(DB, sqlQuery.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK);
			if (!result) {
				cout << "Doctor Add Error: " << errorMessage << "\nSQL: " << sqlQuery << endl;
			}
			return result;
		}
		else {
			return false;
		}
	}
	bool CheckConflict(int doctorId, string StartTime, string EndTime, bool isSurgery) {
		string sql = "SELECT COUNT(*) FROM Appointments WHERE DoctorID=" + to_string(doctorId) + 
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
	bool BookAppointment(int patientId, int doctorId, string Starttime, string EndTime, bool isSurgury) {
		string surg;
		if(isSurgury) {
			surg = "1";
		}
		else {
			surg = "0";
		}
		string sqlQuery = "INSERT INTO Appointments (PatientID, DoctorID, StartTime, EndTime, IsSurgury) VALUES (" + to_string(patientId) + ", " + to_string(doctorId) + ", '" + Starttime + "', '" + EndTime + "', " + surg + ");";

		bool result = (sqlite3_exec(DB, sqlQuery.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK);
		if (!result && errorMessage) {
			cout << "SQLite Error: " << errorMessage << "\nSQL: " << sqlQuery << endl;
			string fullErr = "SQLite Error: " + string(errorMessage) + "\nSQL: " + sqlQuery;
			sqlite3_free(errorMessage);
			errorMessage = new char[fullErr.length() + 1];
			strcpy(errorMessage, fullErr.c_str());
		}
		return result;
	}
	
	string getLastError() {
		if (errorMessage) return string(errorMessage);
		return "Unknown DB error";
	}
	bool GenerateBill(int patientId, double amount, bool paid) {
		string sqlQuery = "INSERT INTO Billing (PatientId, Amount, Paid) VALUES (" + to_string(patientId) + ", " + to_string(amount) + "," + (paid ? "1" : "0") + ");";
		bool result = (sqlite3_exec(DB, sqlQuery.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK);
		if (!result && errorMessage) {
			cout << "Billing Error: " << errorMessage << "\nSQL: " << sqlQuery << endl;
		}
		return result;
	}
	bool UpdateBedStatus(int patientId, string bedId) {
		string sqlQuery = "UPDATE Patients SET AssignedBed='" + bedId + "' WHERE PatientID=" + to_string(patientId) + ";";
		string sqlQuery2 = "UPDATE Beds SET Status = CASE WHEN Status = 'Vacant' THEN 'Occupied' ELSE 'Vacant' END WHERE BedID='" + bedId + "';";
		
		bool result1 = (sqlite3_exec(DB, sqlQuery.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK);
		bool result2 = (sqlite3_exec(DB, sqlQuery2.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK);
		
		if (!result1 || !result2) {
			cout << "Bed Status Update Error: " << errorMessage << endl;
		}
		
		return (result1 && result2);
	}
	bool SetNotices(int id, string content) {
		string sqlQuery = "UPDATE Notices SET Message='" + content + "' WHERE Id=" + to_string(id) + ";";
		bool result = (sqlite3_exec(DB, sqlQuery.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK);
		if (!result && errorMessage) {
			cout << "Notices Error: " << errorMessage << endl;
		}
		return result;
	}
	bool removeNotices(int id) {
		string sqlQuery = "DELETE FROM Notices WHERE Id=" + to_string(id) + ";";
		bool result = (sqlite3_exec(DB, sqlQuery.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK);
		if (!result && errorMessage) {
			cout << "Remove Notices Error: " << errorMessage << endl;
		}
		return result;
	}
	bool AddMedicalRecord(int patientId, int doctorId, string diagnosis, string symptoms, string treatment) {
		if (DB) {
			string sqlQuery = "INSERT INTO MedicalRecords (PatientID, DoctorID, Diagnosis, Symptoms, Treatment) VALUES (" +
				to_string(patientId) + ", " + to_string(doctorId) + ", '" + diagnosis + "', '" + symptoms + "', '" + treatment + "');";
			bool result = (sqlite3_exec(DB, sqlQuery.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK);
			if (!result && errorMessage) {
				cout << "Medical Record Error: " << errorMessage << endl;
			}
			return result;
		}
		return false;
	}
	bool AddPrescription(int patientId, int doctorId, string medicineDetails, string instructions) {
		string sqlQuery = "INSERT INTO Prescriptions (PatientID, DoctorID, MedicineDetails, Instructions) VALUES (" +
			to_string(patientId) + ", " + to_string(doctorId) + ", '" + medicineDetails + "', '" + instructions + "');";
		bool result = (sqlite3_exec(DB, sqlQuery.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK);
		if (!result && errorMessage) {
			cout << "Prescription Error: " << errorMessage << endl;
		}
		return result;
	}
	bool AddPayrollRecord(int doctorId, double amount) {
		string sqlQuery = "INSERT INTO Payroll (DoctorID, Amount) VALUES (" +
			to_string(doctorId) + ", " + to_string(amount) + ");";
		bool result = (sqlite3_exec(DB, sqlQuery.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK);
		if (!result && errorMessage) {
			cout << "Payroll Error: " << errorMessage << endl;
		}
		return result;
	}
	bool AddBed(string bedId, string roomNumber) {
		if (DB) {
			string sqlQuery = "INSERT INTO Beds (BedID, RoomNumber) VALUES ('" + bedId + "', '" + roomNumber + "');";
			bool result = (sqlite3_exec(DB, sqlQuery.c_str(), nullptr, 0, &errorMessage) == SQLITE_OK);
			if (!result && errorMessage) {
				cout << "Bed Add Error: " << errorMessage << endl;
			}
			return result;
		}
		return false;			
	}
	bool EnsureCurrentSessionTable() {
		if (DB) {
			const char* sql = "CREATE TABLE IF NOT EXISTS CurrentSession ("
							  "SessionID INTEGER PRIMARY KEY AUTOINCREMENT, "
							  "UserID INTEGER, "
							  "UserName TEXT, "
							  "UserRole TEXT, "
							  "LoginTime DATETIME DEFAULT CURRENT_TIMESTAMP"
							  ");";
			bool result = (sqlite3_exec(DB, sql, nullptr, 0, &errorMessage) == SQLITE_OK);
			if (!result && errorMessage) {
				cout << "CurrentSession Table Error: " << errorMessage << endl;
			}
			return result;
		}
		return false;
	}
	sqlite3* getDB() {
		return DB;
	}
};
#endif

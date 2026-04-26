--tables
CREATE TABLE Users(
    UserID INTEGER PRIMARY KEY AUTOINCREMENT,
    Username TEXT UNIQUE NOT NULL,
    Password TEXT NOT NULL,
    Role TEXT NOT NULL --Admin/doctor/patients
);
CREATE TABLE Patients(
    PatientID INTEGER PRIMARY KEY AUTOINCREMENT,
    Name TEXT NOT NULL,
    History TEXT,
    AssignedBed TEXT,
    AssignedDoctorID INTEGER,
    FOREIGN KEY (AssignedDoctorID) REFERENCES Users(UserID)
);

CREATE TABLE Doctors(
    DoctorID INTEGER PRIMARY KEY AUTOINCREMENT,
    Name TEXT NOT NULL,
    Specialty TEXT NOT NULL,
    Salary DECIMAL(10, 2) NOT NULL,
    IsAvilable INTEGER NOT NULL,
    FOREIGN KEY (DoctorID) REFERENCES Users(UserID)
);
CREATE TABLE Appointments(
    AppointmentID INTEGER PRIMARY KEY AUTOINCREMENT,
    PatientID INTEGER,
    DoctorID INTEGER,
    StartTime TIME,
    EndTime TIME,
    IsSurgury INTEGER DEFAULT FALSE,
    FOREIGN KEY (PatientID) REFERENCES Patients(PatientID),
    FOREIGN KEY (DoctorID) REFERENCES Users(UserID)
);
CREATE TABLE Billing(
    BillId INTEGER PRIMARY KEY AUTOINCREMENT,
    PatientID INTEGER,
    Amount REAL NOT NULL,
    Paid INTEGER NOT NULL,
    FOREIGN KEY (PatientID) REFERENCES Patients(PatientID)
);
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


struct Patient {
    int patientID;
    string name;
    int age;
    string disease;
    int roomNumber;
};


void addPatient(vector<Patient>& patients) {
    Patient newPatient;

    cout << "Enter Patient ID: ";
    cin >> newPatient.patientID;
    cin.ignore(); 

    cout << "Enter Patient Name: ";
    getline(cin, newPatient.name);

    cout << "Enter Age: ";
    cin >> newPatient.age;
    cin.ignore();

    cout << "Enter Disease: ";
    getline(cin, newPatient.disease);

    cout << "Enter Room Number: ";
    cin >> newPatient.roomNumber;

 
    patients.push_back(newPatient);
    cout << "Patient added successfully!\n";
}


void searchPatient(const vector<Patient>& patients) {
    int patientID;
    cout << "Enter Patient ID to search: ";
    cin >> patientID;

    bool found = false;
    for (const auto& patient : patients) {
        if (patient.patientID == patientID) {
            cout << "Patient found: \n";
            cout << "ID: " << patient.patientID << ", Name: " << patient.name << ", Age: " << patient.age 
                 << ", Disease: " << patient.disease << ", Room Number: " << patient.roomNumber << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Patient with ID " << patientID << " not found.\n";
    }
}


void displayPatients(const vector<Patient>& patients) {
    if (patients.empty()) {
        cout << "No patients are currently admitted.\n";
        return;
    }

    cout << "Patients currently admitted: \n";
    for (const auto& patient : patients) {
        cout << "ID: " << patient.patientID << ", Name: " << patient.name << ", Age: " << patient.age 
             << ", Disease: " << patient.disease << ", Room Number: " << patient.roomNumber << endl;
    }
}


void saveToFile(const vector<Patient>& patients, const string& filename) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }

    size_t size = patients.size();
    outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));

    for (const auto& patient : patients) {
        outFile.write(reinterpret_cast<const char*>(&patient), sizeof(Patient));
    }

    outFile.close();
    cout << "Patient records saved successfully!\n";
}


void loadFromFile(vector<Patient>& patients, const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cout << "Error opening file for reading or file does not exist.\n";
        return;
    }

    size_t size;
    inFile.read(reinterpret_cast<char*>(&size), sizeof(size));

    patients.clear(); 
    for (size_t i = 0; i < size; ++i) {
        Patient patient;
        inFile.read(reinterpret_cast<char*>(&patient), sizeof(Patient));
        patients.push_back(patient);
    }

    inFile.close();
    cout << "Patient records loaded successfully!\n";
}

int main() {
    vector<Patient> patients;
    string filename = "patients_data.dat";

  
    loadFromFile(patients, filename);

    while (true) {
        int choice;
        cout << "\nHospital Patient Management System\n";
        cout << "1. Add a new patient\n";
        cout << "2. Search for a patient by ID\n";
        cout << "3. Display all admitted patients\n";
        cout << "4. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addPatient(patients);
                break;
            case 2:
                searchPatient(patients);
                break;
            case 3:
                displayPatients(patients);
                break;
            case 4:
                saveToFile(patients, filename);
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}

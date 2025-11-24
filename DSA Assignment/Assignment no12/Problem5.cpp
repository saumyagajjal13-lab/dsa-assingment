#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
using namespace std;

struct PlacementRecord {
    int studentID;
    string studentName;
    string company;
    string package;
    string placementDate;
    string status;
};

class PlacementPortal {
private:
    static const int INITIAL_SIZE = 50;
    vector<list<PlacementRecord>> table;
    int currentSize;
    int count;

    int hashFunction(int studentID) {
        return studentID % currentSize;
    }

    void rehash() {
        vector<list<PlacementRecord>> oldTable = table;
        currentSize *= 2;
        table.clear();
        table.resize(currentSize);
        count = 0;

        for (auto& chain : oldTable) {
            for (auto& record : chain) {
                insertRecord(record);
            }
        }
        cout << "Table rehashed to size: " << currentSize << endl;
    }

public:
    PlacementPortal() {
        currentSize = INITIAL_SIZE;
        table.resize(currentSize);
        count = 0;
    }

    void insertRecord(PlacementRecord record) {
        if (count >= currentSize * 0.7) {
            rehash();
        }

        int index = hashFunction(record.studentID);
        table[index].push_back(record);
        count++;
    }

    void addPlacement(int id, string name, string company, string pkg, string date, string status) {
        PlacementRecord record = {id, name, company, pkg, date, status};
        insertRecord(record);
        cout << "Placement record added for " << name << endl;
    }

    PlacementRecord* searchPlacement(int studentID) {
        int index = hashFunction(studentID);
        
        for (auto& record : table[index]) {
            if (record.studentID == studentID) {
                return &record;
            }
        }
        return nullptr;
    }

    void displayStudentPlacement(int studentID) {
        PlacementRecord* record = searchPlacement(studentID);
        if (record != nullptr) {
            cout << "\nPlacement Details:\n";
            cout << "Student ID: " << record->studentID << endl;
            cout << "Student Name: " << record->studentName << endl;
            cout << "Company: " << record->company << endl;
            cout << "Package: " << record->package << endl;
            cout << "Placement Date: " << record->placementDate << endl;
            cout << "Status: " << record->status << endl;
        } else {
            cout << "No placement record found for Student ID: " << studentID << endl;
        }
    }

    void updatePlacementStatus(int studentID, string newStatus) {
        PlacementRecord* record = searchPlacement(studentID);
        if (record != nullptr) {
            record->status = newStatus;
            cout << "Placement status updated to: " << newStatus << endl;
        } else {
            cout << "Student record not found!" << endl;
        }
    }

    void displayCompanyWise(string company) {
        cout << "\nPlacements in " << company << ":\n";
        bool found = false;
        
        for (auto& chain : table) {
            for (auto& record : chain) {
                if (record.company == company) {
                    cout << "Student: " << record.studentName << " (ID: " << record.studentID 
                         << "), Package: " << record.package << ", Status: " << record.status << endl;
                    found = true;
                }
            }
        }
        
        if (!found) {
            cout << "No placements found for " << company << endl;
        }
    }

    void displayAllPlacements() {
        cout << "\nAll Placement Records:\n";
        bool found = false;
        
        for (auto& chain : table) {
            for (auto& record : chain) {
                cout << "ID: " << record.studentID << ", Name: " << record.studentName 
                     << ", Company: " << record.company << ", Package: " << record.package 
                     << ", Status: " << record.status << endl;
                found = true;
            }
        }
        
        if (!found) {
            cout << "No placement records found!" << endl;
        }
    }

    void displayStatistics() {
        int placed = 0, pending = 0, rejected = 0;
        double totalLoadFactor = 0;
        int maxChainLength = 0;
        
        for (auto& chain : table) {
            int chainLength = chain.size();
            totalLoadFactor += chainLength;
            if (chainLength > maxChainLength) {
                maxChainLength = chainLength;
            }
            
            for (auto& record : chain) {
                if (record.status == "Placed") placed++;
                else if (record.status == "Pending") pending++;
                else if (record.status == "Rejected") rejected++;
            }
        }
        
        cout << "\nPlacement Statistics:\n";
        cout << "Total Records: " << count << endl;
        cout << "Table Size: " << currentSize << endl;
        cout << "Load Factor: " << (double)count / currentSize << endl;
        cout << "Max Chain Length: " << maxChainLength << endl;
        cout << "Placed: " << placed << endl;
        cout << "Pending: " << pending << endl;
        cout << "Rejected: " << rejected << endl;
    }
};

int main() {
    PlacementPortal portal;
    int choice, id;
    string name, company, pkg, date, status;

    do {
        cout << "\nSmart College Placement Portal\n";
        cout << "1. Add Placement Record\n";
        cout << "2. Search Student Placement\n";
        cout << "3. Update Placement Status\n";
        cout << "4. Display Company-wise Placements\n";
        cout << "5. Display All Placements\n";
        cout << "6. Display Statistics\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter Student ID: ";
                cin >> id;
                cout << "Enter Student Name: ";
                cin >> name;
                cout << "Enter Company: ";
                cin >> company;
                cout << "Enter Package: ";
                cin >> pkg;
                cout << "Enter Placement Date: ";
                cin >> date;
                cout << "Enter Status (Placed/Pending/Rejected): ";
                cin >> status;
                portal.addPlacement(id, name, company, pkg, date, status);
                break;
            case 2:
                cout << "Enter Student ID to search: ";
                cin >> id;
                portal.displayStudentPlacement(id);
                break;
            case 3:
                cout << "Enter Student ID: ";
                cin >> id;
                cout << "Enter New Status: ";
                cin >> status;
                portal.updatePlacementStatus(id, status);
                break;
            case 4:
                cout << "Enter Company Name: ";
                cin >> company;
                portal.displayCompanyWise(company);
                break;
            case 5:
                portal.displayAllPlacements();
                break;
            case 6:
                portal.displayStatistics();
                break;
            case 7:
                cout << "Exiting Placement Portal...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while(choice != 7);

    return 0;
}
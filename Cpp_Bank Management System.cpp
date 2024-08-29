
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Structure to represent a customer account
struct CustomerAccount {
    string customer_id;
    string customer_name;
    string customer_address;
    double account_balance;
};
int MAX_RECORDS;
// Function prototypes
void displayMenu();
void enterNewRecord(CustomerAccount records[], int& recordCount);
void searchAndDisplayRecord(const CustomerAccount records[], int recordCount);
void withdrawAmount(CustomerAccount records[], int recordCount);
void depositAmount(CustomerAccount records[], int recordCount);
void deleteRecord(CustomerAccount records[], int& recordCount);
void changeRecord(CustomerAccount records[], int recordCount);
void displayAllRecords(const CustomerAccount records[], int recordCount);
bool saveRecordsToFile(const CustomerAccount records[], int recordCount, const string& file_path);
int loadRecordsFromFile(CustomerAccount records[], const string& file_path);

int main() {
	cout<<"enter the amount of customer record you want to store"<<endl;
cin>>MAX_RECORDS;
    string file_path = "customer_records.txt";
    CustomerAccount records[MAX_RECORDS];
    int recordCount = loadRecordsFromFile(records, file_path);

    char choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case '1':
                enterNewRecord(records, recordCount);
                break;
            case '2':
                searchAndDisplayRecord(records, recordCount);
                break;
            case '3':
                withdrawAmount(records, recordCount);
                break;
            case '4':
                depositAmount(records, recordCount);
                break;
            case '5':
                deleteRecord(records, recordCount);
                break;
            case '6':
                changeRecord(records, recordCount);
                break;
            case '7':
                displayAllRecords(records, recordCount);
                break;
            case '8':
                if (saveRecordsToFile(records, recordCount, file_path)) {
                    cout << "Program terminated. Records saved to file successfully." << endl;
                } else {
                    cout << "Error saving records to file." << endl;
                }
                break;
            default:
                cout << "Invalid choice. Please enter a number (1-7) or '8' to quit." << endl;
        }
    } while (choice != '8');

    return 0;
}

void displayMenu() {
    cout << "\nMenu:" << endl;
    cout << "1. Enter new records into the file" << endl;
    cout << "2. Search for a particular customer's record and display it" << endl;
    cout << "3. Withdraw a specified amount from the customer account" << endl;
    cout << "4. Deposit a specified amount to the account" << endl;
    cout << "5. Search for a particular customer's record and delete it" << endl;
    cout << "6. Search for a particular customer's record and change it" << endl;
    cout << "7. Display the contents of the entire file" << endl;
    cout << "8. Quit" << endl;
}

void enterNewRecord(CustomerAccount records[], int& recordCount) {
    if (recordCount < MAX_RECORDS) {
        CustomerAccount newRecord;
        cout << "Enter customer ID: ";
        cin >> newRecord.customer_id;
        cout << "Enter customer name: ";
        cin.ignore(); // Clear the newline character from the buffer
        getline(cin, newRecord.customer_name);
        cout << "Enter customer address: ";
        getline(cin, newRecord.customer_address);

        // Validate input for account balance
        do {
            cout << "Enter account balance: ";
            cin >> newRecord.account_balance;
            if (newRecord.account_balance < 0) {
                cout << "Account balance cannot be negative. Please enter a non-negative value." << endl;
            }
        } while (newRecord.account_balance < 0);

        records[recordCount++] = newRecord;
        cout << "Record added successfully." << endl;
    } else {
        cout << "Maximum number of records reached." << endl;
    }
}

void searchAndDisplayRecord(const CustomerAccount records[], int recordCount) {
    string searchId;
    cout << "Enter customer ID to search: ";
    cin >> searchId;

    for (int i = 0; i < recordCount; ++i) {
        if (records[i].customer_id == searchId) {
            cout << "Customer ID: " << records[i].customer_id << endl;
            cout << "Customer Name: " << records[i].customer_name << endl;
            cout << "Customer Address: " << records[i].customer_address << endl;
            cout << "Account Balance: " << records[i].account_balance << endl;
            return;
        }
    }

    cout << "Customer not found." << endl;
}

void withdrawAmount(CustomerAccount records[], int recordCount) {
    string searchId;
    cout << "Enter customer ID to withdraw from: ";
    cin >> searchId;

    for (int i = 0; i < recordCount; ++i) {
        if (records[i].customer_id == searchId) {
            double withdrawalAmount;
            cout << "Enter withdrawal amount: ";
            cin >> withdrawalAmount;

            if (records[i].account_balance - withdrawalAmount >= 25) {
                records[i].account_balance -= withdrawalAmount;
                cout << "Withdrawal successful. New balance: " << records[i].account_balance << endl;
            } else {
                cout << "Withdrawal failed. Insufficient funds or balance would be less than 25." << endl;
            }
            return;
        }
    }

    cout << "Customer not found." << endl;
}

void depositAmount(CustomerAccount records[], int recordCount) {
    string searchId;
    cout << "Enter customer ID to deposit to: ";
    cin >> searchId;

    for (int i = 0; i < recordCount; ++i) {
        if (records[i].customer_id == searchId) {
            double depositAmount;
            cout << "Enter deposit amount: ";
            cin >> depositAmount;

            records[i].account_balance += depositAmount;
            cout << "Deposit successful. New balance: " << records[i].account_balance << endl;
            return;
        }
    }

    cout << "Customer not found." << endl;
}

void deleteRecord(CustomerAccount records[], int& recordCount) {
    string searchId;
    cout << "Enter customer ID to delete: ";
    cin >> searchId;

    for (int i = 0; i < recordCount; ++i) {
        if (records[i].customer_id == searchId) {
            for (int j = i; j < recordCount - 1; ++j) {
                records[j] = records[j + 1];
            }
            --recordCount;
            cout << "Record deleted successfully." << endl;
            return;
        }
    }

    cout << "Customer not found." << endl;
}

void changeRecord(CustomerAccount records[], int recordCount) {
    string searchId;
    cout << "Enter customer ID to change: ";
    cin >> searchId;

    for (int i = 0; i < recordCount; ++i) {
        if (records[i].customer_id == searchId) {
            cout << "Enter new information:" << endl;
            cout << "Enter customer name: ";
            cin.ignore();
            getline(cin, records[i].customer_name);
            cout << "Enter customer address: ";
            getline(cin, records[i].customer_address);
            cout << "Record changed successfully." << endl;
            return;
        }
    }

    cout << "Customer not found." << endl;
}

void displayAllRecords(const CustomerAccount records[], int recordCount) {
    for (int i = 0; i < recordCount; ++i) {
        cout << "\nCustomer ID: " << records[i].customer_id << endl;
        cout << "Customer Name: " << records[i].customer_name << endl;
        cout << "Customer Address: " << records[i].customer_address << endl;
        cout << "Account Balance: " << records[i].account_balance << endl;
    }
}

bool saveRecordsToFile(const CustomerAccount records[], int recordCount, const string& file_path) {
    ofstream file(file_path, ios::out);

    if (file.is_open()) {
        for (int i = 0; i < recordCount; ++i) {
            file << records[i].customer_id << ',' << records[i].customer_name << ',' << records[i].customer_address << ',' << records[i].account_balance << '\n';
        }

        file.close();
        return true;
    }

    return false;
}

int loadRecordsFromFile(CustomerAccount records[], const string& file_path) {
    ifstream file(file_path, ios::in);
    int recordCount = 0;

    if (file.is_open()) {
        while (recordCount < MAX_RECORDS && getline(file, records[recordCount].customer_id, ',')) {
            getline(file, records[recordCount].customer_name, ',');
            getline(file, records[recordCount].customer_address, ',');
            file >> records[recordCount].account_balance;
            file.ignore(); // Ignore the newline character

            ++recordCount;
        }

        file.close();
    }

    return recordCount;
}

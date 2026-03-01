#include <iostream>
#include <string>
#include <fstream> 

using namespace std;

// UNIT 3: Base Class
class Person {
protected: 
    string name;
    string phone;

public:
    // UNIT 2: Constructors
    Person() {
        name = "Unknown";
        phone = "Unknown";
    }

    Person(string n, string p) {
        name = n;
        phone = p;
    }
};

// UNIT 3: Single Inheritance
class Contact : public Person {
private:
    string email;

public:
    Contact() : Person() {
        email = "Unknown";
    }

    void setDetails(string n, string p, string e) {
        name = n;     
        phone = p;    
        email = e;    
    }

    // Getters needed for searching and rewriting the file
    string getName() { return name; }
    string getPhone() { return phone; }
    string getEmail() { return email; }

    // UNIT 3: Friend Function
    friend void displayContact(Contact c);
};

void displayContact(Contact c) {
    cout << "Name: " << c.name << " | Phone: " << c.phone << " | Email: " << c.email << endl;
}

int main() {
    Contact phonebook[100]; 
    int totalContacts = 0;
    int choice;

    // Load contacts on startup
    ifstream inFile("contacts.txt"); 
    if (inFile.is_open()) {
        string n, p, e;
        while (getline(inFile, n, ',') && getline(inFile, p, ',') && getline(inFile, e)) {
            phonebook[totalContacts].setDetails(n, p, e);
            totalContacts++;
        }
        inFile.close();
    }

    do {
        cout << "\n--- Advanced Contact Management System ---" << endl;
        cout << "1. Add a New Contact" << endl;
        cout << "2. Display All Contacts" << endl;
        cout << "3. Search for a Contact" << endl; // NEW
        cout << "4. Delete a Contact" << endl;     // NEW
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (totalContacts < 100) {
                    string tempName, tempPhone, tempEmail;
                    cin.ignore(); 

                    cout << "Enter Name: ";
                    getline(cin, tempName); 
                    cout << "Enter Phone Number: ";
                    getline(cin, tempPhone);
                    cout << "Enter Email: ";
                    getline(cin, tempEmail);
                    
                    phonebook[totalContacts].setDetails(tempName, tempPhone, tempEmail);
                    totalContacts++;
                    
                    ofstream outFile("contacts.txt", ios::app); 
                    if (outFile.is_open()) {
                        outFile << tempName << "," << tempPhone << "," << tempEmail << endl;
                        outFile.close();
                    }
                    cout << "Contact saved permanently!" << endl;
                } else {
                    cout << "Phonebook is full!" << endl;
                }
                break;

            case 2:
                if (totalContacts == 0) {
                    cout << "Your phonebook is empty." << endl;
                } else {
                    cout << "\n--- Saved Contacts ---" << endl;
                    for (int i = 0; i < totalContacts; i++) {
                        cout << i + 1 << ". ";
                        displayContact(phonebook[i]); 
                    }
                }
                break;

            case 3: {
                // NEW: Search Logic
                if (totalContacts == 0) {
                    cout << "Your phonebook is empty." << endl;
                    break;
                }
                
                string searchName;
                bool found = false;
                cin.ignore();
                cout << "Enter the Exact Name to Search: ";
                getline(cin, searchName);

                for (int i = 0; i < totalContacts; i++) {
                    if (phonebook[i].getName() == searchName) {
                        cout << "\n--- Contact Found ---" << endl;
                        displayContact(phonebook[i]);
                        found = true;
                        break; // Stop searching once found
                    }
                }

                if (!found) {
                    cout << "Contact not found." << endl;
                }
                break;
            }

            case 4: {
                // NEW: Delete Logic
                if (totalContacts == 0) {
                    cout << "Your phonebook is empty." << endl;
                    break;
                }

                string deleteName;
                bool found = false;
                cin.ignore();
                cout << "Enter the Exact Name to Delete: ";
                getline(cin, deleteName);

                for (int i = 0; i < totalContacts; i++) {
                    if (phonebook[i].getName() == deleteName) {
                        found = true;
                        
                        // Shift all subsequent contacts to the left by 1
                        for (int j = i; j < totalContacts - 1; j++) {
                            phonebook[j] = phonebook[j + 1]; 
                        }
                        
                        totalContacts--; // Reduce the total count
                        cout << "Contact deleted successfully." << endl;

                        // Overwrite the text file with the newly updated array
                        // Notice we removed ios::app, so it creates a fresh file
                        ofstream outFile("contacts.txt"); 
                        if (outFile.is_open()) {
                            for (int k = 0; k < totalContacts; k++) {
                                outFile << phonebook[k].getName() << "," 
                                        << phonebook[k].getPhone() << "," 
                                        << phonebook[k].getEmail() << endl;
                            }
                            outFile.close();
                        }
                        break; 
                    }
                }

                if (!found) {
                    cout << "Contact not found. No deletion made." << endl;
                }
                break;
            }

            case 5:
                cout << "Exiting the program. Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
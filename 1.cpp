#include <iostream>
#include <string>
#include <vector> // NEW: The library needed to use vectors

using namespace std;

// 1. CLASS & CONSTRUCTORS: The Base Class
class Person {
protected:
    string name;
    string phone;

public:
    // Default Constructor
    Person() {
        name = "Unknown";
        phone = "Unknown";
    }

    // Parameterized Constructor
    Person(string n, string p) {
        name = n;
        phone = p;
    }
};

// 2. INHERITANCE: The Derived Class
class Contact : public Person {
private:
    string email;

public:
    // Constructor using initializer list to call the Base Constructor
    Contact() : Person() {
        email = "Unknown";
    }

    // Method to set all details
    void setDetails(string n, string p, string e) {
        name = n;
        phone = p;
        email = e;
    }

    // Getters
    string getName() { return name; }
    
    // Method to display a single contact
    void displayContact() {
        cout << "Name: " << name << " | Phone: " << phone << " | Email: " << email << endl;
    }
};

int main() {
    // 3. VECTOR: Replacing the old array!
    vector<Contact> phonebook; 
    int choice;

    do {
        cout << "\n--- Vector Contact Management System ---" << endl;
        cout << "1. Add a New Contact" << endl;
        cout << "2. Display All Contacts" << endl;
        cout << "3. Delete a Contact" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string tempName, tempPhone, tempEmail;
                Contact newContact; // Create a temporary contact object

                cin.ignore();
                cout << "Enter Name: ";
                getline(cin, tempName);
                cout << "Enter Phone Number: ";
                getline(cin, tempPhone);
                cout << "Enter Email: ";
                getline(cin, tempEmail);

                // Set the details of the temporary contact
                newContact.setDetails(tempName, tempPhone, tempEmail);

                // Add it to the end of the vector
                phonebook.push_back(newContact); 
                cout << "Contact added successfully!" << endl;
                break;
            }

            case 2:
                // check if the vector is empty using .empty()
                if (phonebook.empty()) { 
                    cout << "Your phonebook is empty." << endl;
                } else {
                    cout << "\n--- Saved Contacts ---" << endl;
                    // .size() automatically knows exactly how many contacts exist
                    for (int i = 0; i < phonebook.size(); i++) { 
                        cout << i + 1 << ". ";
                        phonebook[i].displayContact();
                    }
                }
                break;

            case 3: {
                if (phonebook.empty()) {
                    cout << "Your phonebook is empty." << endl;
                    break;
                }

                string deleteName;
                bool found = false;
                cin.ignore();
                cout << "Enter the Exact Name to Delete: ";
                getline(cin, deleteName);

                for (int i = 0; i < phonebook.size(); i++) {
                    if (phonebook[i].getName() == deleteName) {
                        found = true;
                        // Vectors have a built-in erase function! No manual shifting needed.
                        phonebook.erase(phonebook.begin() + i); 
                        cout << "Contact deleted successfully." << endl;
                        break;
                    }
                }

                if (!found) {
                    cout << "Contact not found." << endl;
                }
                break;
            }

            case 4:
                cout << "Exiting the program. Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
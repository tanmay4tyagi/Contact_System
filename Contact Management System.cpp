#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

// ================= BASE CLASS =================
class Person {
protected:
    string name;
    string phone;

public:
    Person() {
        name = "Unknown";
        phone = "Unknown";
    }

    Person(string n, string p) {
        name = n;
        phone = p;
    }
};

// ================= DERIVED CLASS =================
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

    string getName() { return name; }
    string getPhone() { return phone; } 
    string getEmail() { return email; }

    friend void displayContact(Contact c);
};

void displayContact(Contact c) {
     cout << c.name << " | " << c.phone << " | " << c.email << endl;
}

// ================= VALIDATION FUNCTIONS =================
bool isValidPhone(string phone) {

    if (phone.empty()) 
        return false;

    if (phone[0] != '+')
        return false;

    if (phone.length() < 10)
        return false;

    for (int i = 1; i < phone.length(); i++) {
        if (!isdigit(phone[i]))
            return false;
    }

    return true;
}

bool isValidEmail(string email) {

    int atPos = email.find('@');
    int dotPos = email.find('.', atPos);

    if (atPos == string::npos || dotPos == string::npos)
        return false;

    if (atPos > dotPos)
        return false;

    if (dotPos == email.length() - 1)
        return false;

    return true;
}

 
// ================= MAIN =================
int main() {

    Contact phonebook[100];
    int totalContacts = 0;
    int choice;

    // Load contacts from file 
    ifstream inFile("contacts.txt");
    if (inFile.is_open()) {
        string n, p, e;
        
        while (getline(inFile, n, ',') &&
               getline(inFile, p, ',') &&
               getline(inFile, e)) {

            phonebook[totalContacts].setDetails(n, p, e);
            totalContacts++;
        }
        inFile.close();
    }

    do {
        cout << "\033[1;32m";  // Green color
        cout << "\n--- Advanced Contact Management System ---\n";
cout << "\033[0m";     // Reset color
        cout << "1. Add a New Contact" << endl;
        cout << "2. Display All Contacts" << endl;
        cout << "3. Search for a Contact" << endl;
        cout << "4. Delete a Contact" << endl;
        cout << "5. Edit a Contact" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            if (totalContacts < 100) {

                string tempName, tempPhone, tempEmail;
                cin.ignore();

                cout << "Enter Name: ";
                getline(cin, tempName);

                // PHONE VALIDATION LOOP
                do {
                    cout << "Enter Phone Number (+CountryCodeNumber): ";
                    getline(cin, tempPhone);

                    if (!isValidPhone(tempPhone)) {
                        cout << "Invalid phone number!" << endl;
                        cout << "Example: +919876543210" << endl;
                    }

                } while (!isValidPhone(tempPhone));

                // EMAIL VALIDATION LOOP
                do {
                    cout << "Enter Email: ";
                    getline(cin, tempEmail);

                    if (!isValidEmail(tempEmail)) {
                        cout << "Invalid email format!" << endl;
                        cout << "Example: name@gmail.com" << endl;
                    }

                } while (!isValidEmail(tempEmail));

                phonebook[totalContacts].setDetails(tempName, tempPhone, tempEmail);
                totalContacts++;

                ofstream outFile("contacts.txt", ios::app);
                if (outFile.is_open()) {
                    outFile << tempName << "," 
                            << tempPhone << "," 
                            << tempEmail << endl;
                    outFile.close();
                }

                cout << "Contact saved successfully!" << endl;
            }
            else {
                cout << "Phonebook is full!" << endl;
            }
            break;

        case 2:
            if (totalContacts == 0) {
                cout << "Your phonebook is empty." << endl;
            }
            else {
                cout << "\n--- Saved Contacts ---" << endl;

                for (int i = 0; i < totalContacts; i++) {
                    cout << i + 1 << ". ";
                    displayContact(phonebook[i]);
                }
            }
            break;

        case 3: {
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
                    break;
                }
            }

            if (!found) {
                cout << "Contact not found." << endl;
            }
            break;
        }

        case 4: {
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

                    for (int j = i; j < totalContacts - 1; j++) {
                        phonebook[j] = phonebook[j + 1];
                    }

                    totalContacts--;
                    found = true;

                    ofstream outFile("contacts.txt");
                    if (outFile.is_open()) {
                        for (int k = 0; k < totalContacts; k++) {
                            outFile << phonebook[k].getName() << ","
                                    << phonebook[k].getPhone() << ","
                                    << phonebook[k].getEmail() << endl;
                        }
                        outFile.close();
                    }

                    cout << "Contact deleted successfully." << endl;
                    break;
                }
            }

            if (!found) {
                cout << "Contact not found." << endl;
            }
            break;
        }

        case 5: {
    if (totalContacts == 0) {
        cout << "Your phonebook is empty." << endl;
        break;
    }

    string editName;
    bool found = false;
    cin.ignore();

    cout << "Enter the Exact Name to Edit: ";
    getline(cin, editName);

    for (int i = 0; i < totalContacts; i++) {
        if (phonebook[i].getName() == editName) {

            string newName, newPhone, newEmail;

            cout << "Enter New Name: ";
            getline(cin, newName);

            // Phone validation
            do {
                cout << "Enter New Phone (+CountryCodeNumber): ";
                getline(cin, newPhone);

                if (!isValidPhone(newPhone))
                    cout << "Invalid phone number!" << endl;

            } while (!isValidPhone(newPhone));

            // Email validation
            do {
                cout << "Enter New Email: ";
                getline(cin, newEmail);

                if (!isValidEmail(newEmail))
                    cout << "Invalid email format!" << endl;

            } while (!isValidEmail(newEmail));

            phonebook[i].setDetails(newName, newPhone, newEmail);
            found = true;

            // Rewrite entire file
            ofstream outFile("contacts.txt");
            if (outFile.is_open()) {
                for (int k = 0; k < totalContacts; k++) {
                    outFile << phonebook[k].getName() << ","
                            << phonebook[k].getPhone() << ","
                            << phonebook[k].getEmail() << endl;
                }
                outFile.close();
            }

            cout << "Contact updated successfully!" << endl;
            break;
        }
    }

    if (!found)
        cout << "Contact not found." << endl;

    break;
}

        case 6:
    cout << "\nTotal Contacts Registered: " 
         << totalContacts << endl;

    cout << "Exiting the program. Goodbye!" << endl;
    break;
        default:
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 6);

    return 0;
}
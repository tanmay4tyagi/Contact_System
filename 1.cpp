#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>   // for remove() and rename()

using namespace std;

// ================= BASE CLASS =================
class Person {
protected:
    string name;
    string phone;

public:
    Person() {
        name = "";
        phone = "";
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
        email = "";
    }

    void setDetails(string n, string p, string e) {
        name = n;
        phone = p;
        email = e;
    }

    string getName() {
        return name;
    }

    string getPhone() {
        return phone;
    }

    string getEmail() {
        return email;
    }

    void displayContact() {
        cout << "Name  : " << name << endl;
        cout << "Phone : " << phone << endl;
        cout << "Email : " << email << endl;
        cout << "------------------------" << endl;
    }
};

// ================= MAIN FUNCTION =================
int main() {

    int choice;

    do {
        cout << "\n===== FILE CONTACT MANAGEMENT SYSTEM =====" << endl;
        cout << "1. Add New Contact" << endl;
        cout << "2. Display All Contacts" << endl;
        cout << "3. Delete Contact" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();   // clear newline from buffer

        switch (choice) {

        // ================= ADD CONTACT =================
        case 1: {
            Contact newContact;
            string name, phone, email;

            cout << "Enter Name: ";
            getline(cin, name);

            cout << "Enter Phone: ";
            getline(cin, phone);

            cout << "Enter Email: ";
            getline(cin, email);

            newContact.setDetails(name, phone, email);

            ofstream outFile("contacts.txt", ios::app);

            if (!outFile) {
                cout << "Error opening file!" << endl;
                break;
            }

            outFile << newContact.getName() << endl;
            outFile << newContact.getPhone() << endl;
            outFile << newContact.getEmail() << endl;
            outFile << "-----" << endl;

            outFile.close();

            cout << "Contact added successfully!" << endl;
            break;
        }

        // ================= DISPLAY CONTACTS =================
        case 2: {
            ifstream inFile("contacts.txt");

            if (!inFile) {
                cout << "No contacts found." << endl;
                break;
            }

            string name, phone, email, separator;

            cout << "\n===== SAVED CONTACTS =====" << endl;

            while (getline(inFile, name)) {

                getline(inFile, phone);
                getline(inFile, email);
                getline(inFile, separator);

                cout << "Name  : " << name << endl;
                cout << "Phone : " << phone << endl;
                cout << "Email : " << email << endl;
                cout << "------------------------" << endl;
            }

            inFile.close();
            break;
        }

        // ================= DELETE CONTACT =================
        case 3: {
            string deleteName;
            bool found = false;

            cout << "Enter Exact Name to Delete: ";
            getline(cin, deleteName);

            ifstream inFile("contacts.txt");
            ofstream tempFile("temp.txt");

            if (!inFile) {
                cout << "No contacts found." << endl;
                break;
            }

            string name, phone, email, separator;

            while (getline(inFile, name)) {

                getline(inFile, phone);
                getline(inFile, email);
                getline(inFile, separator);

                if (name != deleteName) {
                    tempFile << name << endl;
                    tempFile << phone << endl;
                    tempFile << email << endl;
                    tempFile << "-----" << endl;
                } else {
                    found = true;
                }
            }

            inFile.close();
            tempFile.close();

            remove("contacts.txt");
            rename("temp.txt", "contacts.txt");

            if (found)
                cout << "Contact deleted successfully!" << endl;
            else
                cout << "Contact not found." << endl;

            break;
        }

        case 4:
            cout << "Exiting program. Goodbye!" << endl;
            break;

        default:
            cout << "Invalid choice! Try again." << endl;
        }

    } while (choice != 4);

    return 0;
}
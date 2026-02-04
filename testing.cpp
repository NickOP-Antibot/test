#include<iostream>
#include<string>
#include<fstream>

using namespace std;

void checkname(string &, string &, bool &);
void addname(string &);

int main() {
    string name,password;
    bool found = false;

    cout << "Enter your full-name: ";
    getline(cin, name);
    checkname(name, password, found);

    if (found == false) {
        addname(name);
        
    }

    cout << "Continue testing?: \n1. Yes\n2. No\nEnter your choice: ";
    int cont;
    cin >> cont;
    if (cont == 1) {
        cin.ignore();
        main();
    } else {
        cout << "Exiting program." << endl;
        return 0;
    }

    return 0;
}





void checkname(string &name, string &password, bool &found) {
    ifstream inputFile("costomer.txt");
    if (!inputFile) {
        cerr << "Error opening file." << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        if (line.find("name : " + name) != string::npos) {
            if (getline(inputFile, line)) {
                found = true;
                cout << "Enter your password: ";
                cin >> password;
                if (line.find("password : " + password) != string::npos) {
                    cout << "Correct password." << endl;
                } else {
                    cout << "Incorrect password." << endl;
                    inputFile.close();
                    return;
                }
            }
            cout << "\nFound your name in the file : " << name << endl;
            cout << "\n------------------------" << endl;
            for(int i = 0; i < 2; i++) {
                if(getline(inputFile, line)) {
                    cout << line << endl;
                }
            }
            cout << "------------------------\n" << endl;
        }
    }
    if (!found) {
        cout << "Name not found in the file." << endl;
    }
    inputFile.close();
}

void addname(string &name) {
    cout << "\n Do you want to add username?" << endl;
    cout << "1. Yes\n2. No\nEnter your choice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        int age, password;
        string sex;
        cout << "Enter your age: ";
        cin >> age;
        cout << "Enter your sex (male/female): ";
        cin >> sex;
        cout << "Set your password (numeric): ";
        cin >> password;
        ofstream outputFile("costomer.txt", ios::app);
        if (!outputFile) {
            cerr << "Error opening file." << endl;
            return;
        }
        outputFile << "\nname : " << name << endl;
        outputFile << "password : " << password << endl;
        outputFile << "age : " << age << endl;
        outputFile << "sex : " << sex << endl;
        outputFile << "------------------------" << endl;
        outputFile.close();
        cout << "Name added to the file." << endl;
    } else {
        cout << "Exiting without adding name." << endl;
    }
}
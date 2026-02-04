#include<iostream>
#include<string>
#include<fstream>

using namespace std;

void checkname(string &, string &, bool &);
void addname(string &);
void fixname(string &);

int main() {
    string name,password;
    bool found = false;

    cout << "Enter your full-name : ";
    getline(cin, name);
    if (name.empty()) {
        cerr << "Exiting program." << endl;
        return 0;
    }

    fixname(name);

    checkname(name, password, found);

    if (found == false) {
        addname(name);
        
    }

    cout << "Continue testing?: \n1. Yes\n2. No\nEnter your choice: ";
    int cont;
    cin >> cont;
    if (cont == 1) {
        cin.ignore();
        cout << "------------------------\n" << endl;
        main();
    } else {
        cout << "Exiting program." << endl;
        return 0;
    }

    return 0;
}





void checkname(string &name, string &password, bool &found) {
    ifstream inputFile(name + ".txt");
    if (!inputFile) {
        cerr << "Name not found." << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        if (line.find("name : " + name) != string::npos) {
            if (getline(inputFile, line)) {
                found = true;
                cout << "Enter your password: ";
                cin >> password;
                if (line.find("password : " + password) != string::npos && line.substr(11) == password) {
                    cout << "Correct password." << endl;
                } else {
                    cout << "Incorrect password." << endl;
                    cout << "------------------------\n" << endl;
                    inputFile.close();
                    return;
                }
            }
            cout << "\nFound your name : " << name << endl;
            cout << "\n--------Details---------" << endl;
            for(int i = 0; i < 2; i++) {
                if(getline(inputFile, line)) {
                    cout << line << endl;
                }
            }
            cout << "\n------------------------\n" << endl;
        }
    }
    if (!found) {
        cout << "Name not found." << endl;
    }
    inputFile.close();
}

void addname(string &name) {
    cout << "\nDo you want to add username?" << endl;
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
        ofstream outputFile(name + ".txt", ios::app);
        if (!outputFile) {
            cerr << "Error opening file." << endl;
            return;
        }
        outputFile << "--------Details---------" << endl;
        outputFile << "name : " << name << endl;
        outputFile << "password : " << password << endl;
        outputFile << "age : " << age << endl;
        outputFile << "sex : " << sex << endl;
        outputFile << "\n--------History---------" << endl;
        outputFile.close();
        cout << "Name added to the file." << endl;
    } else {
        cout << "Exiting without adding name." << endl;
    }
}

void fixname(string &name) {
    int N = name.size();
    for (int i = 0; i < N; i++) {
        if (name[i] == ' ') {
            name[i] = '_';
        }
        if (name[i] >= 65 && name[i] <= 90) {
            name[i] = name[i] + 32;
        }
    }
}
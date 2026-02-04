#include<iostream>
#include<string>
#include<fstream>

using namespace std;

void checkname(string, bool &);
void addname(string);

int main() {
    string name;
    bool found = false;
    cout << "Enter your name: ";
    getline(cin, name);

    checkname(name, found);

    if (found == false) {
        addname(name);
        
    }
    return 0;
}





void checkname(string name, bool &found) {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error opening file." << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        if (line.find("name : " + name) != string::npos) {
            found = true;
            cout << "\nFound your name in the file : " << name << endl;
            cout << "\n------------------------" << endl;
            cout << line << endl;
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

void addname(string name) {
    cout << "\n Do you want to add username?" << endl;
        cout << "1. Yes\n2. No\nEnter your choice: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            int age;
            string sex;
            cout << "Enter your age: ";
            cin >> age;
            cout << "Enter your sex: ";
            cin >> sex;
            ofstream outputFile("input.txt", ios::app);
            if (!outputFile) {
                cerr << "Error opening file." << endl;
                return;
            }
            outputFile << "\nname : " << name << endl;
            outputFile << "age : " << age << endl;
            outputFile << "sex : " << sex << endl;
            outputFile << endl;
            outputFile.close();
            cout << "Name added to the file." << endl;
        } else {
            cout << "Exiting without adding name." << endl;
        }
}
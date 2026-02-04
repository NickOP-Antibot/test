#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<ctime>

using namespace std;

void checkname(string &, string &, bool &);
void addname(string &);
void fixname(string &);
void fucsex(string &);

time_t now = time(0);
struct tm *timeinfo = localtime(&now);

int main() {
    string name,password;
    bool found = false;
    
    cout << setfill('0') << setw(2) << timeinfo->tm_mday << "/" << setw(2) << timeinfo->tm_mon + 1 << "/" << timeinfo->tm_year + 1900 << "\n";
    cout << setfill('0') << setw(2) << timeinfo->tm_hour << ":" << setw(2) << timeinfo->tm_min << ":" << setw(2) << timeinfo->tm_sec << "\n"<< endl;

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
    ifstream inputFile("costomer/" + name + ".txt");
    ofstream outputFile("costomer/" + name + ".txt", ios::app);
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
            while(getline(inputFile, line)) {
                    cout << line << endl;
                }
            
            outputFile << setfill('0') << setw(2) << timeinfo->tm_mday << "/" << setw(2) << timeinfo->tm_mon + 1 << "/" << timeinfo->tm_year + 1900 << "\n";
            outputFile << setfill('0') << setw(2) << timeinfo->tm_hour << ":" << setw(2) << timeinfo->tm_min << ":" << setw(2) << timeinfo->tm_sec << "\n"<< endl;

            cout << "\n" << endl;
        }
    }
    inputFile.close();
    outputFile.close();
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
        fucsex(sex);
        cout << "Set your password (numeric): ";
        cin >> password;
        ofstream outputFile("costomer/" + name + ".txt", ios::app);
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
        cout << "\n------------------------" << endl;
        cout << "Name added to the file." << endl;
        cout << "------------------------\n" << endl;
    } else {
        cout << "\n------------------------" << endl;
        cout << "Exiting without adding name." << endl;
        cout << "------------------------\n" << endl;
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

void fucsex(string &sex) {
    cout << "Enter your sex (male/female): ";
    cin >> sex;
    if (sex == "male" || sex == "Male" || sex == "MALE" || sex == "m" || sex == "M") {
        sex = "male";
    } else if (sex == "female" || sex == "Female" || sex == "FEMALE" || sex == "f" || sex == "F") {
        sex = "female";
    } else {
        cin.ignore();
        cout << "Please enter again." << endl;
        fucsex(sex);
    }
}
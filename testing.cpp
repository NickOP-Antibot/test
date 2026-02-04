#include<iostream>
#include<string>
#include<fstream>

using namespace std;

int main() {
    ifstream inFile("testfile.txt");
    if (!inFile) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    string data;
    while (getline(inFile, data)) {
        cout << data << endl;
    }
    inFile.close();
    return 0;
}
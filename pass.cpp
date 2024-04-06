#include <iostream>
#include <fstream>
using namespace std;

int main() {
    string password;

    // Prompting the user to enter the password
    cout << "Enter the administrator password: ";
    getline(cin, password);

    // Writing the password to a file named "password.dat"
    ofstream file("password.dat");
    if (file.is_open()) {
        file << password;
        file.close();
        cout << "Password set successfully!" << endl;
    } else {
        cout << "Error: Unable to set password." << endl;
    }

    return 0;
}


#include "Utils.h"
#include <iostream>
#include <limits>

using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getValidatedInput(int min, int max) {
    int choice;
    cin >> choice;
    if (cin.fail() || choice < min || choice > max) {
        clearInput();
        cout << "Invalid option. Please try again." << endl;
        return -1;
    }
    return choice;
}
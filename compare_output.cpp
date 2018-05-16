#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

int main(int argc, char* argv[]) {
    string input_1 = argv[1];
    string input_2 = argv[2];

    ifstream input1, input2;
    input1.open(input_1.c_str());
    input2.open(input_2.c_str());

    while (!input1.eof() && !input2.eof()) {
        string sen1, sen2;
        getline(input1, sen1);
        getline(input2, sen2);
        if (sen1.compare(sen2) != 0) {
            cout << sen1 << ' ' << sen2 << endl;
        }
    }

    if (!input1.eof()) {
        cout << "input1 not eof" << endl;
        while (!input1.eof()) {
            string sen;
            getline(input1, sen);
            cout << sen << endl;
        }
    }

    if (!input2.eof()) {
        cout << "input2 not eof" << endl;
        while (!input2.eof()) {
            string sen;
            getline(input2, sen);
            cout << sen << endl;
        }
    }
    return 0;
}
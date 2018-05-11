#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <ctime>

using namespace std;

void generate_randon_text_file(string file_name, int file_size) {
    ofstream output;
    output.open(file_name.c_str());
    int total_size_so_far = 0;
    int sentence_size = 0;
    int number_of_word = 0;
    char letter;

    while (total_size_so_far < file_size) {
        sentence_size = 1 + rand() % 2000;
        while (total_size_so_far + sentence_size > file_size) {
            sentence_size = 1 + rand() % 2000;
        }
        for (int i = 0; i < sentence_size; i++) {
            letter = 'a' + rand() % 26;
            output << letter;
        }

        total_size_so_far += sentence_size;
        if (total_size_so_far + 1 < file_size) {
            output << endl;
            total_size_so_far ++;
        }
    }
    output.close();
    cout << "File " << file_name << " has been generated!" << endl;
}

void input() {

}

void merge() {
    
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Not enough parameters!" << endl;
        return 0;
    }
    
    // input()
    // merge()    
    return 0;
}
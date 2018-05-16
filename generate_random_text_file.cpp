#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <ctime>

using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 3) {
        return 0;
    }

    string file_name = argv[1];
    int file_size = strtol(argv[2], nullptr, 0);
    int size_each_sentence = file_size / 1000;

    ofstream output;
    output.open(file_name.c_str());
    int total_size_so_far = 0;
    int sentence_size = 0;
    int number_of_word = 0;
    char letter;

    while (total_size_so_far < file_size) {
        sentence_size = 1 + rand() % size_each_sentence;
        while (total_size_so_far + sentence_size > file_size) {
            sentence_size = 1 + rand() % size_each_sentence;
        }
        for (int i = 0; i < sentence_size; i++) {
            letter = ' ' + rand() % 94;
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
    return 0;
}
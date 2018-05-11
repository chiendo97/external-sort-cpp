#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <queue>

using namespace std;

struct HeapNode {
    string sentence;
    int index;
    HeapNode(string a, int b): sentence(a), index(b) {}
    bool operator<(const HeapNode& rhs) const {
        return (sentence.compare(rhs.sentence) > 0);
    }
};

int input(string input_name, int TOTAL_MEM) {
    ifstream input; 
    input.open(input_name.c_str());

    int input_size; 
    input.seekg(0, input.end);
    input_size = input.tellg();
    input.seekg(0, input.beg);
    cout << "The size of the file chosen is (in bytes): " << input_size << endl;

    int runs_count;
    runs_count = input_size / TOTAL_MEM + 1;
    cout << "runs_count: " << runs_count << endl;

    int run_count = 0;
    int total_mem_so_far = 0;

    ofstream output;
    vector<string> data;

    while (!input.eof()) {
        string sentence;
        getline(input, sentence);
        if (total_mem_so_far + sentence.size() < TOTAL_MEM) {
            total_mem_so_far += sentence.size() + 1;
            data.push_back(sentence);
        } else {
            sort(data.begin(), data.end());

            run_count++;
            stringstream ss;
            ss << "run_" << run_count << ".txt";
            output.open(ss.str());

            int data_size = data.size();
            for (int i = 0; i < data_size-1; i++) {
                output << data[i];
                output << endl;
            }
            output << data[data_size-1];
            output.close();

            data.clear();
            total_mem_so_far = sentence.size();
            data.push_back(sentence);
        }
    }

    if (data.size() > 0) {
        sort(data.begin(), data.end());

        run_count++;
        stringstream ss;
        ss << "run_" << run_count << ".txt";
        output.open(ss.str());

        int data_size = data.size();
        for (int i = 0; i < data_size-1; i++) {
            output << data[i];
            output << endl;
        }
        output << data[data_size-1];
        output.close();
    }

    return runs_count;
}

void merge(int runs_count, string output_name) {
    ifstream input[runs_count];
    for (int i = 0; i < runs_count; i++) {
        stringstream ss;
        ss << "run_" << i+1 << ".txt";
        input[i].open(ss.str());
    }

    priority_queue<HeapNode, vector<HeapNode> > heap;

    ofstream output;
    output.open(output_name.c_str());

    for (int i = 0; i < runs_count; i++) {
        string sentence;
        getline(input[i], sentence);
        heap.push(HeapNode(sentence, i));
    }

    while (!heap.empty()) {
        string sentence = heap.top().sentence; 
        int index = heap.top().index;
        heap.pop();

        cout << sentence << ' ' << index << endl;
        output << sentence << endl;
        
        if (!input[index].eof()) {
            getline(input[index], sentence);
            heap.push(HeapNode(sentence, index));
        }
    }

    output.close();
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Not enough parameters!" << endl;
        return 0;
    }

    string input_name = argv[1];
    string output_name = argv[2];
    int TOTAL_MEM = strtol(argv[3], nullptr, 0);
    
    int runs_count = input(input_name, TOTAL_MEM);

    merge(runs_count, output_name);
    return 0;
}
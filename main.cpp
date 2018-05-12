#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <queue>

using namespace std;

const clock_t begin_time = clock();

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

    int run_count = 0;
    int total_mem_so_far = 0;

    ofstream output;
    vector<string> data;

    cout << "File " << input_name << " is being read!" << endl;

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
            cout << "Writing " << ss.str() << endl;
            // cout << "Entire process so far took a total of: " << float(clock() - begin_time) / CLOCKS_PER_SEC * 1000 << " msec." << endl;
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
        cout << "Writing " << ss.str() << endl;
        // cout << "Entire process so far took a total of: " << float(clock() - begin_time) / CLOCKS_PER_SEC * 1000 << " msec." << endl;
        output.open(ss.str());

        int data_size = data.size();
        for (int i = 0; i < data_size-1; i++) {
            output << data[i];
            output << endl;
        }
        input.close();
        output << data[data_size-1];
        output.close();
    }

    cout << "Entire process so far took a total of: " << float(clock() - begin_time) / CLOCKS_PER_SEC * 1000 << " msec." << endl;
    cout << "Read input is done!" << endl;
    return run_count;
}

void merge(int start, int end, int location) {

    int runs_count = end - start + 1;

    ifstream input[runs_count];
    for (int i = 0; i < runs_count; i++) {
        stringstream ss;
        ss << "run_" << start + i << ".txt";
        input[i].open(ss.str());
    }

    priority_queue<HeapNode, vector<HeapNode> > heap;

    ofstream output;
    stringstream ss;
    ss << "run_" << location << ".txt";
    output.open(ss.str());

    for (int i = 0; i < runs_count; i++) {
        string sentence;
        if (!input[i].eof()) {
            getline(input[i], sentence);
            // cout << sentence << ' ' << i << ' ' << sentence.length() << endl;
            // if (sentence.length() == 0) {
            //     cout << "Making heap: " << i << ' ' << sentence << endl;
            // }
            heap.push(HeapNode(sentence, i));
        }
    }

    cout << endl << "Starting merge from " << start << " to " << end << " into " << location << endl;

    while (!heap.empty()) {
        string sentence = heap.top().sentence; 
        int index = heap.top().index;
        heap.pop();

        // cout << sentence << ' ' << index << ' ' << sentence.length() << endl;
        output << sentence << endl;
        
        if (!input[index].eof()) {
            getline(input[index], sentence);
            heap.push(HeapNode(sentence, index));
        }
    }

    cout << "Merging stoped!" << endl << endl;

    for (int i = 0; i < runs_count; i++) {
        input[i].close();
    }

    output.close();
}

void merge(int runs_count, string output_name) {
    const int distance = 100;
    int start = 1;
    int end = runs_count;
    while (start < end) {
        int location = end;
        while (start <= end) {
            int mid = min(start + distance, end);
            location++;
            merge(start, mid, location);
            start = mid + 1;
        }
        end = location;
    }

    // cout << start << ' ' << end << endl;

    stringstream ss;
    ss << "run_" << start << ".txt";
    rename(ss.str().c_str(), output_name.c_str());

    for (int i = 1; i < end; i++) {
        stringstream ss;
        ss << "run_" << i << ".txt";
        cout << "Removing " << ss.str() << endl;
        remove(ss.str().c_str());
    }
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
    // cout << runs_count << endl;

    // for (int i = 1; i <= runs_count; i++) {
    //     stringstream ss;
    //     ss << "run_" << i << ".txt";
    //     cout << "Removing " << ss.str() << endl;
    //     remove(ss.str().c_str());
    // }

    cout << "Entire process took a total of: " << float(clock() - begin_time) / CLOCKS_PER_SEC * 1000 << " msec." << endl;
    return 0;
}
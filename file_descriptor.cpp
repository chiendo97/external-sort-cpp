#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int main() {

    int runs_count = 500;
    int memory_blocks = 1024;

    vector<int> runs_in_pass;

    int runs_countdown = runs_count; // runs_count = input_file_size/TOTAL_MEM + 1;
	int future_runs_num = 0;
	while(runs_countdown > (memory_blocks-1))
	{
		if(runs_countdown % (memory_blocks-1) > 0)
			runs_countdown = (runs_countdown/(memory_blocks - 1)) + 1;
		else
			runs_countdown = runs_countdown/(memory_blocks-1);
		runs_in_pass.push_back(runs_countdown);
		future_runs_num += runs_countdown;
	}
	if(runs_countdown>1)
	{
		future_runs_num++; 
		runs_in_pass.push_back(1);
	}

    for (int i = 0; i < runs_in_pass.size(); i++) {
        cout << i << ' ' << runs_in_pass[i] << endl;
    }
    return 0;
}
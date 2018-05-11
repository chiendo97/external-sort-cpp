# large file sort project


This project is an implementation of the External Sort algorithm in C++.

External sorting is used primarily when data that needs to be sorted is unable to fit into RAM at one time, thus necessitating iterative access of blocks of this data to solve the problem. The algorithm consists of two main steps: first, the data is read into memory a block at a time, sorted, and written back out into temporary files and second, these temporary files are then merged two, three, four, ten, or etc. at a time, similar to merge sort.

# Example

One example of external sorting is the external merge sort algorithm, which is a K-way merge algorithm. It sorts chunks that each fit in RAM, then merges the sorted chunks together.

The algorithm first sorts M items at a time and puts the sorted lists back into external memory. It then recursively does a M/B-way merge on those sorted lists. To do this merge, B elements from each sorted list are loaded into internal memory, and the minimum is repeatedly outputted.

For example, for sorting 900 megabytes of data using only 100 megabytes of RAM:

1. Read 100 MB of the data in main memory and sort by some conventional method, like quicksort.
2. Write the sorted data to disk.
3. Repeat steps 1 and 2 until all of the data is in sorted 100 MB chunks (there are 900MB / 100MB = 9 chunks), which now need to be merged into one single output file.
4. Read the first 10 MB (= 100MB / (9 chunks + 1)) of each sorted chunk into input buffers in main memory and allocate the remaining 10 MB for an output buffer. (In practice, it might provide better performance to make the output buffer larger and the input buffers slightly smaller.)
5. Perform a 9-way merge and store the result in the output buffer. Whenever the output buffer fills, write it to the final sorted file and empty it. Whenever any of the 9 input buffers empties, fill it with the next 10 MB of its associated 100 MB sorted chunk until no more data from the chunk is available. This is the key step that makes external merge sort work externally -- because the merge algorithm only makes one pass sequentially through each of the chunks, each chunk does not have to be loaded completely; rather, sequential parts of the chunk can be loaded as needed.

Historically, instead of a sort, sometimes a replacement-selection algorithm[3] was used to perform the initial distribution, to produce on average half as many output chunks of double the length.

# How to use
Program accept input file name, output file name and memory limit as parameters 

```
g++ main.cpp -o main && ./main "input file name" "output file name" "memory limit"
```
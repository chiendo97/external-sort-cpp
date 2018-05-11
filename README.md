# large file sort project


This project is an implementation of the External Sort algorithm in C++.

External sorting is used primarily when data that needs to be sorted is unable to fit into RAM at one time, thus necessitating iterative access of blocks of this data to solve the problem. The algorithm consists of two main steps: first, the data is read into memory a block at a time, sorted, and written back out into temporary files and second, these temporary files are then merged two, three, four, ten, or etc. at a time, similar to merge sort.

```
g++ main.cpp -o main && ./main 
```
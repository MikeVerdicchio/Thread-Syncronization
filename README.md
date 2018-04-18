Thread Syncronization
=====================
This repository contains the source code for a parallel, maximum-finding binary reduction. This was an assignment for Operating Systems (CS 4414) at the University of Virginia.

**Note: If you are a current student in, or are planning to take, CS 4414, it is an Honor Violation to view this source code.**



Objective
---------
The objective of the machine problem was to implement a parallel, maximum-finding binary reduction. That is, a program that finds the maximum number in a collection on N numbers using only N/2 threads. This required comparing two numbers at a time and passing on the larger of the two onto the next round of comparisons and reusing threads from round-to-round. Furthermore, the problem specified that a barrier primitive be implemented to ensure that all the comparisons for any given round were completed before moving on to the next. The education construct for this assignment was to familiarize ourselves with synchronization primitives and multiple threads of execution.

The focus of this assignment was not to compute the largest number as fast as possible, but to synchronize threads using barriers and semaphores.


Usage
-----
```
make
./generate <num_points>
./max < input.txt
```

The number of points that you can specify for the input file depends on the memory usage by your system and must be a power of 2. A safe number that normally works is 2^14 = 16384. Feel free to experiment with larger inputs on your machine.
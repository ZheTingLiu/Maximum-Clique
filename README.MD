## This assignment is 2018 spring semester for the course named Data Science in NTHU CS.

### Goal
* Find a MAX clique for an undirected graph
* Use C++ to implement it

### Testing environment
* OS: Windows10
* Compiler: g\++ 5.4.0(C++11)

### Data format
* Input file is a .txt file. The following is the content. A line means one edge. Each edge uses one space to distinguish the ID of two nodes. It means that there is an edge between these two nodes.
 ```
	0 1
    0 2
    0 3
    0 4
 ```
* The output file is also a .txt file. The following is the content. Each line represents the ID of one node. The output order is in ascending order.
 ```
 0
 1
 2
 ```
 
### Operation
* Use makefile to compile this program. Type this instruction "main.exe inputFileName.txt oututFileName.txt" in the cmd.
* The program will be terminated if the execution time is over 3 minutes or it finds the MAX clique.

### Note
&emsp; The number of nodes and edges in the final test case are 82168 and 2907369. So, I need to access individual bits in a char or I can't load the test case. The MAX clique size which this program finds in the final testing case is over 1200. I think the test case is customized by TA, so it can be divided by 8. If you want to run in other cases, you need to adjust the program a little. By the way, The TA doesn't provide the final testing case and the final result. I can only know that the clique size is over 1200.
This is assignment 3 of Artificial Intelligence which is based on Heterogeneous grouping.

In the assignment the task is to group N students in M groups according to marks in K different subjects so that the diversity(i.e absolute differnce of marks) in each group is minimum.

Chromosome: Each chromosome is represented by avg value of K different subject of each student in that group(a gene). 
Population size : 200 (Can be changed by changing definition of 'POP_SIZE' in line#34)
Crossover :selecting two parent by tournament selection according to their fitness value and crossing using a random cross over point. 
Mutation : Once in a while in many cycles of crossovers randomly a chromosome is randomly selected and a gene in it is modified randomly.
Fitness function : Based on absolute difference in marks of K subject of in a group expanded over all group. SO objective is get the chromosome with minimum fitness value.


complilation: Run the code.Enter the values required that are asked by the program.
1) Enter number of students
2) No of groups you want to form.
3) No of subjects
Then,
4) Enter the marks of students in those subjects as asked.

Then it will print the best chromosome (or group division) made by program with fitness value which should be minimized here.

To print whole population in descending order uncomment "prntPop(p,n)" in line #315

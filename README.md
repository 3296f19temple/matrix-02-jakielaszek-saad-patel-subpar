# Matrix Multiplication

## Requirements

This lab required us to implement features in the c-programming langauge to allow for matrix multiplication in order to be done with parallelism in mind. The techniques and technology used to do this are MPI, openMP and SIMD to create parallelism to solve the problem. I believe that we have implemented most of the features that were required in this lab. The lab mostly dealt with changing the mmult function to fit the different requirements of the lab such as SIMD and openMP by changing the for-loop contents or adding directives in the case of openMP. MPI required the code to be changed by creating a master/slave relationship in the main file.

The project requires three implementations that must be done. These are SIMD, MPI and openMP. SIMD required that the for-loop in mmult be changed inorder to access memory in a more effiecient way. MPI required the main file to have a master/slave relationship where the master code spilts the code to be sent to different slave processes in order to be multiplied. This required the usage of MPI_Recv and MPI_Send in order to have communication between the master and slaves. The last way to implement the algorithm is to use openMP. This requires mmult function in the mmult_omp.c file to allow for work to be spilt between threads.

## Teamwork

Dishant Patel - wrote the shell script for task 1 and implement MPI to be done in task 5, also wrote the README
Ahmad Saad - Implemented Task 1 to read and write matrix from and to a file. Implemented Task 4 Open MP. Tried to assist Dishant with Task 5. I created and maintained the Trello board mostly.
The master branch was locked so that anything that code has to be done in a seperate branch and can only be added to master through creating pull requests for the branch. The pull requests must be reviewed by someone else besides the person that created the pull request.

## Full Project Life Cycle

Trello project boards were used in order to keep track of the tasks. It was used by pinning a members name to a specific task and changing its status to doing. After the task is done, the member would switch the current task to done and pin to another task and change that task's status.

This does have the usual life cycle of the code that is followed. I think through the building of a shell script that the extra additions to the life cycle of the code can be hidden from the programmer. For instance, the shell script will compile all of the code that is necessary to run the program.

The testing for this project is just write printf statments to see if the code is being executed in the proper places. I think that testing for speed, resources and correctness is also necessary to make sure that the code is being written properly and implemented properly as well. The code correctness from the professor was taken into consideration.

The random generation of matrices in different sizes have been implemented. An extra program was implemented inorder to generate a random matrices in different sizes. A read function was also added into the project inorder to read from a text file and place it into the matrices.

The production of graphs was automated using python and madlid plots to do so.

The majority of tasks is mainly about writing variations of the code with a minor portion to be associated with testing and reporting activities.

## Graphs

matrix-02-jakielaszek-sad-patel-subpar created by GitHub Classroom
Trello BOard Link: https://trello.com/b/uLhLPekH/jakielaszek-saad-patel-subpar

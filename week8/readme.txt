1.Steps
1) First, I examine the code and decided to change the for loop in main
function into multithreading functions. I creat the helper function called
multithread which has type void* to meet the requirement for pthread_create

2)Then I include the library <pthread.h>. I use pthread_create to create
threads and use pthread_join to wait for all threads to complete their tasks.
The task of arranging the created tasks is for the operation system.

3)Then I create some global variable because they need to be used by both the
multithread function and by the main function.


2. Issues
1) It takes time for me to think of where to start.
Basically, what we do for this assignment is to divide the graphing task into
independent sub-tasks to improve the performance. Thus, I find that we could
partition the whole graph into subspaces with #of thread in use. They do not
meet racing conditions, thus I decided to change this part into multithreading.

2)Ascii error
Something strange happened when I copy the main.c file from my pc to seasnet
server. The quotation mark is in weird format so that it has several errors
such as 'stray /342.' So I check manually for quotation marks and main.c could
sucessfully compile.

3)Printf error
Initally I put the printf part for the graph inside the multithread function.
However, it will not work since the output would just be digits instead of
graph. So I create a 3D global array, modifying it in multithread and print
it in main.

3.Performance.
The performance of using 1 thread is exactly the same as the performance of the
main.c before since it also only use 1 thread a time.
Then, comparing the time used with 1,2,4,8 threads, 

real	 0m53.564s
real	 0m27.690s
real	 0m14.231s
real	 0m7.792s

we could see that the more threads it uses, the less time it costs. It is
because the threads work parallely and do the job as one single thread. The
time it costs is inversly proportional to the number of threads.
Also,system times for the 4 situations are all around 53-56s since they
do the same job, the amount of work does not change. It is because of the
multithreading that the performance of this program has been greatly enhance.

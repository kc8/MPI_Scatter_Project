

###################PROJECT TITLE#################################################



MPI Scatter and Gather.

Author:
	Kyle Cooper

Purpose:

	This program scatters an array with n number of ints among n number of processors
then all of the slave (and master) process calculate the total of their sub array and then
"Gather" them back to the master array to do the final sum and print out the time it took to 
complete

Class: 
	Spring 2014 CS 242

Written In:
	Open MPI 1.6.5 and C On Linux Mint 16 32-bit

To Run:
	In the directory of the project folder, in the terminal do the following:

	(Compile without makefile) 
	Compile the MPIProject.c file with terminal using mpicc. 
	Once in the directory use this command: 
		mpicc -o mpiScatter MPIProject.c
	(run without makefile)
	To run make sure you have compiled MPIProject.c and that you are in the directory
	and use mpirun with the number of processes the command 
		mpirun -np (#of procs here) mpiScatter.o 
	With makefile:
		By default type make to compile and execute the program:
		To compile with the make file type:
			make all 
		Then to run the program type: 
			make run 
		The default run, runs the program with 4 processors. To change this 
		either compile/ run manually (without the make file) or change the 
		makefiles's run execs to -np "the number of processors you want".
		

After Running: 
	It will ask for the number of ints in the array to add, make sure this number 
	is divisible by the number of processors or it will not work. 

Environment used:
	TO program Open MPI 1.6.5 was used along with C. This was all done in Linux Mint 
	16 32-bit with the Cinnamon GUI.
	The standard terminal was used (Bash).
	GEdit was also used to actual write the program.
	The entire program was written in VMWare and Virtual box (a virtual machine).

Data used:
	The data used for testing to ensure this program works was small and large
	First a for loop was used, each value (i) would be a small number 1 - 4 and then
	placed into the whole array, from these small numbers the program could be seen 
	that it was working correctly.
	After this larger numbers were used.
	Then finally random large numbers were used from 0 to 100 using srand() and Time 	to seed srand(). These were then added to the array.

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

//@author Kyle Cooper Date: May 8, 2014 Class: Spring 2014 CS242
//Global Varaibales:
int my_id, num_procs;
#define mpi_root 0 //The root proccess so the everyone knows

/*
 This is the main function, it does everything in the program.
 proc_array is the array each proccesor will get
  whole_array is the whole array only known to the master
  back_array is the array that the master will get back after the math is done
Scatter works in this method because it sends out sub arrays to every proccess
 including the master, in this case scatter (and gather) need to be seen be all 
 the proccesors
Gather works be collecting all of the back_arrays that hold the totals of the sub 
arrays and sending them back to the master to do the final summation.
*/
int main(int argc, char **argv) 
{
	/*These are the arrays that will store the entire array, or parts of the 	
	   array for each process, and then the array that is supposed to be sent back 
	  to the main process
	*/ 
	int *proc_array, *whole_array, *back_array;
	int wholeSize, count; //stores  amount of the entire array and size to be sent
	/*holds total for each array and the complete total for entire array*/
	int size, i, total, completetotal;	
	int min = 1, max = 100; //max and min of the size of the numbers
	double start, finish; //start and finsih times
	
	/*
	 These are all of the MPI defenied variables
	*/
	MPI_Status status;
	MPI_Init(&argc, &argv);
	/*
	  my_id holds each proccesorers id, and num_procs holds the user defined 	  
	   amount of proccessors
	*/
	MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	
	/*
	  This is the first time root is encountered, this if statement will make 
	  the entire array, based on the size the user specified out of random numbers
	*/
	if (my_id == mpi_root)
	{
		printf("How many numbers in the array? \n");
		scanf("%d", &wholeSize); //gets random numbers in array from user
		/*//Size of each sub array to be sent to other processors */
		count = wholeSize/num_procs; 

		//allocate size for the entire array: 
		whole_array=(int*)malloc(wholeSize*sizeof(int));
		//allocate size for the return array (of one int each return):
		back_array=(int*)malloc(num_procs*sizeof(int));
		//apply random numbers at some point ****:

		srand(time(NULL)); //seed random with time
		/* loop through to add random numbers to the entire array */
		for(i=0; i<wholeSize;i++)
		{
			whole_array[i]= rand() %(min - max) + min;
			
		}
		start = MPI_Wtime(); //take the start time
	}
	/*
	  allocate enough memory for each sub array on every proccesor (including the 
	  master)
	*/
	proc_array = (int*)malloc(count*sizeof(int));

	//scatters the entire array for all proccessors, each proc gets one in the 
	// entire world, due to how scatter functions.
	MPI_Scatter(whole_array, count, MPI_INT, /*send size of count whole_array*/
			proc_array, count, MPI_INT, /*each proc gets 2 ints */ 			
			mpi_root, MPI_COMM_WORLD); /*master sends to all */
	
	/*
	  This loop will add up each proc_array and then add there part sum to total
	*/
	total = 0;
	for(i = 0; i<count; i++)
	{
		total += proc_array[i];
	}
	/*below is commented out but can be used to print each total for an id */
	//printf("id %d, total %d\n", my_id, total);
	/*
	  Use gather to collect each total and then send them back to the master
	*/
	
	MPI_Gather(&total, 1, MPI_INT, /*sends the value of total to the master */
		back_array,1,MPI_INT, /*the array that the master will get */
		mpi_root, MPI_COMM_WORLD); /*every proccess sends to the master */

	/*
 	  The second if statement checks to make sure the id is the master. It then 
	  gets the back_array from gather and proccess the total sum of the entire 	   
	    array, prints out the total and the time it took
	*/
	if(my_id == mpi_root)
	{
		/*loops through the total  in each back_array and then adds it to the 			 
		 total for the entire array 
		*/
		completetotal = 0;
		for(i=0; i<num_procs; i++)
		{
			completetotal += back_array[i];
		}

		finish = MPI_Wtime(); //Take the finsih time
		/*Print out all the information */
		printf("results from all processors: %d\n", completetotal);
		printf("Start Time: %f Finish Time: %f \n", start, finish);
		printf("Total time: %f\n", finish-start); //prints the time the entire process took
	}
	MPI_Finalize();  //MPI is finally done. Time to quit.


}

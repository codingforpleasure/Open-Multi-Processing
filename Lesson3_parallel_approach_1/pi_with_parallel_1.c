#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 3
static long num_steps = 10000000;
double step;
void main()
{
	int i,gotXthreads;
	double pi;
	double sum[NUM_THREADS]; //changed from variable to an array of sums
	double total_sum= 0.0;
	step = 1.0 / (double) num_steps;

	double time_before, time_after,interval;

	time_before = omp_get_wtime();

	omp_set_num_threads(NUM_THREADS); //Requesting from the system NUM_THREADS
	#pragma openmp parallel
	{
		// each thread holds it's stack, the stack holds the variables below. the reason for this for avoiding race control.

		int j;
		double x;
		int thread_id = omp_get_thread_num();
		int num_of_threads = omp_get_num_threads();

		// saving the number of threads given to me by the system,
		// since not necceraly the NUM_THREADS I requested was given to me can be even less.
		if (thread_id == 0) gotXthreads = num_of_threads;

		//A simple cyclic distribution (round robin) , like dealing a deck of cards
		for (j=0,sum[j] = 0.0 ; j < num_steps; j=j+num_of_threads)
		{
			x = (j+0.5)*step;
			sum[thread_id] = sum[thread_id] + 4.0/(1.0+x*x);

		}
	}

	// Back to the master thread, now our single thread should sum up all the partial sums calculated by the other threads
	for (i=0 ; i < gotXthreads ; i++)
	{
		total_sum = total_sum + sum[i];
	}

	pi = step * total_sum;

	printf("\nThe value of pie is: %.5f\n", pi);
	time_after = omp_get_wtime();
	interval = time_after - time_before;
	printf("\nThe interval time took: %.5f\n", interval); //We can see the false sharing effect
}

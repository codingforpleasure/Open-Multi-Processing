#include <stdio.h>
#include <omp.h>

static long num_steps = 10000000;
double step;

int main(int argc, const char *argv[])
{
	int i;
	double x,pi, sum = 0.0;
	step = 1.0 / (double) num_steps;
	double time_before, time_after,interval;

	/* Taking timestamp before calculation process started */
	time_before = omp_get_wtime();

	for (i=0 ; i < num_steps; i++)
	{
		x = (i+0.5)*step;
		sum = sum + 4.0/(1.0+x*x);
	}

	pi = step * sum;

	printf("\nThe value of pi is: %.5f\n", pi);

	/* Taking timestamp after calculation process ended */
	time_after = omp_get_wtime();

	interval = time_after - time_before;
	printf("\nThe duration time it took to calculate pi was: %f seconds\n", interval);
	return 0;
}


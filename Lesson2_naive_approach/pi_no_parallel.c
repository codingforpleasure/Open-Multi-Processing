#include <stdio.h>
#include <omp.h>

static long num_steps = 10000000;
double step;
void main()
{
	int i;
	double x,pi, sum = 0.0;
	step = 1.0 / (double) num_steps;
	double time_before, time_after,interval;

	time_before = omp_get_wtime();
	for (i=0 ; i < num_steps; i++)
	{
		x = (i+0.5)*step;
		sum = sum + 4.0/(1.0+x*x);
	}

	pi = step * sum;

	printf("\nThe value of pie is: %.5f\n", pi);
	time_after = omp_get_wtime();
	interval = time_after - time_before;
	printf("\nThe interval time took: %f\n", interval);
}

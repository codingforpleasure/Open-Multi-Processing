#include <stdio.h>
#include <omp.h>

int main(int argc, const char *argv[])
{
	#pragma omp parallel
	{
	int ID = omp_get_thread_num();
	printf("hello(%d)",ID);
	printf("world(%d).\n",ID);
	}

	return 0;
}


#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	
	int my_rank, commsize;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &commsize);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	int N = atoi(argv[1]);
	
	double part_sum = 0.0;
	
	//printf("my_rank = %d\n", my_rank);

	int n0 = N * my_rank / commsize + 1;
	int n1 = N * (my_rank + 1) / commsize + 1;
	//printf("n0 = %d, n1 = %d\n", n0, n1);

	for (int i = n0; (i <= N) && (i < n1); ++i) {
		part_sum += 1.0 / i;	
	}
	
	//printf("part_sum = %f\n\n", part_sum);

	if (my_rank != 0) {
		MPI_Send(&part_sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	} else {
		double sum = part_sum;
		for (int i = 1; i < commsize; ++i) {
			MPI_Recv(&part_sum, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			sum += part_sum;
		}

		printf("%f\n", sum);
	}
	
	MPI_Finalize();

	return 0;
}

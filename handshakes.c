#include <mpi.h>
#include <stdio.h>


int main(int argc, char** argv) {
	
	int my_rank, commsize;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &commsize);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	int msg = 1;
	if (my_rank != 0) {
		MPI_Recv(&msg, 1, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("rank %d received a message = %d from rank %d\n", my_rank, msg, my_rank - 1);

		msg++;

		MPI_Send(&msg, 1, MPI_INT, (my_rank + 1) % commsize, 0, MPI_COMM_WORLD);
	}

	if (my_rank == 0) {
		MPI_Send(&msg, 1, MPI_INT, my_rank + 1, 0, MPI_COMM_WORLD);
		MPI_Recv(&msg, 1, MPI_INT, commsize - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("rank %d received a message = %d from rank %d\n", my_rank, msg, commsize - 1);
	}

	MPI_Finalize();

	return 0;
}

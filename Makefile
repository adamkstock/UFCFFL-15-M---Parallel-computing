all: final10-5 final10-2 final10-1 final9-1 final9-2 final9-5

final10-5: 10-5final.c
	mpicc -g 10-5final.c -o final10-5 -fopenmp -lcrypto

final10-2: 10-2final.c
	mpicc -g 10-2final.c -o final10-2 -fopenmp -lcrypto

final10-1: 10-1final.c
	mpicc -g 10-1final.c -o final10-1 -fopenmp -lcrypto

final9-1: 9-1final.c
	gcc 9-1final.c -o final9-1 -lcrypto -fopenmp

final9-2: 9-2final.c
	gcc 9-2final.c -o final9-2 -lcrypto -fopenmp

final9-5: 9-5final.c
	gcc 9-5final.c -o final9-5 -lcrypto -fopenmp


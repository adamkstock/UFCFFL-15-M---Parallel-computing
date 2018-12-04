all: test10-5 test10-2 test10-1

test10-5: 10-5thread.c
	mpicc -g 10-5thread.c -o test10-5 -fopenmp -lcrypto

test10-2: 10-2thread.c
	mpicc -g 10-2thread.c -o test10-2 -fopenmp -lcrypto

test10-1: 10-1thread.c
	mpicc -g 10-1thread.c -o test10-1 -fopenmp -lcrypto


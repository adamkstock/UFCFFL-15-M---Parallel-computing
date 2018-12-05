# UFCFFL-15-M---Parallel-computing

## Presentation in labled folder 

### attempts in c labled by attempt -
  
        source 		= x.c  	    
        compiled file 	= testx  

### completed versions labled as -

        source 		= x-xfinal.c
        compiled file	= completex-x

### compilation -
 
        files labled 1 and 3-9 compile using -
		- gcc (source).c -o (compiled file)  -lcrypto
		- example 'gcc 8-5thread.c -o test8-5  -lcrypto'
        these require the linker switch '-lcrypto' as they use the encryption functions

        file 2.c compiles with -   
                - gcc 2.c -o test2
        this file can be compiled without switches

        files 10 and higher compile with -
                - mpicc -g (source).c -o (compiled file) -fopenmp -lcrypto
        these files require the open mpi wrapper, this is a small shell script that       
        invokes gcc with the relevent arguements for mpi compilation

### execution - 

        files 1-9 can be run using -
                - ./(compiled file)

        files 10 and higher require -  
                - mpirun -np (number of threads) ./(compiled file)

        make and shell script files can be run using - 
                - ./(filename).(extension if required)


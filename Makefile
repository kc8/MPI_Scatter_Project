# Makefile for MPI programs

##### User configurable options
MF=     Makefile.MPI.c
CC          = mpicc
CLINKER     = $(CC)
OPTFLAGS    = -O2

# The paths to MPI and X11
MPI_DIR     = $(MPI_LIB)
INCLUDE_DIR = -I$(MPI_INCLUDE)
###MPE_LIBS    = -lmpe -lX11 -lm

### End User configurable options

###MPEFLAGS    = -mpe=graphics
CFLAGS  =   $(OPTFLAGS)  $(INCLUDE_DIR) $(MPIINC) -I$(MPIHOME)/include -I$(MPIDIR)
LIBS = -lmpi
EXECS = all run
SRC= \   mpi  
        
default: $(EXECS)

clean:
	/bin/rm -f *.o *~ $(EXECS)
	
all:  MPIProject.c
	$(CC) $(FLAGS) MPIProject.c -o MPIProjectScatter

run: MPIProjectScatter
	mpirun -np 4 MPIProjectScatter

.c.o:
	$(CC) $(CFLAGS) -c $*.c

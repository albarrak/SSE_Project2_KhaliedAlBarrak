CC = gcc
CFLAGS= -o
DeFLAG= -Wall
OptFLAG= -o3
EXE= App
SRC= Application.c ForestImplementation.c ImageImplementation.c ImageOperations.c UnionFindImplementation.c
OBI=$(SRC:.c=.o)

all: $(SRC) $(EXE)
	
$(EXE): $(OBI)
	@echo "compiling the code in Profiling mode"
#	$(CC) -c $(SRC)
#	$(CC) $(CFLAGS) $@ $(OBI) -g -pg
	$(CC) $(CFLAGS) $@ $(OBI) -lm -g -pg
.c.o:
	$(CC) -c $< -o $@
Run:
	App frame.ppm GreenScreenSample.ppm image.ppm 4
	@echo "Finish Running"
	
clean:
	del *.o *.exe

CC = gcc
CFLAGS= -o
DeFLAG= -Wall
OptFLAG= -o3
ImageName=image.ppm
EXE= App
SRC= Application.c ForestImplementation.c ImageImplementation.c ImageOperations.c UnionFindImplementation.c
OBI=$(SRC:.c=.o)

all: $(SRC) $(EXE)
	
$(EXE): $(OBI)
	@echo "compiling the code"
	$(CC) $(CFLAGS) $@ $(OBI) -lm
.c.o:
	$(CC) -c $< -o $@

profile: $(OBI)
	@echo "Profiling the code"
	$(CC) $(CFLAGS) $(EXE) $(OBI) -lm -g -pg
#	App.exe frame.ppm GreenScreenSample.ppm $(ImageName) 40
	gprof App.exe gmon.out

debug: $(OBI)
	echo "Debug the code using -Wall"
	$(CC) -c $(DeFLAG) $(SRC) 
	$(CC) $(CFLAGS) $(EXE) $(OBI) -lm 
optimize: $(SRC)
	@echo "Optimizing the code"
	$(CC) -c $(OptFLAG) $(SRC)
	$(CC) $(CFLAGS) $(OptFLAG) $(EXE) $(OBI) -lm

Run:
	App frame.ppm GreenScreenSample.ppm $(ImageName) 40
	@echo "Finish Running"
	
clean:
	del *.o *.exe gmon.out $(ImageName)

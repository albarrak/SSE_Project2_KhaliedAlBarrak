CC = gcc
CFLAGS= -o
DeFLAG=  -Wall
OptFLAG= -O3
ImageName=image.ppm
EXE= App
SRC= Application.c ForestImplementation.c ImageImplementation.c ImageOperations.c UnionFindImplementation.c
OBI=$(SRC:.c=.o)

all: $(SRC) $(EXE)
	
$(EXE): $(OBI)
	@echo "compiling the code"
	$(CC) $(CFLAGS) $@ $(OBI) -lm

profile: $(OBI)
	@echo "Profiling the code"
	$(CC) $(CFLAGS) $(EXE) $(OBI) -lm -g -pg
#	App.exe frame.ppm GreenScreenSample.ppm $(ImageName) 40
#	gprof App.exe gmon.out

debug: $(OBI)
	echo "Debug the code using -Wall"
	$(CC) -c $(DeFLAG) $(SRC) 
	$(CC) $(CFLAGS) $(EXE) $(OBI) -lm 
	
optimize: $(SRC) 
	@echo "Optimizing the code"
	$(CC) -c $(OptFLAG) $(SRC)
	$(CC) $(CFLAGS) $(EXE) $(SRC) -lm
	
testing: 
	
.c.o:
	$(CC) -c $(OptFLAG) $< -o $@

Run:
	App GreenScreenSample.ppm frame.ppm $(ImageName) 40
	@echo "Finish Running"
	
clean:
	del *.o *.exe gmon.out $(ImageName) 

# Variables
CC = gcc
CFLAGS= -o
DeFLAG=  -Wall
OptFLAG= -O3
ImageName=image.ppm
EXE= App
# SRC files for the compiling
SRC= Application.c ForestImplementation.c ImageImplementation.c ImageOperations.c UnionFindImplementation.c
# SRC files for the testing
SRCTest1= tstOne.c ForestImplementation.c  UnionFindImplementation.c
SRCTest2= tstTwo.c ForestImplementation.c  UnionFindImplementation.c
SRCTest3= tstThree.c ForestImplementation.c  UnionFindImplementation.c
# Renaming SRC files to Object file
OBITest1=$(SRCTest1:.c=.o)
OBITest2=$(SRCTest2:.c=.o)
OBITest3=$(SRCTest3:.c=.o)
OBI=$(SRC:.c=.o)

# Targets
all: $(SRC) $(EXE)
	
$(EXE): $(OBI)
	@echo "compiling the code"
	$(CC) $(CFLAGS) $@ $(OBI) -lm

profile: $(OBI)
	@echo "Profiling the code"
	$(CC) $(CFLAGS) $(EXE) $(OBI) -lm -g -pg
	./App frame.ppm GreenScreenSample.ppm $(ImageName) 40 
	gprof App.exe gmon.out					

debug: $(OBI)
	echo "Debug the code using -Wall"
	$(CC) -c $(DeFLAG) $(SRC) 
	$(CC) $(CFLAGS) $(EXE) $(OBI) -lm 	
optimize: $(SRC) 
	@echo "Optimizing the code"
	$(CC) -c $(OptFLAG) $(SRC)
	$(CC) $(CFLAGS) $(EXE) $(SRC) -lm
test-all:
	-@python tstingCases.py

test1: $(SRCTest1) $(OBITest1)
	@echo "Running Test 1.."
	$(CC) $(CFLAGS) $@ $(OBITest1) -lm
test2: $(SRCTest2) $(OBITest2)
	@echo "Running Test 2.."
	$(CC) $(CFLAGS) $@ $(OBITest2) -lm
test3: $(SRCTest3) $(OBITest3)
	@echo "Running Test 3.."
	$(CC) $(CFLAGS) $@ $(OBITest3) -lm	
.c.o:
	$(CC) -c $(OptFLAG) $< -o $@

run:
	@echo "Running the exe file"
	./App GreenScreenSample.ppm frame.ppm $(ImageName) 40
clean:
#	del *.o *.exe gmon.out $(ImageName) test*  
	rm *.o App gmon.out $(ImageName) test*

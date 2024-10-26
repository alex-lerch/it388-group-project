all: Controller.o FileReader.o FileWriter.o MergeSortInt.o MPIMergeSortInt.o OMPMergeSortInt.o MergeSortLong.o MPIMergeSortLong.o OMPMergeSortLong.o
	g++ -o main.exe Controller.o FileReader.o FileWriter.o MergeSortInt.o MPIMergeSortInt.o OMPMergeSortInt.o -fopenmp

Controller.o: Controller.cpp FileReader.o FileWriter.o MergeSortInt.o MPIMergeSortInt.o OMPMergeSortInt.o
	g++ -c Controller.cpp

FileReader.o: FileReader.cpp
	g++ -c FileReader.cpp

FileWriter.o: FileWriter.cpp
	g++ -c FileWriter.cpp

#Int files
MergeSortInt.o: MergeSortInt.cpp
	g++ -c MergeSortInt.cpp

MPIMergeSortInt.o: MPIMergeSortInt.cpp MergeSortInt.h
	g++ -c MPIMergeSortInt.cpp

OMPMergeSortInt.o: OMPMergeSortInt.cpp MergeSortInt.h
	g++ -c OMPMergeSortInt.cpp

#Long files
MergeSortLong.o: MergeSortLong.cpp
	g++ -c MergeSortLong.cpp

MPIMergeSortLong.o: MPIMergeSortLong.cpp MergeSortLong.h
	g++ -c MPIMergeSortLong.cpp

OMPMergeSortLong.o: OMPMergeSortLong.cpp MergeSortLong.h
	g++ -c OMPMergeSortLong.cpp

clean:
	rm *.o all
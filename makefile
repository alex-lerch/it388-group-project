merg_sort: Controller.cpp FileReader.cpp FileWriter.cpp MergeSortInt.cpp MergeSortString.cpp MergeSortLong.cpp OMPMergeSortInt.cpp OMPMergeSortLong.cpp MPIMergeSortInt.cpp MPIMergeSortLong.cpp OMPMergeSortString.cpp
	mpicxx -o merge_sort Controller.cpp FileReader.cpp FileWriter.cpp MergeSortInt.cpp MergeSortString.cpp MergeSortLong.cpp OMPMergeSortInt.cpp OMPMergeSortLong.cpp OMPMergeSortString.cpp MPIMergeSortInt.cpp MPIMergeSortLong.cpp -fopenmp

clean:
	rm merge_sort
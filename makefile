merg_sort: Controller.cpp FileReader.cpp FileWriter.cpp MergeSortInt.cpp MergeSortLong.cpp OMPMergeSortInt.cpp OMPMergeSortLong.cpp MPIMergeSortInt.cpp MPIMergeSortLong.cpp
	mpicxx -o merge_sort Controller.cpp FileReader.cpp FileWriter.cpp MergeSortInt.cpp MergeSortLong.cpp OMPMergeSortInt.cpp OMPMergeSortLong.cpp MPIMergeSortInt.cpp MPIMergeSortLong.cpp -fopenmp

clean:
	rm merge_sort